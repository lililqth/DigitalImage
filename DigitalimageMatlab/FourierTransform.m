bmp=imread('1.bmp');
subplot(2,2,1),imshow(bmp);title('Դͼ��');
gray=rgb2gray(bmp);
subplot(2,2,2),imshow(gray);title('�Ҷ�ͼ��');
FT=fft2(gray);
FS=fftshift(FT);
P=log(1+abs(FS));
subplot(2,2,3),imshow(P,[]);title('����Ҷ�任ͼ��');
FR=real(ifft2(ifftshift(FS)));  
ret=im2uint8(mat2gray(FR));  
subplot(2,2,4),imshow(ret);title('����Ҷ��任ͼ��');








