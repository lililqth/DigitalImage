%This file is to implement histogram equlization
originalImage = imread('1.bmp');%���ͼ������ά�ģ�M*N*4������Ҫת���ɻҶ�ͼ

%��ȡ��ͼ���ǰ��ά���ݣ���������ά��������ϳ�RGBͼ��
R = originalImage(:,:,1);
G = originalImage(:,:,2);
B = originalImage(:,:,3);

rgbImage = cat(3,R,G,B);
grayImage = rgb2gray(rgbImage);
%��ʾͼ��
figure,imshow(grayImage);
title('Original Image');
%����ͼ������ظ���
numOfPixels = size(grayImage,1) * size(grayImage,2);

frequency = zeros(256,1);%����ͳ�Ƹ����Ҷȳ��ֵĴ���
probability = zeros(256,1);%������ֵĿ�����

for i=1:size(grayImage,1)
    for j=1:size(grayImage,2)
       value = grayImage(i,j);
       frequency(value+1) = frequency(value+1) + 1;
       probability(value+1) = frequency(value+1) / numOfPixels;
    end
end

cum = zeros(256,1);%��¼��������ֵ���ۻ��ֲ�
probc = zeros(256,1);%��¼��������ֵ���ۻ��ֲ��Ŀ�����
output = zeros(256,1);%����ͼ���и����Ҷ�ֵ�ľ��⻯֮���ֵ
sum = 0;
numOfBins = 255;

for i=1:size(probability)
    sum = sum + frequency(i);
    cum(i) = sum;
    probc(i) = cum(i) / numOfPixels;
    output(i) = round(probc(i) * numOfBins);
end

HEImage = uint8(zeros(size(grayImage,1),size(grayImage,2)));%���⻯���ͼ��
for i=1:size(grayImage,1)
    for j=1:size(grayImage,2)
        HEImage(i,j) = output(grayImage(i,j)+1);
    end
end

figure,imshow(HEImage);
title('Histogram Equalization');

