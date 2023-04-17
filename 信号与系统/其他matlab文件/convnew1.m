function y = convnew1(x,h)
    t=tic;
    lx=length(x);
    lh=length(h);
    C = zeros(1,lx + lh-1);
    x = [zeros(1,lh-1),x,zeros(1,lh-1)];
    for i = 1:lx + lh-1
        for j = 1:lh
            C(i)=C(i)+h(j)*x(i+lh-j);
        end
    end
    toc(t);
end

