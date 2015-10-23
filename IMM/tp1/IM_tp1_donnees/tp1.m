clear;
%Affichage des coupes
load('IRM_cerveau_avecbiais.mat');
%coupe_aff(M0,1); %sagittal
%coupe_aff(M0,2); %coronal
%coupe_aff(M0,3); %axial

%k-means
nbClasses=3; %le fond n'est pas compté
[seg,seuils]=k_moyennes(M0,3);
%coupe_aff(seg,1); %penser à modifier coupe_aff pour afficher en fausse couleur

%marching cubes
%seg=smooth3(seg); %ne fonctionne pas sous QtOctave
MarchingCubes(seg,1.5);



%I1=squeeze(seg(:,:,60));
%I2=squeeze(seg(:,:,120));

%figure;
%imagesc(I1);axis equal;axis off;
%figure;
%imagesc(I2);axis equal;axis off;


%I=double(imread('image_test_biais.png'))
%coupe_aff(M0,1);
%coupe_aff(2);
%coupe_aff(3);


%I =M0(:,:,80);
%least_square(I);