function K=SSD(I,J)

H=(I-J).*(I-J);

K=sum(H(:));

end