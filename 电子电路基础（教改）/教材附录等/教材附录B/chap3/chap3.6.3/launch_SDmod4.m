%++++++++++++++++++++++++++++++++++++++++++++++++%
% 　　模拟电路基础——从系统级到电路级             %
%++++++++++++++++++++++++++++++++++++++++++++++++%
% 　　　　　陈抗生　周金芳                       %
%++++++++++++++++++++++++++++++++++++++++++++++++%
% 　　　　 科学出版社　2020                      %
%++++++++++++++++++++++++++++++++++++++++++++++++%
%
% 4th-order CIFF sigma-delta modulator
%
clear; close all;

% parameter
% OSR=128 fs=6.144MHz
% ftest=17  (=12.75kHz)
% fB=32     (=24kHz)
OSR=128; order=4; M=1;
N = 2^13;
ftest=17; fB=32;

ntf = synthesizeNTF(order,OSR,0);
figure(1);
plotPZ(ntf);
title('Figure 3.6.18')

form = 'CIFF';
swing = 0.2; %Amplifier output swing, Vp
umax = 0.9*M; %Scale system for inputs up to 0.9 of full-scale
[a,g,b,c] = realizeNTF(ntf,form);
b(2:end) = 0;
ABCD = stuffABCD(a,g,b,c,form);
ABCD = scaleABCD(ABCD,M+1,ftest/N,swing,[],umax);
[a,g,b,c] = mapABCD(ABCD,form);

% plot NTF and STF
figure(2); clf;
[Ha Ga]=calculateTF(ABCD);
f=linspace(0,0.5,100);
z=exp(2i*pi*f);
magHa=dbv(evalTF(Ha,z));
magGa=dbv(evalTF(Ga,z));
semilogx(f,magHa,'b',f,magGa,'m','Linewidth',1);
legend('NTF','STF','Location','southeast');
xlabel('Normalized Frequency');
ylabel('dB')
grid on;
title('Figure 3.6.19')

[snr_pred,amp_pred] = predictSNR(ntf,OSR);
[snr,amp] = simulateSNR(ntf,OSR);
[pk_snr pk_amp] = peakSNR(snr,amp);
figure(3);
plot(amp,snr,'ob-');
xlabel('Input Level (dBFS)');
ylabel('SQNR (dB)');
grid on;
text(-20,120,sprintf('peak SNR = %4.1fdB\n',pk_snr),'Hor','right');
title('Figure 3.6.20')

t0=clock;

% ************************************************************************
% Global variables
% ************************************************************************
bw=24e3;            % Base-band
Fs=OSR*2*bw;        % Oversampling frequency
Ts=1/Fs;
nper=ftest;
Fin=nper*Fs/N;      % Input signal frequency (Fin = nper*Fs/N)
Ampl=0.5;           % Input signal amplitude [V]
Ntransient=10;
Amax=1;             % Op-amp saturation value [V]
NCOMPARATORI=1;     % 1 bit quantizer

% NOT USED BUT must be defined 
Cs=2.5e-12;         % Integrating Capacitance of the first integrator
match=9e-10;        % Realistic value, but not related to any technology (because of non disclosure agreement)
% ************************************************************************

% Modulator coefficients

finrad=Fin*2*pi;    % Input signal frequency in radians

s0=sprintf('** Simulation Parameters **');
s1=sprintf('   Fs(Hz)=%1.0f',Fs);
s2=sprintf('   Ts(s)=%1.6e',Ts);
s3=sprintf('   Fin(Hz)=%1.4f',Fin);
s4=sprintf('   BW(Hz)=%1.0f',bw);
s5=sprintf('   OSR=%1.0f',OSR);
s6=sprintf('   Npoints=%1.0f',N);
s7=sprintf('   tsim(sec)=%1.3f',N/Fs);
s8=sprintf('   Nperiods=%1.3f',N*Fin/Fs);
disp(s0)
disp(s1)
disp(s2)
disp(s3)
disp(s4)
disp(s5)
disp(s6)
disp(s7)
disp(s8)
% ************************************************************************
% open Simulink diagram and simulate
% ************************************************************************
open_system('SDmod4')
options=simset('InitialState', zeros(1,5), 'RelTol', 1e-3, 'MaxStep', 1/Fs);
set_param('SDmod4','InitInArrayFormatMsg', 'None');	% Disable warning on model initialization
sim('SDmod4', (N+Ntransient)/Fs, options);  % Starts Simulink simulation

% plot output spectrum, calculate SNR
w=hann_pv(N);
f=Fin/Fs;               % Normalized signal frequency
yy1=zeros(1,N);
yy1=yout(2+Ntransient:1+N+Ntransient)';

ptot=zeros(1,N);
[snr,ptot]=calcSNR(yy1(1:N),f,1,fB,w,N);
Rbit=(snr-1.76)/6.02;  % Equivalent resolution in bits

figure(4);clf;
semilogx(linspace(0,Fs/2,N/2), ptot(1:N/2), 'r');
grid on;
title('PSD of a 4th-Order Sigma-Delta Modulator')
xlabel('Frequency (Hz)')
ylabel('PSD (dB)')
axis([0 Fs/2 -200 0]);
text_handle = text(floor(Fs/OSR),-20, sprintf('SNR = %4.1fdB @ OSR=%d\n',snr,OSR));
text_handle = text(floor(Fs/OSR),-40, sprintf('ENOB = %2.2f bits @ OSR=%d\n',Rbit,OSR));

%  
s1=sprintf('   SNR(dB)=%1.3f',snr);
s2=sprintf('   ENOB = %2.2f bits @ OSR=%d\n',Rbit,OSR);
s3=sprintf('   Simulation time =%1.3f min',etime(clock,t0)/60);
disp(s1)
disp(s2)
disp(s3)

% plot integrator output
figure(5); clf;
t = 0:4000;
subplot(6,1,1), plot(t,y0(1:4001))
axis([0 4000 -1.2 1.2]);
title('Output');
subplot(6,1,2), plot(t,y1(1:4001))
title('Figure 3.6.24');
axis([0 4000 -swing swing]);
subplot(6,1,3), plot(t,y2(1:4001))
axis([0 4000 -swing swing]);
subplot(6,1,4), plot(t,y3(1:4001))
axis([0 4000 -swing swing]);
subplot(6,1,5), plot(t,y4(1:4001))
axis([0 4000 -swing swing]);
subplot(6,1,6), plot(t,yout(1:4001))
axis([0 4000 -1.2 1.2]);
xlabel('Sample Number');


% plot histgram of integrator output
figure(6)
nbins=200;
[bin1,xx1]=histo(y1, nbins);
[bin2,xx2]=histo(y2, nbins);
[bin3,xx3]=histo(y3, nbins);
[bin4,xx4]=histo(y4, nbins);
clf;
subplot(2,2,1), plot(xx1, bin1)
grid on;
title('First Integrator Output')
xlabel('Voltage [V]')
ylabel('Occurrences')
subplot(2,2,2), plot(xx2, bin2)
grid on;
title('Second Integrator Output')
xlabel('Voltage [V]')
ylabel('Occurrences')
subplot(2,2,3), plot(xx3, bin3)
grid on;
title('Third Integrator Output')
xlabel('Voltage [V]')
ylabel('Occurrences')
subplot(2,2,4), plot(xx4, bin4)
grid on;
title('Fourth Integrator Output')
xlabel('Voltage [V]')
ylabel('Occurrences')