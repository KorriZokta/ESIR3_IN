function I=information_mutuelle(H)
H=H/sum(H(:));
pi=sum(H,2);
pj=sum(H,1);
I=0;
for x=1:256
    for y=1:256
        if(H(x,y)==0)
            loge=0;
        else
            loge=log2(H(x,y)/(pi(x)*pj(y)));
        end
        
        I=I+H(x,y)*loge;
    end
end

end