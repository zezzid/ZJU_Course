clear all;
N = 15;
Np = 1000;

window = ones(1,N);
window = [window,zeros(1,Np-length(window))];
y=fftshift(fft(window));
subplot(5,2,1);plot(window);title('¾ØÐÎ´°Ê±Óò');xlim([0 20]);
subplot(5,2,2);plot(abs(y));title('¾ØÐÎ´°ÆµÓò');

window = hann(N)';
window = [window,zeros(1,Np-length(window))];
y=fftshift(fft(window));
subplot(5,2,3);plot(window);title('ººÄþ´°Ê±Óò');xlim([0 20]);
subplot(5,2,4);plot(abs(y));title('ººÄþ´°ÆµÓò');

window = hamming(N)';
window = [window,zeros(1,Np-length(window))];
y=fftshift(fft(window));
subplot(5,2,5);plot(window);title('ººÃ÷´°Ê±Óò');xlim([0 20]);
subplot(5,2,6);plot(abs(y));title('ººÃ÷´°ÆµÓò');

window = kaiser(N)';
window = [window,zeros(1,Np-length(window))];
y=fftshift(fft(window));
subplot(5,2,7);plot(window);title('¿­Éª¶û´°Ê±Óò');xlim([0 20]);
subplot(5,2,8);plot(abs(y));title('¿­Éª¶û´°ÆµÓò');

window = blackman(N)';
window = [window,zeros(1,Np-length(window))];
y=fftshift(fft(window));
subplot(5,2,9);plot(window);title('²¼À³¿ËÂü´°Ê±Óò');xlim([0 20]);
subplot(5,2,10);plot(abs(y));title('²¼À³¿ËÂü´°ÆµÓò');
