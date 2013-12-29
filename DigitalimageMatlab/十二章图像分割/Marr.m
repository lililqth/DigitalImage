I = imread('1.bmp');
I =rgb2gray(I);
subplot(121);
imshow(I);
title('Ô­Í¼');
BW4 = edge(I,'log');
subplot(122);
imshow(BW4,[]);
title('MARRËã×Ó±ßÔµ¼ì²â'); 