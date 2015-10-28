function K=Hist2(I,J)
nbPixI=size(I,1);
nbPixJ=size(I,2);
K=zeros(256,256);

for i=1:nbPixI
    for j=1:nbPixJ
        abs=I(i,j)+1;
        ord=J(i,j)+1;
        K(abs,ord)=K(abs,ord)+1;
    end
end

end