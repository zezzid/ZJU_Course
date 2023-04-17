function C = convnew2(A,B)
    B=rot90(rot90(B));
    row_A=size(A,1);
    col_A=size(A,2);
    row_B=size(B,1);
    col_B=size(B,2);
    c_row=(row_B+1)/2;
    c_col=(col_B+1)/2;
    
    data=zeros(row_A+2*row_B-2,col_A+2*col_B-2);
    data(row_B:row_B+row_A-1,col_B:col_B+col_A-1)=A;
    
    C=zeros(row_A+row_B-1,col_A+col_B-1);
    for i = c_row:c_row+row_A+row_B-2
        for j = c_col:c_col+col_A+col_B-2
            temp=B.*data(i-c_row+1:i+c_row-1,j-c_col+1:j+c_col-1);
            C(i-c_row+1,j-c_col+1)=sum(sum(temp));
        end
    end
end
