function dynamiclock( a )

%------------------------------------------------------------------------------------------
%   Dynamiclock
%   Ett lås vilket styres med hälp av en arduino
%   Systemet består av 4 knappar
%   varav 3 av dem är för kombination och 1 för att byta lösen
%   Vid rätt kombination tänds den storalampan
%   Slår man fel kombination 3 gånger bryts Systemet
%   Kombinationen väljs vid start av programmet och kan bytas enbart när öppet tillstånd
% Authors: Leonard Holgorsson & Hadi Deknache
%------------------------------------------------------------------------------------------

nextState = 'changepass';
currentState = nextState;

%Initerar alla knappar som ingågnar för att läsa in värde
a.pinMode(2,'INPUT');%btn 1
a.pinMode(3,'INPUT');%btn 2
a.pinMode(4,'INPUT');%btn 3
a.pinMode(5,'INPUT');%btn change pass

%Initerar alla led som utgångar för att skriva ut värde
a.pinMode(6,'OUTPUT');% led 1
a.pinMode(7,'OUTPUT');% led 2
a.pinMode(8,'OUTPUT');% led 3
a.pinMode(9,'OUTPUT');% Bigled 4

%Sätter alla led till avstängda
a.digitalWrite(6,0);
a.digitalWrite(7,0);
a.digitalWrite(8,0);
a.digitalWrite(9,0);

%Vår försöksvariabel som håller reda på antalet fel man tryckt
tries = 0;
i = 1;

btnPressed = 0;
k = 0;

%Matrix med kombinationer som ska lagras
b = zeros(2,4);

while(1)

    % Kollar ifall man försökt öppna låset mer än 3 gånger
    % Stoppar programmet ifall tries är 3 eller större

    if (tries >=3)
        a.digitalWrite(6,0);
        a.digitalWrite(7,0);
        a.digitalWrite(8,0);
        a.digitalWrite(9,0);

        disp('too many failed attempts');

        break;
    end


    %Läser in knapparna

    k1=~a.digitalRead(2);
    k2=~a.digitalRead(3);
    k3=~a.digitalRead(4);
    passBtn = ~a.digitalRead(5);

    %Om man trycker någon av dem 3 knapparna sätts btnPressed till1
    %Annars är den 0
    if k1 | k2 | k3
        btnPressed = 1;
    elseif ~(k1 | k2 | k3)
        btnPressed = 0;
    end

    %Ser vilken knapp som tryckts ifall btnPressed
    %Samt kontrollerar så att man inte trycker flera samtidigt
    if btnPressed
        if k1 && ~(k2 | k3)
            k = 1;
        end
        if k2 && ~(k1 | k3)
            k = 2;
        end
        if k3 && ~(k1 | k2)
            k = 3;
        end

    end

    %Switch case sats som kollar state samt bytar ifall en ny händelse inträffar
    switch currentState
        %Case för att byta kombination
        case {'changepass'}
            if btnPressed
                nextState = 'changepress';
                btn = k;
            end

        %Kollar vilken knapp som tryckts
        case {'changepress'}

            if btnPressed
                btn = k;
                nextState = 'changepress';
            end

            if ~btnPressed
                nextState = 'changerelease';
            end

        %Case för när man släpper knappen som skall lagras
        case {'changerelease'}
            %Säkerhetsställer att man släppt knappen
            %Och att i mindre än 4 då kombination ska vara 4 lång
            %Lagrar knapp i Matrix och ökar i
            if ~btnPressed && i <4
                b(1,i) = btn;
                disp(b(1,i));
                nextState = 'changepass';
                i = i+1;

            % Annars ifall i =4 eller större samt ingen knapp tryckts
            %Lagrar knapptryck och går till nästa state låst
            elseif ~btnPressed && i >=4
                b(1,i) = btn;
                disp(b(1,i));
                nextState = 'locked';
                disp(b(1,1:4));
                tries = 0;
            end

        %Case låst stänger den av alla led
        %Läser av första rätta knapp i matrixen

        case{'locked'}

            i = 1;
            a.digitalWrite(6,0);
            a.digitalWrite(7,0);
            a.digitalWrite(8,0);
            a.digitalWrite(9,0);

            b(2,i) = k;

            %Kollar ifall knapp motsvarade samma som i matrixen
            %Går till nästa state
            if btnPressed && k == b(1,i)
                nextState = 'push1';
            end

            % ifall inte samma så fortsätter den i go2locked
            if btnPressed && k ~= b(1,i)
                nextState = 'go2locked';
            end

        % Fastnar här sålänge man trycker knapp
        case{'go2locked'}

            if k2 | k1 | k3
                nextState = 'go2locked';
            end
            %Ökar tries ifall man trycker fel knapp
            if ~(k2 | k1 | k3)
                tries = tries+1;
                nextState = 'locked';
            end

        %case för första rätta kombination
        case{'push1'}

            % Medan rätt knapp nedtryckt hamnar den i samma state
            if btnPressed && k == b(1,i)
                nextState = 'push1';

                %Om fel knapp trycks låses den igen
                if btnPressed && k ~= b(1,i)
                    nextState = 'go2locked';
                end

            % Annars rätt knapp släpps går den till release1
            elseif ~btnPressed
                nextState = 'release1';
                i=2;
            end


        case{'release1'}

            %Tänder lampa för första rätt knappkombination
            if ~btnPressed
                a.digitalWrite(6,1);
            end
            %Om fel knapp trycks låses den igen
            if btnPressed && k ~= b(1,i)
                nextState = 'go2locked';
            end
            %Ifall rätt knapp trycks för kombination 2 går den till nästa state
            if btnPressed && k == b(1,i)
                nextState = 'push2';
            end

        case{'push2'}
            % Medan rätt knapp nedtryckt hamnar den i samma state
            if btnPressed && k == b(1,i)
                nextState = 'push2';
            end
            % Annars rätt knapp släpps går den till release2
            if ~btnPressed
                nextState = 'release2';
                i=3;

            end
            %Ifall fel knapp trycks ner istället låses det
            if btnPressed && k ~= b(1,i)
                nextState = 'go2locked';
            end

        case{'release2'}
            %kollar så att knapp släppt
            if ~btnPressed
                a.digitalWrite(7,1);
            end

            %Kollar nästa kombination att det är rätt
            if btnPressed && k == b(1,i)
                nextState = 'push3';
            end
            %Låses ifall fel knapp trycks
            if btnPressed && k ~= b(1,i)
                nextState = 'go2locked';
            end


        case{'push3'}
            %Ifall rätt knapp trycks går den till push 3
            if btnPressed && k == b(1,i)
                nextState = 'push3';
            end

            %Ifall knapp släpps går den till release3 och ökar steget i matrixen
            if ~btnPressed
                nextState = 'release3';
                i=4;

            end
            %Ifall fel knapp låses låset
            if btnPressed && k ~= b(1,i)
                nextState = 'go2locked';
            end

        case{'release3'}
            %Ifall ingen knapp trycks tänder den lampan för rätt kombination
            if ~btnPressed
                a.digitalWrite(8,1);
                nextState = 'release3';
            end
            %ifall rätt knapp trycks så hoppar den till nästa state
            if btnPressed && k == b(1,i)
                nextState = 'push4';

            end
            %ifall fel knapp låses systemet
            if btnPressed && k ~= b(1,i)
                nextState = 'go2locked';
            end


        case{'push4'}
            %Kollar om knapp tryckts och rät knapp i matrixen motsvarar
            if btnPressed && k == b(1,i)
                nextState = 'push4';

            end
            %Ifall knapp släpps går den till öppet
            if ~btnPressed
                nextState = 'open';

            end
            %Ifall fel knapp trycks låses det
            if btnPressed && k ~= b(1,i)
                nextState = 'go2locked';
            end

        case{'open'}
            %Nollställer försöken
            tries = 0;
            %Kollar så att ingen knapp trycks
            if ~btnPressed
                nextState = 'open';
            %Annars ifall någon knapp trycks så låses låset
            elseif (k1 | k2 | k3)
                nextState = 'go2locked';
            end
            a.digitalWrite(6,0);
            a.digitalWrite(7,0);
            a.digitalWrite(8,0);
            a.digitalWrite(9,1);


            %Ifall man trycker på byt kombinationknappen
            %Hoppar den in i byt kombination
            if passBtn
                disp('Changepass')
                nextState='changepass';
                i = 1;
                a.digitalWrite(9,0);

            end

    end

    %Sätter nästa state till nuvarande state
    currentState=nextState;
end



end
