clear all;
T=0.01;
t=0:T:100;
x=cos(2*pi*0.01*t).*cos(2*pi*10*t+0.01*t);
n=-1000:1000;
N=length(n);
h=zeros(1,N);
for i=1:N
    if(mod(i,2) == 0) 
        h(i) = 2/pi/n(i);%希尔伯特变换器
    end
end
%%%%%%%%输入信号理论值%%%%%%%%
Ad=abs(cos(2*pi*0.01*t));%理论幅度
pd=atan2(sin(2*pi*10*t+0.01*t),cos(2*pi*10*t+0.01*t));%理论相位
for i=1:length(x)
    fd(i)=10+0.01/2/pi;%理论频率
end

%%%%%%%%矩形窗%%%%%%%%%%
[y1,A1,p1,f1]=cal_window(1,N,h,x);

%%%%%%%%%汉宁窗%%%%%%%%%
[y2,A2,p2,f2]=cal_window(2,N,h,x);

%%%%%%%%%汉明窗%%%%%%%%%
[y3,A3,p3,f3]=cal_window(3,N,h,x);

%%%%%%%%%凯瑟尔窗%%%%%%%%%
[y4,A4,p4,f4]=cal_window(4,N,h,x);

%%%%%%%%%布莱克曼窗%%%%%%%%%
[y5,A5,p5,f5]=cal_window(5,N,h,x);

figure(1)
subplot(4,5,1);
plot(t,y1);xlabel('时间');title('矩形窗输入输出信号');axis([50,50.5,-1.3,1.3]);hold on;
plot(t,x, 'r--' , 'linewidth' ,2);axis([50,50.5,-1.3,1.3]);
legend('计算','理论');
subplot(4,5,2);
plot(t,y2);xlabel('时间');title('汉宁窗输入输出信号');axis([50,50.5,-1.3,1.3]);hold on;
plot(t,x, 'r--' , 'linewidth' ,2);axis([50,50.5,-1.3,1.3]);
legend('计算','理论');
subplot(4,5,3);
plot(t,y3);xlabel('时间');title('汉明窗输入输出信号');axis([50,50.5,-1.3,1.3]);hold on;
plot(t,x, 'r--' , 'linewidth' ,2);axis([50,50.5,-1.3,1.3]);
legend('计算','理论');
subplot(4,5,4);
plot(t,y4);xlabel('时间');title('凯瑟尔窗输入输出信号');axis([50,50.5,-1.3,1.3]);hold on;
plot(t,x, 'r--' , 'linewidth' ,2);axis([50,50.5,-1.3,1.3]);
legend('计算','理论');
subplot(4,5,5);
plot(t,y5);xlabel('时间');title('布莱克曼窗输入输出信号');axis([50,50.5,-1.3,1.3]);hold on;
plot(t,x, 'r--' , 'linewidth' ,2);axis([50,50.5,-1.3,1.3]);
legend('计算','理论');

subplot(4,5,6);
plot(t,A1);title('包络幅度');axis([0,100,0,1.3]);hold on;
plot(t,Ad, 'r--' , 'linewidth' ,2);axis([0,100,0,1.3]);
legend('计算','理论');
subplot(4,5,7);
plot(t,A2);title('包络幅度');axis([0,100,0,1.3]);hold on;
plot(t,Ad, 'r--' , 'linewidth' ,2);axis([0,100,0,1.3]);
legend('计算','理论');
subplot(4,5,8);
plot(t,A3);title('包络幅度');axis([0,100,0,1.3]);hold on;
plot(t,Ad, 'r--' , 'linewidth' ,2);axis([0,100,0,1.3]);
legend('计算','理论');
subplot(4,5,9);
plot(t,A4);title('包络幅度');axis([0,100,0,1.3]);hold on;
plot(t,Ad, 'r--' , 'linewidth' ,2);axis([0,100,0,1.3]);
legend('计算','理论');
subplot(4,5,10);
plot(t,A5);title('包络幅度');axis([0,100,0,1.3]);hold on;
plot(t,Ad, 'r--' , 'linewidth' ,2);axis([0,100,0,1.3]);
legend('计算','理论');

subplot(4,5,11);
plot(t,p1);title('相位');axis([1,1.5,-3.15,3.15]);hold on;
plot(t,pd, 'r--' , 'linewidth' ,2);axis([1,1.5,-3.15,3.15]);
legend('计算','理论');
subplot(4,5,12);
plot(t,p2);title('相位');axis([1,1.5,-3.15,3.15]);hold on;
plot(t,pd, 'r--' , 'linewidth' ,2);axis([1,1.5,-3.15,3.15]);
legend('计算','理论');
subplot(4,5,13);
plot(t,p3);title('相位');axis([1,1.5,-3.15,3.15]);hold on;
plot(t,pd, 'r--' , 'linewidth' ,2);axis([1,1.5,-3.15,3.15]);
legend('计算','理论');
subplot(4,5,14);
plot(t,p4);title('相位');axis([1,1.5,-3.15,3.15]);hold on;
plot(t,pd, 'r--' , 'linewidth' ,2);axis([1,1.5,-3.15,3.15]);
legend('计算','理论');
subplot(4,5,15);
plot(t,p5);title('相位');axis([1,1.5,-3.15,3.15]);hold on;
plot(t,pd, 'r--' , 'linewidth' ,2);axis([1,1.5,-3.15,3.15]);
legend('计算','理论');

subplot(4,5,16);
plot(t,f1);title('瞬时频率');axis([0,100,-10,30]);hold on;
plot(t,fd, 'r--' , 'linewidth' ,2);axis([0,100,-10,30]);
legend('计算','理论');
subplot(4,5,17);
plot(t,f2);title('瞬时频率');axis([0,100,-10,30]);hold on;
plot(t,fd, 'r--' , 'linewidth' ,2);axis([0,100,-10,30]);
legend('计算','理论');
subplot(4,5,18);
plot(t,f3);title('瞬时频率');axis([0,100,-10,30]);hold on;
plot(t,fd, 'r--' , 'linewidth' ,2);axis([0,100,-10,30]);
legend('计算','理论');
subplot(4,5,19);
plot(t,f4);title('瞬时频率');axis([0,100,-10,30]);hold on;
plot(t,fd, 'r--' , 'linewidth' ,2);axis([0,100,-10,30]);
legend('计算','理论');
subplot(4,5,20);
plot(t,f5);title('瞬时频率');axis([0,100,-10,30]);hold on;
plot(t,fd, 'r--' , 'linewidth' ,2);axis([0,100,-10,30]);
legend('计算','理论');