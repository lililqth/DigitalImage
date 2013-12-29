%This file is to implement histogram equlization
originalImage = imread('1.bmp');%这个图像是四维的（M*N*4），需要转换成灰度图

%先取出图像的前三维数据（丢弃第四维）并将其合成RGB图像
R = originalImage(:,:,1);
G = originalImage(:,:,2);
B = originalImage(:,:,3);

rgbImage = cat(3,R,G,B);
grayImage = rgb2gray(rgbImage);
%显示图像
figure,imshow(grayImage);
title('Original Image');
%计算图像的像素个数
numOfPixels = size(grayImage,1) * size(grayImage,2);

frequency = zeros(256,1);%用于统计各个灰度出现的次数
probability = zeros(256,1);%计算出现的可能性

for i=1:size(grayImage,1)
    for j=1:size(grayImage,2)
       value = grayImage(i,j);
       frequency(value+1) = frequency(value+1) + 1;
       probability(value+1) = frequency(value+1) / numOfPixels;
    end
end

cum = zeros(256,1);%记录各个像素值的累积分布
probc = zeros(256,1);%记录各个像素值的累积分布的可能性
output = zeros(256,1);%与那图像中各个灰度值的均衡化之后的值
sum = 0;
numOfBins = 255;

for i=1:size(probability)
    sum = sum + frequency(i);
    cum(i) = sum;
    probc(i) = cum(i) / numOfPixels;
    output(i) = round(probc(i) * numOfBins);
end

HEImage = uint8(zeros(size(grayImage,1),size(grayImage,2)));%均衡化后的图像
for i=1:size(grayImage,1)
    for j=1:size(grayImage,2)
        HEImage(i,j) = output(grayImage(i,j)+1);
    end
end

figure,imshow(HEImage);
title('Histogram Equalization');

