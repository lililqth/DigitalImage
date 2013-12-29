%Ã¤È¥¾í»ý¸´Ô­
I=checkerboard(8);
PSF=fspecial('gaussian',7,10);
V=.0001;
BlurredNoisy=imnoise(imfilter(I,PSF),'gaussian',0,V);
WT=zeros(size(I));
WT(5:end-4,5:end-4)=1;
INITPSF=ones(size(PSF));
FUN=inline('PSF+P1','PSF','P1');
[J P]=deconvblind(BlurredNoisy,INITPSF,20,10*sqrt(V),WT,FUN,0);
subplot(221);imshow(BlurredNoisy);
title('A=Blurred and Noisy');
subplot(222);imshow(PSF,[]);
title('True PSF');
subplot(223);imshow(J);
title('Deblured Image');
subplot(224);imshow(P,[]);
title('Recovered PSF');