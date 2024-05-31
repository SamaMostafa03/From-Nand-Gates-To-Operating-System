//program to set R2<-max(R0,R1)
    @R0
    D=M 
    @R1
    D=D-M //D<-R0-R1
    @R0-MAX
    D;JGE
    @R1
    D=M
    @R2 
    M=D //R2<-R1
    @END
    0;JMP
(R0-MAX)
    @R0
    D=M 
    @R2 
    M=D //R2<-R0
(END)
    @END
    0;JMP