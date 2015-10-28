function coupe_aff(M0,axe)

vmin=min(M0(:))
vmax=max(M0(:))
x=size(M0,1)
y=size(M0,2)
z=size(M0,3)
if(axe==1) %sagittal
    for i=1:x
       f1= squeeze(M0(i,:,:));
       %imshow(f1,[vmin vmax]);         %affichage en ndg
       imagesc(f1);axis equal;axis off; %affichage en fausse couleur
       drawnow;
    end
elseif(axe==2) %coronal
    for i=1:y
        f2= squeeze(M0(:,i,:));
        %imshow(f2,[vmin vmax]);
        imagesc(f2);axis equal;axis off;
        drawnow;
    end
elseif(axe==3) %axial
    for i=1:z
        f3= squeeze(M0(:,:,i));
        %imshow(f3,[vmin vmax]);
        imagesc(f3);axis equal;axis off;
        drawnow;
    end
end
end