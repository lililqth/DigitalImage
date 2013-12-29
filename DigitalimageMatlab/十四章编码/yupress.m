clear;
I=imread('1.bmp');       
figure;
subplot(2,2,1),imshow(I); title('原图像');

I=rgb2gray(I);                  
subplot(2,2,2),imshow(uint8(I));  
title('灰度图像');

I=double(I);             
for i=1:8
    for j=1:8
        if (i==1)
            Y(i,j)=sqrt(1/8);
        else
            Y(i,j)=sqrt(2/8)*cos((i-1)*(2*j-1)*pi/(2*8));
        end;
    end;
end;
s=blkproc(I,[8 8],'P1*x*P2',Y,Y');

subplot(2,2,3),imshow(s);  
title('DCT系数');

a=ones(8,8);
b=reshape(Y,1,64);
midvalue=median(b);
for i=1:8
    for j=1:8
        if(abs(Y(i,j))<midvalue)
            a(i,j)=0;
        end;
    end;
end;
s=blkproc(s,[8 8],'P1.*x',a);
s=blkproc(s,[8 8],'P1*x*P2',Y',Y);


subplot(2,2,4),imshow(uint8(s));
title('阈值编码方式压缩的图像');
