%++++++++++++++++++++++++++++++++++++++++++++++++%
% 　　模拟电路基础——从系统级到电路级             %
%++++++++++++++++++++++++++++++++++++++++++++++++%
% 　　　　　陈抗生　周金芳                       %
%++++++++++++++++++++++++++++++++++++++++++++++++%
% 　　　　 科学出版社　2020                      %
%++++++++++++++++++++++++++++++++++++++++++++++++%
%
% 12bit pipeline ADC
%
clear;

fs=1;
ts=1/fs;

fin_pre=0.1;
nfft=2048;
fin=antismear(fin_pre,fs,nfft)

bits_number = 12;

open_system('pipeline_12bit')

sim('pipeline_12bit', 5000*ts);	% Starts Simulink simulation