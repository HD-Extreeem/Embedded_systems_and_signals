function [e, u, y, t]=Preglering(a, N, Ts, v)
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
t=zeros(1, N);

start=0; elapsed=0; ok=0; % anv?nds f?r att uppt?cka f?r korta samplingstider
k=0; % samplingsindex

% Konfigurering av in- och utg?ngar -----------------------------------------------------
% Arduino ing?ngar
% analoga ing?ngar ?A0? och ?A1? beh?ver inte konfigureras. 0..1023 
% ?A0?: y
% analoga utg?ngar beh?ver inte heller konfigureras. DAC1-> PWM, DAC0 -> DAC, 
% 0..255
% ?DAC0?: u
analogRead(a, 'A0');%Tar bort ful spik i b?rjan av plottningen.
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
    % ber?kna felv?rdet som skillnad mellan ?rv?rdet och b?rv?rdet 
    e(k)=v-y(k);
    
    %u(k)=(diff(y)/diff(t)).*e(k);
     % Regulatorblock
     % ber?kna styrv?rdet, t.ex p-regulator med f?rst?rkning Kp=1
     u(k)=e(k); % p-regulator, Kp=1

    % begr?nsa styrv?rdet till l?mpliga v?rden, vattenmodellen t.ex. u >=0 och u <255, samt
    %      heltal
    u(k)=min(max([0, round(u(k)), 255]));
    
    % skriva ut styrv?rdet
    analogWrite(a,u(k), 'DAC1'); %DAC-utg?ng

    %online-plot
    plot(t,y,'k-',t,u,'m:',t,e,'b');
    

    elapsed=cputime-start; % r?knar ?tg?ngen tid i sekunder
    ok=(Ts-elapsed); % sparar tidsmarginalen i ok
    
    pause(ok); %pausar resterande samplingstid
  
end % slut av samplingarna ----------------------------------------------------------------------

% plotta en fin slutbild, 
  plot(t,y,'k-');%,,,t,u,'m:',t,e,'b');
  xlabel('samples k')
  ylabel('y')%, u ,e')
  title('xxx-regulator')
  legend('y ', 'u ', 'e ')

% -------------------------------------------------------------------------------------------

