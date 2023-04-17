syms C R Rf Vi s;
A = [2*s*C+1/R, -s*C, 0;...
    s*C, -s*C-1/R-s*C/(1+s*C*R), 0;...
    0, s*C/(1+s*C*R), 1/Rf];
B = [s*C*Vi; 0; 0];
V = A\B;
Vo = V(3);
H = simplify(Vo/Vi);
%%
% a = R*C; b = Rf/R;
a = 2e-7;b = 30;
num = [-a^3*b, 0, 0, 0];
den = [a^3, 6*a^2, 5*a, 1];
figure(1);
bode(tf(num, den));