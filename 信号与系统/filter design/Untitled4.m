clear all£»
T=0.01;
t=0:T:100;
x=cos(2*pi*0.01*t).*cos(2*pi*10*t+0.01*t);
simin=[t;x]';