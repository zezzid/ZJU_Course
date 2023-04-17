clear all;
N=72;%阶数
f=[0.05 0.95];%带宽
m=[1 1];%幅频特性
fs=2000;%采样频率
b=firpm(N,f,m,'h');%采用Parks-McClellan方法设计Hilbert变换器
[H,w]=freqz(b,1,512,fs);%计算Hilbert变换器的脉冲响应
subplot(2,1,1);plot(w,20*log10(abs(H)));axis([0,1000,-30,10]);xlabel('频率/Hz');ylabel('幅值/dB');title('离散希尔伯特变换器幅频特性');
subplot(2,1,2);plot(w,angle(H)/pi*180);xlabel('频率/Hz');ylabel('相角');title('离散希尔伯特变换器相频特性');
