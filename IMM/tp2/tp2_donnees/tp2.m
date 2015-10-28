%%% Cerveau ndg %%%
%  load('IRM_cerveau.mat');
%  Im=M0(:,:,80);
%  Im(isnan(Im))=0;
%  x=Im(:);
%  
%  bandwidth = 25;
%  
%  [Seg means] = MeanShift(x,bandwidth);
%  Seg=reshape(Seg,size(Im));
%  imshow(Seg,[]);
%  figure;
%  imagesc(Seg);axis equal;axis off;


%%% Couleur %%%
I=double(imread('test_MS.jpg'));
Iluv=rgb2luv(I);
L=Iluv(:,:,1);
U=Iluv(:,:,2);
V=Iluv(:,:,3);
x=[L(:) U(:) V(:)];

bandwidth = 20;

[Seg means] = MeanShift(x,bandwidth);
Seg=reshape(Seg,size(I,1),size(I,2));
imshow(Seg,[]);
figure;
imagesc(Seg);axis equal;axis off;