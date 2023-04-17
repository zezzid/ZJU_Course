%%%%%%%%edited by lx on 20220203 for matrix form QM%%%%%%%
clc; clf; clear all;
h=6.626E-34;
h_bar=h/(2*pi);%%%约化普朗克常数
eV2J=1.60E-19;%%%能量转换1 eV=1.602E-19 J
J2eV=1/eV2J;%%能量转换 1J=1/(1.6E-19) eV
m_frele=9.109E-31;%%%粒子质量
delta_x=0.05E-9;%%%%%%%%%%%eigen state step in unit of meter；计算区域的分割步长(step)，单位为m，这里设定为50 pm，差不多氢原子玻尔半径
N=1002;%%%%计算区域总分割数量。总的计算区域大约50 nm。
x=((1:1:N)-N/2)*delta_x;%%生成一个数组，其中的元素按次序表示计算的格点坐标。[1 2 3 4 ... 1000 1001 1002]-501=[-500 -500 -499 -498...498 499 500 501]，再将其乘以步长50pm

potential=['sho','square','triangle'];%%%预设的三种势阱形状


kai=(-h_bar^2/(2*m_frele*delta_x^2));%%%%前置系数
T=kai*(-2*diag(ones(N,1))+diag(ones(N-1,1),1)+diag(ones(N-1,1),-1));%%%产生动能项。注意diag的使用方法。

type='DoubleWell'
switch type%%%%%量子系统用eV为能量标度比较方便。%%%可以仿照我的写法自行修改小v的定义，新建case
    case 'sho'%%%%简谐振子V=a*x^2
        v=eV2J*(20E18/625)*(x).^2;%%%%注意这里的.^用法，表示对数组内的每一个元素求平方。没有.的话会报错
        V=diag(v);%%%利用数组生成方阵
    case 'square'
        height=0.05;%%well depth in unit of eV。从顶部往下算的势阱深度（或者从底部往上算起的势垒高度，两者等价，只是参考零点不同），单位eV
        v=[height*ones(1,floor(N/4)) 0*ones(1,N-floor(N/4)*2) height*ones(1,floor(N/4))]*eV2J;%%%%这里将三个数组顺序拼接起来，语法为[a空格b空格c]；第一个和第三个数组对应上述一定高度的势垒，宽度为250step，第二个数组势能为0，宽度~500step
        V=diag(v);%%同上
    case 'triangle'
        v=linspace(0,2,N/2);%%%%linsapce函数生成了一个从0变化到2，总共501个元素的等差数列，作为半三角势垒的右半边。
        v=[ones(1,N/2)*10 v]*eV2J;%%%%%生成了一个高度为10 eV的等效无穷高势垒，并与上述半三角拼接。此例中，三角势垒延申到计算区域边缘，总宽度为500个step。边缘势垒高度（第500个step处）为2eV
        V=diag(v);%%同上
    case 'DoubleWell'
        width1=40E-9;%%%%%总宽度 单位m
        N1=floor(width1/delta_x);
        width2=0.05E-9%%%中间势垒宽度 单位nm
        N2=floor(width2/delta_x);
        height1=1;%%well depth in unit of eV。从顶部往下算的势阱深度（或者从底部往上算起的势垒高度，两者等价，只是参考零点不同），单位eV
        height2=1;%%%中间势垒高度，单位eV
        v1=[height1*ones(1,floor((N-N1)/2)) 0*ones(1,N-2*floor((N-N1)/2)) height1*ones(1,floor((N-N1)/2))]*eV2J;%%%%这里将三个数组顺序拼接起来，语法为[a空格b空格c]；第一个和第三个数组对应上述一定高度的势垒，宽度为250step，第二个数组势能为0，宽度~500step
        v2=[0*ones(1,floor((N-N2)/2)) height2*ones(1,N-2*floor((N-N2)/2)) 0*ones(1,floor((N-N2)/2))]*eV2J;
        v=v1+v2;
        V=diag(v);%%同上
        
    otherwise
        warning('No such potential type.')
end

H=T+V;%%生成哈密顿矩阵
[phi,E]=eig(H);%%求本征值和本征向量，注意E返回一个方阵，对角元素是特征值，为了方便，下面再产生一个e
e=eig(H);%%%求特征值，返回到e中
        
        
% x=0:0.001:0.100;
% plot(x,y),ylabel('\DeltaE=E_0-E_1(meV)'),xlabel('耦合势垒高度(eV)')
%%%%%%%%%%%%%%plot 画图
for i=1:1:4%%%循环画图，前4个
    subplot(2,4,i)%%%2行5列，第i个子图
    
    plot(x*1E9,phi(:,i));%%%波函数，横坐标为位置，单位nm
    xlim([min(x*1E9) max(x*1E9)]);
    legend(['E_' num2str(i,1) '=' num2str(e(i)*J2eV*1000,4) 'meV']);
    xlabel('position (nm)')
    ylabel('\psi')
    subplot(2,4,4+i)
    plot(x*1E9,abs(phi(:,i)).^2);%%%波函数模平方，横坐标为位置，单位nm
    xlabel('position (nm)')
    ylabel('|\psi|^2')
    
    yyaxis right
    plot(x*1E9,v*J2eV,'k');%%画出势垒的形状供参考
    hold on
    yyaxis right
    plot(x*1E9,e(i)*J2eV*ones(length(x),1),'r--');%%%本征值用红色虚线画出来
    
    ylim([0 0.1])
    hold off 
    xlim([min(x*1E9) max(x*1E9)]);
    ylabel('potential (eV)')
end

%%%%%%%%%%%%%T2
% aa=[0 1 2 3];
% m1=phi(:,1);
% m2=phi(:,2);
% m3=phi(:,3);
% m4=phi(:,4);
% mm0=[m1'*m1;m1'*m2;m1'*m3;m1'*m4];
% mm1=[m2'*m1;m2'*m2;m2'*m3;m2'*m4];
% mm2=[m3'*m1;m3'*m2;m3'*m3;m3'*m4];
% mm3=[m4'*m1;m4'*m2;m4'*m3;m4'*m4];
% bb=[mm0 mm1 mm2 mm3];
% bar3(bb),xlabel('n'),ylabel('m'),zlabel('\psi_m*\psi_n')


