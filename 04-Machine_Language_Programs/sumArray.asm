//program to store the summation of all array elements in variable'sum'
//int[5] arr
//for(int i:0->5)sum=sum+arr[i]
    @i
    M=0
    @sum
    M=0
(LOOP)
    @i
    D=M
    @len
    D=D-M 
    @END
    D;JGE
    @arr
    D=M
    @i
    A=M+D
    D=M 
    @sum
    M=M+D
    @i
    M=M+1
    @LOOP
    0;JMP
(END)
    @END
    0;JMP