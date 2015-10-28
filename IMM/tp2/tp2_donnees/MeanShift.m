function [Seg means] = MeanShift(X,bandwidth)
% X est le nuage de points � segmenter, de taille n*d 
% X(i,:) est le i-i�me point (en dimension d)
% bandwidth est le param�tre d'�chelle (R dans l'�nonc�)

stopThresh = 1e-3*bandwidth;  %Seuil pour d�cider que la moyenne a converg�

nbPts = size(X,1); %nombre de points du nuage

Seg = zeros(nbPts,1); %r�sultat de la segmentation


nClust = 0; %nombre de clusters
means = []; %means sera le vecteur contenant les points limite (de convergence) de chaque cluster

% Tant qu'il reste des points qui n'ont pas �t� visit�
while(sum(Seg~=0)<nbPts)
    disp(['nb de points restants=' num2str(nbPts-sum(Seg~=0)) ' nbClust=' num2str(nClust)]);
    
    %A FAIRE : choisir un point qui n'a pas encore �t� visit� 
    %          on obtient donc un indice ind_init
    indice = find(Seg==0);
    i = randi(numel(indice));
    ind_init = indice(i);
    
    %on initialise les moyennes (x_i et x_{i-1} dans l'�nonc�)
    mean_actu = X(ind_init,:);
    mean_old = mean_actu+1;

    %si la moyenne ne bouge plus suffisamment on arrete pour ce cluster
    while(norm(mean_actu-mean_old)>stopThresh)
        mean_old = mean_actu;
        
        %A FAIRE : selectionner tous les "voisins" de mean_actu
        %          mettre � jour mean_actu
        %          mettre � jour Seg
        idx=rangesearch(X,mean_actu,bandwidth);
        res=idx{1};
        mean_actu = mean(X(res,:),1);
        Seg(res)=nClust+1;
    end
    % on a converg� vers mean_actu
    
    mergeWith = 0;
    
    %on parcourt le vecteur means pour savoir s'il contient un vecteur
    %proche de mean_actu
    for cN = 1:nClust
        distToOther = norm(mean_actu-means(cN,:));   %distance entre l'eventuel nouveau cluster et le cN-i�me d�j� existant
        if distToOther < bandwidth/2                 % si la distance est < bandwidth/2 on veut fusionner le nouveau et l'ancien
            mergeWith = cN;
            break;
        end
    end
    
    
    if (mergeWith>0) %on a trouv� un cluster pr�c�dent proche de mean_actu
        % A FAIRE : modifier Seg et means en cons�quence
        Seg(Seg==nClust+1)=mergeWith;
        means(mergeWith,:)=(mean_actu+means(mergeWith,:))/2;
    else
        % A FAIRE : mettre � jour means et nClust
        nClust=nClust+1;
        means(nClust,:)=mean_actu;
    end
end