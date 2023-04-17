%%%%%%%%edited by lx on 20220203 for matrix form QM%%%%%%%
clc; clf; clear all;
h=6.626E-34;
h_bar=h/(2*pi);
eV2J=1.60E-19;
J2eV=1/eV2J;
m_frele=9.109E-31;
delta_x=0.05E-9;%%%%%%%%%%%eigen state step
ee=[];eee=[];delta_e=[];
N=402:400:8002;
for i=1:1:3
    subplot(3,1,i)
    for j=1:1:20
        n=N(j);
        x=((1:1:n)-n/2)*delta_x;
        potential=['sho','square','triangle'];
        
        kai=(-h_bar^2/(2*m_frele*delta_x^2));
        T=kai*(-2*diag(ones(n,1))+diag(ones(n-1,1),1)+diag(ones(n-1,1),-1));
        
        type='square'
        switch type
            case 'sho'
                v=eV2J*(20E18/625)*(x).^2;%%%可以仿照我的写法自行修改小v的定义，新建case
                V=diag(v);
            case 'square'
                height=1;%%well depth in unit of eV
                v=[height*ones(1,floor(n/4)) 0*ones(1,n-floor(n/4)*2) height*ones(1,floor(n/4))]*eV2J;
                V=diag(v);
            case 'triangle'
                v=linspace(0,2,N/2);
                v=[ones(1,N/2)*10 v]*eV2J;
                V=diag(v);
            otherwise
                warning('No such potential type.')
        end
        H=T+V;
        [phi,E]=eig(H);
        e=eig(H);
        
        
        ee(j)=e(1,:);
        eee(j)=e(2,:);
        delta_e(j)=e(2,:)-e(1,:);
        %
        % %%%%%%%%%%%%%%plot
        % for i=1:1:4
        %     subplot(2,5,i)
        %     plot(x*1E9,phi(:,i));
        %     xlim([min(x*1E9) max(x*1E9)]);
        %     legend(['E_' num2str(i,1) '=' num2str(e(i)*J2eV*1000,3) 'meV']);
        %     %subplot(2,5,5+i)
        %     %plot(x*1E9,abs(phi(:,i)).^2);
        %
        %
        %     yyaxis right
        %     plot(x*1E9,v*J2eV,'k');
        %     hold on
        %     yyaxis right
        %     plot(x*1E9,e(i)*J2eV*ones(length(x),1),'r--');
        %     ylim([0 1])
        %     hold off
        %     xlim([min(x*1E9) max(x*1E9)]);
        % end
    end
    
    if i==1
        plot(floor(N/2)*0.05,ee*J2eV*1000);xlim([10 200]);ylabel('E_1(meV)');
    elseif i==2
        plot(floor(N/2)*0.05,eee*J2eV*1000);xlim([10 200]);ylabel('E_2(meV)');
    else
        plot(floor(N/2)*0.05,delta_e*J2eV*1000);xlim([10 200]);ylabel('ΔE(meV)');
    end
    
        
end



