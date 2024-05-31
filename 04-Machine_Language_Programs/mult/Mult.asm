//program to multiply RAM[0] and RAM[1]
//then store the result in RAM[2]
//R0>=0, R1>=0, R0*R1<32768
    @R2
    M=0
    @counter
    M=1
(LOOP)
    @counter
    D=M 
    @R0 
    D=D-M 
    @END
    D;JGT
    @R1
    D=M 
    @END
    D;JEQ
    @R1
    D=M
    @R2
    M=M+D
    @counter
    M=M+1
    @LOOP
    0;JMP
(END)
    @END
    0;JMP


