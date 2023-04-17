clc,clear
A = imread('lenna.jpg');
A = double(A);

M1 = 1/9 * [1 1 1;1 1 1;1 1 1];
M2 = -1/9 * [1 1 1;1 -8 1;1 1 1];
I1 = convnew2(A,M1);
I2 = convnew2(A,M2);
figure(1);
subplot(1,2,1);imshow(uint8(I1));
subplot(1,2,2);imshow(uint8(I2));
imwrite(uint8(I1),'test1.bmp');
imwrite(uint8(I2),'test2.bmp');