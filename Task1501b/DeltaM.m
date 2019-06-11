function [ t, x, y, dm ] = DeltaM(filename)
%DeltaM
%   g�r en deltamodellering av en ljudfil
%
% ing�ng: filnamn �r textstring av ljudfil inkl. extension, t.ex
% 'test.mp3'
% utg�ng: dm-array med alla bin�ra styrv�rden
%           x-array som motsvarar delta-modulerade signalen

%Variabler:
N=700000; %antal f�rsta samples som tas fr�n ljudfil
h=0.008; %minsta kvantiseringsenhet normerad till 1.
yy=[]; Fs=0; y=[]; dm=[]; x=[]; k=0; compare[]; % variablerdeklaration som egentligen inte beh�vs i Matlab

[yy,Fs] = audioread('falukorv.mp3'); %laddar in en ljudfil och sparar v�rden i array "yy". Fs �r samplingsfrekvensen av ljudsignalen

%kolla att N inte �r st�rre �n yy �r l�ng
if N > length(yy)
    display('N �r st�rre �n antal samples. N har kortats ner!')
    N=length(yy);
end


y=yy(1:N); %ta f�rsta N samples bara
dm=0*y;
x=0*y;
compare = 0*y;
t=(1:N); %skapa en tidsvektor

% dm(k) r�knas ut som funktion av h(k-1) och y(k-1)
for k=2:(N-1)
	%skriv in era programrader h�r

  if compare(k) > yy(k)
    dm(k)=1;
    x(k)=x(k)+ h;
    compare(k)=yy(k);

  else
    dm(k)= 0;
    x(k)= x(k)-h;
    compare(k)=yy(k);

  end

end

%spela upp resulterande ljudfil x
sound(x,Fs);


end
