function [y,A,p,f]=cal_window(k,N,h,x)
    T=0.01;
    switch k
        case 1
            window = ones(1,N);
        case 2
            window = hann(N)';
        case 3
            window = hamming(N)';
        case 4
            window = kaiser(N)';
        case 5
            window = blackman(N)';
    end
    
    hN=h.*window;
    y=conv(x,hN,'same');
    A=(abs(x).^2+abs(y).^2).^0.5;
    p=atan2(y,x);%º∆À„œ‡Œª
    q=x+1j*y;
    f = zeros(1,length(q));
    for i=1:length(f)-1
        f(i)=imag(2*(q(i+1)-q(i))./((q(i+1)+q(i))*T))/2/pi;
    end
    f(end)=p(end)/2/pi;