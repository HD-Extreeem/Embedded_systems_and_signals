function motorDirChanger(a)
pause on
    dir=0;
    a.pinMode(3,'OUTPUT');
    a.digitalWrite(3,0);
    pause(0.5);
    
    a.pinMode(2,'OUTPUT');
    a.digitalWrite(2,0);
    
    pause(0.5);
    
    a.analogWrite(254);
    

while(1)
    btn = a.digitalRead(6);
    pause(0.2);
    
    if btn == 1
        
        if dir==0
            dir=1;   
        else
            dir=0;
        
        end
        disp(dir);
        pause(0.8);
        a.digitalWrite(2,dir);
    end    
end



end