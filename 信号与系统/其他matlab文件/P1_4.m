k =1;
omega = 2;
[z,t] = meshgrid(0:0.01:10, 0:0.01:10);
wave =cos(k*z - omega*t);
pcolor(t,z,wave);shading flat;colorbar;
xlabel('t');ylabel('z');axis square