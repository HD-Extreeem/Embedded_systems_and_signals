function lock( a )
%LOCK Summary of this function goes here
%   Detailed explanation goes here
nextState = 'locked';
currentState = nextState;

a.pinMode(2,'INPUT');%btn 1
a.pinMode(3,'INPUT');%btn 2
a.pinMode(4,'INPUT');%btn 3

a.pinMode(6,'OUTPUT');% led 1
a.pinMode(7,'OUTPUT');% led 2
a.pinMode(8,'OUTPUT');% led 3
a.pinMode(9,'OUTPUT');% Bigled 4

a.digitalWrite(6,0);
a.digitalWrite(7,0);
a.digitalWrite(8,0);
a.digitalWrite(9,0);
tries = 0;



%   k1=~a.digitalRead(2);
%  k2=~a.digitalRead(3);
%   k3=~a.digitalRead(4);


while(1)
    
    
    if (tries >=3)
        a.digitalWrite(6,0);
        a.digitalWrite(7,0);
        a.digitalWrite(8,0);
        a.digitalWrite(9,0);
        
        
        disp('too many failed tries');
        
        break;
    end
    
    
    
    k1=~a.digitalRead(2);
    k2=~a.digitalRead(3);
    k3=~a.digitalRead(4);
    
    if k1 | k2 | k3
       buttonPressed = 1;
    end
    
    
    
    if k1
        disp('knapp1')
    end
    
    if k2
        disp('knapp2')
    end
    
    if k3
        disp('knapp3')
    end
    
    switch currentState
        case {'changepass'}
            
        case{'locked'}
            %  disp('locked');
            a.digitalWrite(6,0);
            a.digitalWrite(7,0);
            a.digitalWrite(8,0);
            a.digitalWrite(9,0);
            
            
            
            if k2 & ~(k1 | k3)
                %  disp('ska bli push1');
                nextState = 'push1';
            end
            
            if k1 | k3
                nextState = 'go2locked';
            end
        case{'push1'}
            %  disp('push1');
            
            if k2 & ~(k1 | k3)
                nextState = 'push1';
                
            elseif ~k2 & ~(k1 | k3)
                nextState = 'release1';
            end
            
            if k1 | k3
                nextState = 'go2locked';
            end
        case{'release1'}
            %  disp('release1');
            if ~k2 & ~(k1 | k2)
                a.digitalWrite(6,1);
            end
            
            if k1 | k2
                nextState = 'go2locked';
            end
            
            if k3 & ~(k1 | k2)
                nextState = 'push2';
            end
        case{'push2'}
            disp('push2');
            if k3 & ~(k1 | k2)
                nextState = 'push2';
            end
            
            if ~k3 & ~(k1 | k2)
                nextState = 'release2';
            end
            
            if k1 | k2
                nextState = 'go2locked';
            end
            
        case{'release2'}
            %   disp('release2');
            if ~k3 & ~(k1 | k2)
                a.digitalWrite(7,1);
            end
            
            
            
            if k1 & ~(k2 | k3)
                nextState = 'push3';
            end
            
            if k2 | k3
                nextState = 'go2locked';
            end
            
            
        case{'push3'}
            
            if k1 & ~(k2 | k3)
                nextState = 'push3';
            end
            
            if ~k1 & ~(k2 | k3)
                nextState = 'release3';
                
            end
            
            if k2 | k3
                nextState = 'go2locked';
            end
            
        case{'release3'}
            
            if ~k1 & ~(k2 | k3)
                a.digitalWrite(8,1);
                nextState = 'release3';
            end
            
            if k2 & ~(k1 | k3)
                nextState = 'push4';
                
            end
            
            if k1 | k3
                nextState = 'go2locked';
            end
            
            
        case{'push4'}
            if k2 & ~(k1 | k3)
                nextState = 'push4';
                
            end
            
            if ~k2 & ~(k1 | k3)
                nextState = 'open';
                
            end
            
            if k1 | k3
                nextState = 'go2locked';
            end
            
        case{'open'}
            if ~(k2 | k1 | k3)
                nextState = 'open';
            elseif (k2 | k1 | k3)
                nextState = 'go2locked';
            end
            
            a.digitalWrite(6,0);
            a.digitalWrite(7,0);
            a.digitalWrite(8,0);
            a.digitalWrite(9,1);
            
            
        case{'go2locked'}
            
            if k2 | k1 | k3
                nextState = 'go2locked';
            end
            
            if ~(k2 | k1 | k3)
                tries = tries+1;
                nextState = 'locked';
            end
    end
    currentState=nextState;
end



end

