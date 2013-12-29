bmp=imread('1.bmp');
subplot(2,2,1),imshow(bmp);title('Ô´Í¼Ïñ');
gray=rgb2gray(bmp);
subplot(2,2,2),imshow(gray);title('»Ò¶ÈÍ¼Ïñ');
FT=fft2(gray);
FS=fftshift(FT);
P=log(1+abs(FS));
subplot(2,2,3),imshow(P,[]);title('¸µÀïÒ¶±ä»»Í¼Ïñ');
FR=real(ifft2(ifftshift(FS)));  
ret=im2uint8(mat2gray(FR));  
subplot(2,2,4),imshow(ret);title('¸µÀïÒ¶Äæ±ä»»Í¼Ïñ');








