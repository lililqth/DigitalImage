img=imread('3.png');
%img=double(img);
f=fft2(img);        %����Ҷ�任
f=fftshift(f);      %ʹͼ��Գ�
r=real(f);          %ͼ��Ƶ��ʵ��
i=imag(f);          %ͼ��Ƶ���鲿
margin=log(abs(f));      %ͼ������ף���log������ʾ
phase=log(angle(f)*180/pi);     %ͼ����λ��
l=log(f);           
subplot(2,2,1),imshow(img),title('Դͼ��');
%subplot(2,2,2),imshow(l,[]),title('ͼ��Ƶ��');
subplot(2,2,3),imshow(margin,[]),title('ͼ�������');
subplot(2,2,4),imshow(phase,[]),title('ͼ����λ��');