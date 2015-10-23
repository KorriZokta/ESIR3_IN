close all;clear;clc
n=100;

%on génère les données 
x = rand(1,n);
y = rand(1,n);
z = 2*x-5*y+3 + randn(1,n); %équation du plan z=2x-5y+3 et on ajoute du bruit blanc gaussien(mu=0 std=1)
% c'est cette équation qu'on veut retrouver malgré le bruit présent dans les données
% on cherche donc à estimer a,b et c tel que a*X + b*Y + c soit le plus proche de Z possible

%on affiche les données
L=plot3(x,y,z,'ro'); % affiche les points (x,y,z) (données)
set(L,'Markersize',2*get(L,'Markersize')) % augmente la taille des cercles
set(L,'Markerfacecolor','r') % remplit les cercles

pause %appuyez sur une touche pour continuer

Xcolv = x(:); % on transforme en vecteur colonne
Ycolv = y(:); 
Zcolv = z(:); 
Const = ones(size(Xcolv)); %vecteur de 1 pour le terme constant

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Coefficients = [Xcolv Ycolv Const]\Zcolv; % Trouve les coefficients (moindre carré)
%help \   -->  
%     If A is an M-by-N matrix with M < or > N and B is a column
%     vector with M components, or a matrix with several such columns,
%     then X = A\B is the solution in the least squares sense to the
%     under- or overdetermined system of equations A*X = B.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

XCoeff = Coefficients(1); % coefficient dvt le terme en X (a)
YCoeff = Coefficients(2); % coefficient dvt le terme en Y (b)
CCoeff = Coefficients(3); % terme constant (c)
% avec les variables ci-dessus on a z " à peu près égal à" XCoeff * x + YCoeff * y + CCoeff
% il s'agit du plan qui "explique" le mieux les données.

% On affiche le plan pour vérifier
hold on
[xx, yy]=meshgrid(0:.1:1,0:.1:1); % génère une grille régulière pour l'affichage du plan estimé
zz = XCoeff * xx + YCoeff * yy + CCoeff;
surf(xx,yy,zz) % affiche le plan donné par l'équation estimée
title(sprintf('Plan z=(%f)*x+(%f)*y+(%f)',XCoeff, YCoeff, CCoeff)) %équation du plan estimé (doit être proche de z=2x-5y+3)
% En tournant autour de la surface on voit que les points (x,y,z) sont "à peu près" sur le plan estimé