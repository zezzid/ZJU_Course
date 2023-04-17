clear;

fs=1;
ts=1/fs;

fin_pre=0.1;
nfft=2048;
fin=antismear(fin_pre,fs,nfft);

bits_number = 13;

open_system('pipeline_13bit')

sim('pipeline_13bit', 5000*ts);	% Starts Simulink simulation