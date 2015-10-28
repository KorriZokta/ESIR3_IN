%%% Affichage des coupes %%%
load('IRM_cerveau.mat');
coupe_aff(M0,1);
coupe_aff(M0,2);
coupe_aff(M0,3);

%%% K-means %%%
[seg,seuils]=k_moyennes(M0,3);
imshow(squeeze(M0(:,:,80)),[]);
figure;
imagesc(squeeze(seg(:,:,80)));axis equal;axis off;
figure;
coupe_aff(seg,1);
coupe_aff(seg,2);
coupe_aff(seg,3);

%%% Marching cubes %%%
seg=smooth3(seg);
figure;
MarchingCubes(seg,1.5);

%%% Segmentation avec biais %%%
load('IRM_cerveau_avecbiais.mat');
figure;
imshow(squeeze(M0(:,:,80)),[]);
[seg,seuils]=k_moyennes(M0,3);
figure;
imagesc(squeeze(seg(:,:,80)));axis equal;axis off;

%%% Surf %%%
figure;
surf(M0(:,:,80));

%%% Régression par moindres carrés %%%
%I=double(imread('image_test_biais.png'));
I=M0(:,:,80);
figure;
I=least_square(I);
[seg,seuils]=k_moyennes(I,3);
figure;
imagesc(seg);axis equal;axis off;