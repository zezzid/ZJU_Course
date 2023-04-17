%++++++++++++++++++++++++++++++++++++++++++++++++%
% 　　模拟电路基础——从系统级到电路级             %
%++++++++++++++++++++++++++++++++++++++++++++++++%
% 　　　　　陈抗生　周金芳                       %
%++++++++++++++++++++++++++++++++++++++++++++++++%
% 　　　　 科学出版社　2020                      %
%++++++++++++++++++++++++++++++++++++++++++++++++%
%
% 3bit flash ADC
%
fs=1; ts=1/fs;

fin_pre=0.1;
nfft=2048;
fin=antismear(fin_pre,fs,nfft);

open_system('flash_3bit')

sim('flash_3bit', 3000*ts);	% Starts Simulink simulation