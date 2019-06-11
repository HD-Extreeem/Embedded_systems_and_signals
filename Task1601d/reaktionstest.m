function reaktionstest( a )
%reaktionsTEST
%   Detailed explanation goes here
a.pinMode(4,'INPUT');%player 1 btn
a.pinMode(11,'INPUT');%player 2 btn

a.pinMode(6,'OUTPUT');% player 1 led
a.pinMode(7,'OUTPUT');% player 2 led
a.pinMode(8,'OUTPUT');% main led

a.digitalWrite(6,0);
a.digitalWrite(7,0);
a.digitalWrite(8,0);

%p1Time = zeros(1,8);
%p2Time = zeros(1,8);

score = zeros(8,3);
points = zeros(8,2);

gameStart = 0;
startCounting = 0;
initializeTimer = 0;
i = 1;
setCounter = 1;
allowedToPress = 0;
player1btn = 0;
player2btn = 0;
player1ScoreSet = 0;
player2ScoreSet = 0;

while(1)
    %Startar timer för spelet
    
    if ~initializeTimer
        tic
        initializeTimer = 1;
    end
    
    %Läser in knappar för p1 och p2
    player1btn = ~a.digitalRead(11);
    player2btn = ~a.digitalRead(4);
    
    %startar spelet vid start
    if ~gameStart
        gameStart = 1;
        pause(2);
        
        player1btn = 0;
        player2btn = 0;
    end
    
    if gameStart
        %kör 7 rundor
        if(i<=7)
            %startar counter för timern
            %skriver runda i matrixen
            %slumpar tid
            if (setCounter == i)
                startTime = toc;
                randTime = (rand(1)*5)+2; %% slumpar mellan 2 och 7
                score(i,1) = i;
                setCounter = i+1;
                player1btn = ~a.digitalRead(11);
                player2btn = ~a.digitalRead(4);
                
            end
            
            
            %räknar ner timern
            elapsedTime = toc-startTime;
            
            %kollar om timern är ute för att kunna trycka
            if (elapsedTime >= randTime) && allowedToPress == 0
                a.digitalWrite(8,1);
                allowedToPress = 1;
                tic
            end
            
            %AEGPIJAEPGIJAEGIPAEGJPAEIJAEGG
            
            
            if (player1btn  || player2btn)
                
                if allowedToPress
                    
                    
                    %tar tid vid tryck för p2 och sätter flagga  
                    %tar tid vid tryck för p1 och sätter flagga  
                    if (player1btn && player2btn && ~(player1ScoreSet || player2ScoreSet))
                        score(i,3) = toc;
                        score(i,2) = score(i,3);
                        disp(score(i,2));
                        disp(score(i,3));
                        player1ScoreSet = 1;
                        player2ScoreSet = 1;
                       
                        
                        
                    %tar tid vid tryck för p1 samt sätter flagga    
                    elseif (player1btn  && ~player1ScoreSet)
                        score(i,2) = toc;
                        disp(score(i,2));
                        player1ScoreSet = 1;
                    %tar tid vid tryck för p2 och sätter flagga    
                    elseif (player2btn  && ~player2ScoreSet)
                        score(i,3) = toc;
                        disp(score(i,3));
                        player2ScoreSet = 1;
                        
                    end
                    
                 %slumpar ny tid ifall man fuskar   
                elseif ~allowedToPress
                    %pressed before main LED was on.
                    setCounter = i;
                    disp('game reset');
                    
                    player1btn = 0;
                    player2btn = 0;
                end
            end
            
        end
        %kollar ifall båda har tryckt för att starta ny runda samt tända
        %led för vinnare/vinnarna och lagra resultat
        if (player1ScoreSet && player2ScoreSet) == 1
            
            %kollar ifall p1 fick samma tid som p2 
            %Ger dem samma resultat och tänder leden på den
            if score(i,2) == score(i,3)
                a.digitalWrite(6,1);
                a.digitalWrite(7,1);
                points(i,1)=1;
                points(i,2)=1;
            %kollar ifall p1 fick mindre tid än p2 
            %tänder led för p1 och ger den poäng
            elseif score(i,2)<score(i,3)
                a.digitalWrite(6,1);
                points(i,1)=1;
                points(i,2)=0;
            %kollar ifall p2 fick mindre tid än p1
            %tänder led för p2 och ger p2 resultat
            elseif score(i,3)<score(i,2)
                
                a.digitalWrite(7,1);
                points(i,1)=0;
                points(i,2)=1;
                
                
            end
            %återställer flaggor för spelarna
            player1btn = 0;
            player2btn = 0;
            
            %kollar om alla 7 rundor är slut
            %skriver ut resultatet och tiden för dem båda
            if (i >= 7)
                score(8,2) = (sum(score(1:7,2))/7);
                points(8,1)=  (sum(points(1:7,1)));
                
                score(8,3) = (sum(score(1:7,3))/7);
                points(8,2)=  (sum(points(1:7,2)));
                header = {'Omgång','spelare 1','spelare 2'};
                disp([header;num2cell(score(1:7,1:3))])
                header = {'medelvärde spelar 1','medelvärde spelare 2'};
                disp([header;num2cell(score(8,2:3))])
                header = {'Poäng spelare 1','poäng spelare 2'};
                disp([header;num2cell(points(8,1:2))]);
            end
            player1btn = 0;
            player2btn = 0;
            pause(2);
            
            %återställer flaggor för score samt att man kan trycka på knapp
            %släcker alla led
            i=i+1;
            player1ScoreSet = 0;
            player2ScoreSet = 0;
            allowedToPress = 0;
            a.digitalWrite(6,0);
            a.digitalWrite(7,0);
            a.digitalWrite(8,0);
        end
    end
    
end


end


