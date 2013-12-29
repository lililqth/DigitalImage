clear all;
RGB=imread('1.bmp');
figure(1);imshow(RGB);title('原始图像');
I=rgb2gray(RGB);
D=dct2(I);
figure(2);imshow(log(abs(D)),[]);colormap(jet(64));colorbar;
title('离散余弦变换结果');