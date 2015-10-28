clear;clc;close all;
%%%%%%%%%%%%%%%%%%%%%
bandwidth = 1;     % param�tre du Mean-Shift
%%%%%%%%%%%%%%%%%%%%%

nbPtsParCluster = 500;
nbCluster  = 3;
nbTotalPts = nbPtsParCluster*nbCluster;
m(1,:) = [1 1];
m(2,:) = [-1 -1];
m(3,:) = [1 -1];
var = .6;
x = var*randn(nbPtsParCluster*nbCluster,2);

% on construit un nuage de points � partir des 3 moyennes pr�c�dentes
for i = 1:nbCluster
    x(1+(i-1)*nbPtsParCluster:(i)*nbPtsParCluster,:)       = x(1+(i-1)*nbPtsParCluster:(i)*nbPtsParCluster,:) + repmat(m(i,:),nbPtsParCluster,1);   
end

%affichage
plot(x(:,1),x(:,2),'.');
disp('Appuyez sur une touche pour lancer le clustering par Mean Shift.');
pause;
tic;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%            MEAN-SHIFT
      [Seg means] = MeanShift(x,bandwidth);
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
toc;

disp('Moyennes : ');
disp(means);

% affichage du r�sultat
cVec = 'bgrcmyk'; 
hold on;
for k=1:nbTotalPts
    plot(x(k,1),x(k,2),[cVec(mod(Seg(k),numel(cVec))+1) '.'])
end
