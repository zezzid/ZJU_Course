clear all;
N=80;%阶数
f=[0.05 0.95];%设置带宽
m=[1 1];%理想滤波器的幅频特性
b=firpm(N,f,m,'h');%Hilbert变换器
dt=0.01;
t=0:dt:100;
x=cos(2*pi*0.01*t).*cos(2*pi*10*t+0.01*t);%输入信号
Ad=abs(cos(2*pi*0.01*t));

y=filter(b,1,x);%希尔伯特变换，得到的解析信号为x+1j*y;
A=(abs(x).^2+abs(y).^2).^0.5;%计算幅度

p=atan2(y,x);%计算相位
pd=atan2(sin(2*pi*10*t+0.01*t),cos(2*pi*10*t+0.01*t));%理论相位

q=x+1j*y;%解析信号
f = zeros(1,length(q));%计算频率
temp = diff(q);
for n=1:length(f)-1
    f(n)=imag(100*temp(n)/q(n))/2/pi;
end
f(end)=p(end)/2/pi;
for n=1:length(f)
    fd(n)=10+0.01/2/pi;%理论频率
end
figure(1)
subplot(4,1,1);
plot(t,y);xlabel('时间');title('输入输出信号');axis([48,50,-1.3,1.3]);hold on;
plot(t,x, 'r--' , 'linewidth' ,2);axis([48,50,-1.3,1.3]);
legend('计算','理论');

subplot(4,1,2);
plot(t,A);title('包络幅度');axis([0,100,0,1.3]);hold on;
plot(t,Ad, 'r--' , 'linewidth' ,2);axis([0,100,0,1.3]);
legend('计算','理论');

subplot(4,1,3);
plot(t,p);title('相位');axis([0,2,-3.15,3.15]);hold on;
plot(t,pd, 'r--' , 'linewidth' ,2);axis([0,2,-3.15,3.15]);
legend('计算','理论');

subplot(4,1,4);
plot(t,f);title('瞬时频率');axis([0,100,-10,30]);hold on;
plot(t,fd, 'r--' , 'linewidth' ,2);axis([0,100,-10,30]);
legend('计算','理论');

%%%%%%以下为利用MATLAB自带Hilbert变换求瞬时频率与前部分设计的滤波器求解的对比%%%%%
fs=100;
z = hilbert(x);
instfrq = fs/(2*pi)*diff(unwrap(angle(z)));


figure(2)
plot(t,f);title('瞬时频率对比');axis([0,100,-10,30]);hold on;
plot(t(2:end),instfrq, 'r--' , 'linewidth' ,2);axis([0,100,-10,30]);
legend('计算','理论');
