clear all;
RGB=imread('1.bmp');
figure(1);imshow(RGB);title('ԭʼͼ��');
I=rgb2gray(RGB);
D=dct2(I);
figure(2);imshow(log(abs(D)),[]);colormap(jet(64));colorbar;
title('��ɢ���ұ任���');