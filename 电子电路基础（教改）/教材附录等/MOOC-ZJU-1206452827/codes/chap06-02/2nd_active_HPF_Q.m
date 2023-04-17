%-----------------------------------------------
% 　　　　模拟电路基础：                        
% 　　　　　　从系统级到电路级                  
%-----------------------------------------------
%　　　　陈抗生，周金芳                        
%　　　　科学出版社　2019                      
%-----------------------------------------------
%　　　　中国大学MOOC: 
%  https://www.icourse163.org/course/ZJU-1206452827
%-----------------------------------------------
%
%　　　　参见PPT第15页

% R=20k, C=0.01uF
R=20e3; C=0.01e-6; wn=1/R/C;
% Rf=10k, 15k 20k, 25k, 30k
Rf=[10e3 15e3 20e3 25e3 30e3];
u=1+Rf/R; Q=1./(3-u)

% frequency range
f=logspace(2,4,101);
% reciprocal of normalzed w ( = 2*pi*f/wn )
w=(wn./(f*2*pi));		

for i=1:5
	% this is |H(jw)|
	hw(:,i)= u(i) ./ sqrt( (w.*w-1).^2+(w/Q(i)).^2 ) ;
end;

semilogx(f,hw); grid on;
legend('Q= 0.67','Q= 0.80','Q= 1.00','Q= 1.33','Q= 2.00')
xlabel('f (Hz)'); ylabel('|H(j\omega)|');