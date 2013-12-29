%小波变换
X = imread('1.bmp');

figure(1);
imshow(X);title('原始图像');

[cA,cH,cV,cD] = dwt2(X,'db1');

figure(2);

subplot(2,2,1),imshow(cA),title('cA');

subplot(2,2,2),imshow(cH),title('cH');

subplot(2,2,3),imshow(cV),title('cV');

subplot(2,2,4),imshow(cD),title('cD');

X1 = idwt2(cA,cH,cV,cD,'db1');
figure(3);
imshow(X1,[]);
title('重构图像');