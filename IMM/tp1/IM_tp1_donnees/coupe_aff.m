function coupe_aff(M0,axe)

vmin=min(M0(:))
vmax=max(M0(:))
M0(isnan(M0))=0;
if(axe==1) %sagittal
    for i=1:134
       f1= squeeze(M0(i,:,:));
       %imshow(f1,[vmin vmax]);
       imagesc(f1);axis equal;axis off; %pour fausses couleurs
       drawnow;
    end
elseif(axe==2) %coronal
    for i=1:172
        f2= squeeze(M0(:,i,:));
        %imshow(f2,[vmin vmax]);
        imagesc(f2);axis equal;axis off; %pour fausses couleurs
        drawnow;
    end
elseif(axe==3) %axial
    for i=1:137
        f3= squeeze(M0(:,:,i));
        %imshow(f3,[vmin vmax]);
        imagesc(f3);axis equal;axis off; %pour fausses couleurs
        drawnow;
    end
end
end