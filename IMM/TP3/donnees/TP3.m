I=double(imread('I6.jpg'));
J=double(imread('J6.jpg'));

%Histogramme conjoint
K=Hist2(I,J);
imagesc(log(K));
axis equal off xy;
A=sum(K(:));

%Critère de similarité
%SSD 1 26574152
%SSD 2 473379387
%SSD 3 870751839
%SSD 4 362261357
%SSD 5 699888797
%SSD 6 425536176

%COR 1 0.9782
%COR 2 0.9962
%COR 3 0.1434
%COR 4 0.5640
%COR 5 0.6564
%COR 6 0.7802

%I1  1 2.2433
%I2  2 3.2154
%I3  3 0.9648
%I4  4 1.4775
%I5  5 0.8005
%I6  6 0.9736
B=SSD(I,J);
C=corr2(I,J);
D=information_mutuelle(K)

% %3 Transformation spatiales
% t=0:20;
% [X,Y,Z]=meshgrid(t,t,1:5);
% plot3(X(:),Y(:),Z(:),'ko','LineWidth',2);
% axis equal; set(gca,'IDir','normal');