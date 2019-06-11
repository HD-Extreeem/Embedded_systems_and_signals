function [e, u, y, y2, t]=sjalvsvang(a, N, Ts, v)
% Stomme f?r regulator-block. Kan anv?ndas f?r att l?gga till och anpassa till olika 
% klassiska, tidsdiskreta regulatorer 

% Argument (anpassas efter ?ndam?l)
% a: arduino-objektet som Matlab anv?nder f?r att kommunicera med Arduino
% N: antal samplingar
% Ts: samplingstiden mellan samplingar
% v: b?rv?rde i digitala enheter (0..1023)

% Resultat (anpassas efter ?ndam?l)
% e: vektor med N m?tningar av felsignalen
% u: vektor med N m?tningar av styrsignalen
% y: vektor med N m?tningar av process-svaren == ?rv?rden
% t: tidsdiskret tidsvektor 1:N


% Initialisering av variablerna ---------------------------------------------------------------
e=zeros(1, N);
u=zeros(1, N);
y=zeros(1, N);
y2=zeros(1,N);
t=zeros(1, N);
w=zeros(1,N);
ei=zeros(1,N);

start=0; elapsed=0; ok=0; % anv?nds f?r att uppt?cka f?r korta samplingstider
k=0; % samplingsindex

% Konfigurering av in- och utg?ngar -----------------------------------------------------
% Arduino ing?ngar
% analoga ing?ngar ?A0? och ?A1? beh?ver inte konfigureras. 0..1023 
% ?A0?: y
% analoga utg?ngar beh?ver inte heller konfigureras. DAC1-> PWM, DAC0 -> DAC, 
% 0..255
% ?DAC0?: u
Kp=9.97209;
Kp1=1;
Ti=28.23529412
Td=1,991555243;
analogRead(a, 'A0');%Tar bort ful spik i b?rjan av plottningen.
analogRead(a,'A1');
% cyklisk exekvering av samplingar
  for k=1:N % slinga kommer att k?ras N-g?ngar, varje g?ng tar exakt Ts-sekunder
    
    start = cputime; %startar en timer f?r att kunna m?ta tiden f?r en loop
    if ok <0 % testar om samplingen ?r f?r kort
        k 
        disp('samplingstiden ?r f?r lite! ?ka v?rdet f?r Ts');
        return
    end
    
   % uppdatera tidsvektorn
   t(k)=k;
    
   % l?s ing?ngsv?rde sensorv?rden
    y(k)= analogRead(a, 'A0'); % m?t ?rv?rdet
    y2(k)=analogRead(a,'A1');
    % ber?kna felv?rdet som skillnad mellan ?rv?rdet och b?rv?rdet 
    e(k)=v-y2(k);
    
     % Regulatorblock
     % ber?kna styrv?rdet, t.ex p-regulator med f?rst?rkning Kp=
     
     %w(k)=(w(k-1)+e(k));
     %u(k)=1*(e(k)+Td*((e(k)-e(k-1))/Ts)+((Ts/1)*w(k))); % p-regulator, Kp=1
     %u(k)=Kp*(e(k)+((Ts/999999999999999999)*sum(e(k)+(Td*(e(k)-e(k-1))/Ts))));
     
    % begr?nsa styrv?rdet till l?mpliga v?rden, vattenmodellen t.ex. u >=0 och u <255, samt
    %      heltal
    
    if(k==1)
        %w(k)=(w(k)+e(k));
        %u(k)=Kp*(e(k)+(Td*(e(k)-e(k))/Ts)+((Ts/1)*w(k))); % p-regulator, Kp=1
        ei(k)=e(k)+e(k);
        %P(k)=Kp*e(k);
        %I(k)=Td*(e(k)+e(k-1)/Ts);
        %D(k)=Kp*(Td/Ts)*(e(k)-e(k-1));
        %u(k)=Kp*(P(k)+I(k)+D(k));
        u(k)=Kp.*(e(k)+((Ts/Ti).*sum(ei(k)+(Td.*(e(k)-e(k))/Ts))));
    else
        %w(k)=Kp*(w(k-1)+e(k));
        %u(k)=Kp*(e(k)+(Td*(e(k)-e(k-1))/Ts)+((Ts/1)*w(k))); % p-regulator, Kp=1
        ei(k)=e(k-1)+e(k);
        u(k)=Kp.*(e(k)+((Ts/inf).*sum(ei(k)+(Td.*(e(k)-e(k-1))/Ts))));
    end
    u(k)=min(max(0, round(u(k))), 255);
    
    % skriva ut styrv?rdet
    analogWrite(a,u(k), 'DAC1'); %DAC-utg?ng

    %online-plot
    plot(t,y,'k-',t,y2,'g',t,u,'m:',t,e,'b');
    %plot(t,y2,'g',t,u,'m:',t,e,'b');
    
    elapsed=cputime-start; % r?knar ?tg?ngen tid i sekunder
    ok=(Ts-elapsed); % sparar tidsmarginalen i ok
    
    pause(ok); %pausar resterande samplingstid
  
end % slut av samplingarna ----------------------------------------------------------------------

% plotta en fin slutbild, 
  plot(t,y,'k-',t,y2,'g',t,u,'m:',t,e,'b');
  %plot(t,y2,'g',t,u,'m:',t,e,'b');
  xlabel('samples k')
  ylabel('y, y2, u ,e')
  title('PID-regulator')
  legend('?vreTank1 ','UndreTank2', 'u ', 'e ')
  analogWrite(a,0, 'DAC1');
% -------------------------------------------------------------------------------------------

