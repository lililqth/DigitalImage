I = imread('1.bmp');
I =rgb2gray(I);
subplot(121);
imshow(I);
title('ԭͼ');
BW4 = edge(I,'canny');
subplot(122);
imshow(BW4,[]);
title('Canny���ӱ�Ե���'); 