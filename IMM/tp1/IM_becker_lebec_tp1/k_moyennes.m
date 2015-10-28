function [Segmentation,Seuils] = k_moyennes(M0,k)
Moyennes = zeros(k,1);
Seuils=zeros(k+1,1);
vmax=max(M0(:));
vmin=min(M0(:));

%initialisation des k seuils
Seuils(1)=vmin;
Seuils(k+1)=vmax;
for(i=2:k)
    Seuils(i)=vmin+((i-1)*(vmax-vmin))/k;
end
Seuils_old = Seuils+1;

while (norm(Seuils-Seuils_old)>0) %tant que les seuils bougent
    
   %Mise a jour des moyennes de chaque classe 
   for (imm=2:k+1)
       Moyennes(imm-1,1)=mean(M0(M0>Seuils(imm-1)&M0<Seuils(imm)));
   end
        
   Seuils_old = Seuils;
   %Mise a jour des seuils s�parant chaque classe
       for(i=2:k)
           Seuils(i)=(Moyennes(i-1,1)+Moyennes(i,1))/2
       end
       
end

%Construction de la segmentation 
Segmentation=zeros(size(M0));
for i=1:k
    %Segmentation(Segmentation>Seuils(i) & Segmentation<Seuils(i+1)) = Moyennes(i);
    Segmentation(M0>Seuils(i) & M0<Seuils(i+1)) = i;
end