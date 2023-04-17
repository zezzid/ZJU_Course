%%%%%%%%edited by lx on 20220316 for matrix form band structure calculation%%%%%%%
clc; clf; clear all;
h=6.626E-34;
h_bar=h/(2*pi);%%%约化普朗克常数
eV2J=1.60E-19;%%%能量转换1 eV=1.602E-19 J
J2eV=1/eV2J;%%能量转换 1J=1/(1.6E-19) eV
m_frele=9.109E-31;%%%粒子质量
delta_x=0.5E-12;%%%%%%%%%%%eigen state step in unit of meter；计算区域的分割步长(step)，单位为m，这里设定为0.5 pm，差不多0.01倍氢原子玻尔半径
N=300;%%%%计算区域为一个晶格周期，大小是150pm(化学键长度)。
p=N*delta_x;
kp_list=linspace(-pi,pi,100);
x=((1:1:N)-N/2)*delta_x;%%生成一个数组，其中的元素按次序表示计算的格点坐标。[1 2 3 4 ... 100]-50=[ -49 -48...48 49 50]，再将其乘以步长5pm
E_K=zeros(5,length(kp_list));%%%%前5个能带的E-K关系暂存
kai=(-h_bar^2/(2*m_frele*delta_x^2));%%%%前置系数
T=kai*(-2*diag(ones(N,1))+diag(ones(N-1,1),1)+diag(ones(N-1,1),-1));%%%产生动能项。注意diag的使用方法。
type='K_P';
switch type%%%%%量子系统用eV为能量标度比较方便。%%%可以仿照我的写法自行修改小v的定义，新建case
    case 'K_P'%%%%周期方势阱模型
        height=50;%well depth in unit of eV。从顶部往下算的势阱深度（或者从底部往上算起的势垒高度，两者等价，只是参考零点不同），单位eV
        aN=150;
        bN=N-aN;
        a=aN*delta_x;
        b=bN*delta_x;
        vb=eV2J*(height)*ones(1,bN);
        va=eV2J*(0)*ones(1,aN);
        v=[vb va];
        V=diag(v);%%%利用数组生成方阵
    case 'Coul'%%%%假想的一维库伦势能
        epsilon=8.85E-12;%%真空介电常数
        q=1.6021E-19;%%电子电荷
        v=-(q*q)./(4*pi*epsilon*abs(x-0.15E-12).^1);%%%不要将电荷的中心位置设置在格点上，避免无穷大.距离依赖关系可能不是1次方
        V=diag(v);%%%利用数组生成方阵
    case 'delta'%%%%PK模型b->0, U->inf极限
        height=1000;%well depth in unit of eV。从顶部往下算的势阱深度（或者从底部往上算起的势垒高度，两者等价，只是参考零点不同），单位eV
        aN=290;
        bN=N-aN;
        a=aN*delta_x;
        b=bN*delta_x;
        vb=eV2J*(height)*ones(1,bN);
        va=eV2J*(0)*ones(1,aN);
        v=[vb va];
        V=diag(v);%%%利用数组生成方阵
    otherwise
        warning('No such potential type.')
end
H=T+V;%%生成哈密顿矩阵

for ii=1:1:length(kp_list)
    H(1,N)=kai*exp(1i*kp_list(ii));%%%%布洛赫定理给出周期性边界条件1
    H(N,1)=kai*exp(-1i*kp_list(ii));%%%%%%%%布洛赫定理给出周期性边界条件2
    [phi,E]=eig(H);%%求本征值和本征向量，注意E返回一个方阵，对角元素是特征值，为了方便，下面再产生一个e
    e=eig(H);%%%求特征值，返回到e中。
    E_K(:,ii)=J2eV*real(e(1:5));%%%%将前5个特征值保存到E_K的第ii列中
end
figure(1)
%plot(kp_list,E_K(1,:))

%plot(kp_list(2:100),diff(E_K(1,:))./diff(kp_list))
%hold on
%plot(kp_list(3:100),diff(diff(E_K(1,:))./diff(kp_list))./diff(kp_list(2:100)))
plot(kp_list(3:100),h_bar^2*1./(diff(diff(E_K(1,:))./diff(kp_list))./diff(kp_list(2:100))))
xlabel('k*p');
ylabel('m(k*p)');


%%%%%%%%%%%画出kp=pi（布里渊区边界）附近的波函数模平方
% figure(2)
% subplot(2,2,1)
% plot(x*1E9,abs(phi(:,1)).^2);
% yyaxis right
% plot(x*1E9,v*J2eV,'r');%%画出势垒的形状供参考
% xlim([min(x*1E9) max(x*1E9)]);
% legend(['E_1=' num2str(e(1)*J2eV,3) 'eV']);
% 
% subplot(2,2,2)
% plot(x*1E9,abs(phi(:,2)).^2);
% yyaxis right
% plot(x*1E9,v*J2eV,'r');%%画出势垒的形状供参考
% xlim([min(x*1E9) max(x*1E9)]);
% legend(['E_2=' num2str(e(2)*J2eV,3) 'eV']);
% 
% subplot(2,2,3)
% plot(x*1E9,abs(phi(:,3)).^2);
% yyaxis right
% plot(x*1E9,v*J2eV,'r');%%画出势垒的形状供参考
% xlim([min(x*1E9) max(x*1E9)]);
% legend(['E_3=' num2str(e(3)*J2eV,3) 'eV']);
% 
% subplot(2,2,4)
% plot(x*1E9,abs(phi(:,4)).^2);
% xlabel('X position (nm)')
% ylabel('|psi|^2')
% yyaxis right
% plot(x*1E9,v*J2eV,'r');%%画出势垒的形状供参考
% xlim([min(x*1E9) max(x*1E9)]);
% ylabel('potential energy (eV)')
% legend(['E_4=' num2str(e(4)*J2eV,3) 'eV']);
% 
% 
% 
% 
% 
