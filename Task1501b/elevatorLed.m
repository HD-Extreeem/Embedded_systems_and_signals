function elevatorLed(a)
pause on
dir=1;

a.pinMode(3,'OUTPUT');
a.digitalWrite(3,0);

a.pinMode(2,'OUTPUT');
a.digitalWrite(2,dir);

a.pinMode(7,'OUTPUT');
a.digitalWrite(7,0);

a.analogWrite(0);

startMeasure = 0;

pause(0.4);

goToCase = 0;
valuesLight = zeros(1,300);
valuesHeavy= zeros(301,600);
i = 1;
j = 1;
filename = 'data.xlsx';


while(1)
    
    %SAMLA MÄTVÄRDEN FÖR LÄTT VIKT
    if (startMeasure == 1)
        i=i+1;
        
        %GÖR OM MÄTVÄRDEN TILL mA
        valuesLight(i)=(a.analogRead('A0')/1024)*2000;
        
        %STANNA OM MÄTVÄRDEN FÖR MOTORSTRÖM ÖVERSTIGER 175 mA
        if valuesLight(i) >= 175
            a.digitalWrite(3,1);
            disp('Too heavy! Breaking!');
        end
    end
    
    %SAMLA MÄTVÄRDEN FÖR TUNG VIKT
    if (startMeasure == 2)
        j=j+1;
        
        %GÖR OM MÄTVÄRDEN TILL mA
        valuesHeavy(j)=(a.analogRead('A0')/1024)*2000;
        
        %STANNA OM MÄTVÄRDEN FÖR MOTORSTRÖM ÖVERSTIGER 175 mA
        if valuesHeavy(j) >= 175
            a.digitalWrite(3,1);
            disp('Too heavy! Breaking!');
        end
    end
    
    %NOTIFIERA OM ATT VÄRDENA FÖR LÄTT VIKT ÄR SAMLADE
    if i == 300
        disp('Done collecting the first 300 values');
    end
    
    %KOLLA OM ALLA VÄRDEN ÄR SAMLADE OCH RITA UT DEM
    if(i>=300 && j>=300)
        
        plot(valuesLight(1:300));
        hold on
        plot(valuesHeavy(1:300));
        title('Motorström för olika vikter')
        xlabel('Arrayindex')
        ylabel('mA')
        legend('Lätt vikt', 'Tung vikt', 'Location', 'southwest')
        a.analogWrite(0);
        xlswrite(filename,valuesLight(1:300),'A1:KN1');
        xlswrite(filename,valuesHeavy(1:300),'A2:KN2');
        break;
        
    end
    
    %Läs in knappingången
    btn = a.digitalRead(6);
    
    
    if btn == 1
        
        %ÅK NER
        if goToCase == 2
            a.analogWrite(200);
            goToCase = 3;
            
            %STANNA OCH STÄLL IN RIKTNING
        elseif goToCase == 3
            %    a.digitalWrite(7,0);
            a.analogWrite(0);
            dir=1;
            goToCase = 0;
            
            %ÅK UPP
        elseif goToCase == 0
            a.analogWrite(200);
            a.digitalWrite(7,1);
            
            startMeasure = startMeasure + 1;
            
            goToCase = 1;
            
            %STANNA OCH STÄLL IN RIKTNING
        elseif goToCase == 1
            dir=0;
            a.digitalWrite(7,0);
            a.analogWrite(0);
            goToCase = 2;
        end
        
        pause(0.2);
        a.digitalWrite(2,dir);
        
    end
        
end

end