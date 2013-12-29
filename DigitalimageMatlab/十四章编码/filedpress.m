

clear;
I=imread('1.bmp');       
figure;
subplot(2,3,1),imshow(I); title('原图像');

I=double(rgb2gray(I));            
subplot(2,3,2),imshow(uint8(I));  
title('灰度后的图像');
Y=zeros(8,8);
for i=1:8
    for j=1:8
        if i==1
            Y(i,j)=sqrt(1/8);
        else
            Y(i,j)=sqrt(2/8)*cos((pi*(2*(j-1)+1)*(i-1))/16);
        end
    end
end
s=blkproc(I,[8 8],'P1*x*P2',Y,Y'); 

subplot(2,3,3),imshow(uint8(s));
title('DCT系数');

for j=1:8
    for i=1:8
        if j<=8-i+1
            a(i,j)=1;
        else
            a(i,j)=0;
        end;
    end;
end;
s=blkproc(s,[8 8],'P1.*x',a);
subplot(2,3,4),imshow(uint8(s));
title('DCT系数');

s=blkproc(s,[8 8],'P1*x*P2',Y',Y);
subplot(2,3,5),imshow(uint8(s));
title('区域压缩处理的图像') 

