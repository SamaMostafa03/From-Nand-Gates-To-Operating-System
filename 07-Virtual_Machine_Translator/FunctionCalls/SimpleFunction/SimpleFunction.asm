//function SimpleFunction.test 2
(SimpleFunction.test)
 @R14
 M=0
 //Initialize Local variables
(LOOP-INIT-LCL-SimpleFunction.test)
 @2
 D=A
 @R14
 D=D-M
 @START-SimpleFunction.test
 D;JEQ
 //PUSH CONSTATNT 0
 @0
 D=A 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
 //POP LOCAL RAM[R14]
 @R14
 D=M 
 @LCL
 D=M+D 
 @R13 
 M=D 
 @SP 
 M=M-1 
 A=M 
 D=M 
 @R13 
 A=M 
 M=D 
 @R14
 M=M+1
 @LOOP-INIT-LCL-SimpleFunction.test
 0;JMP
(START-SimpleFunction.test)
//push local 0
 @0
 D=A 
 @LCL
 A=M+D 
 D=M 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
//push local 1
 @1
 D=A 
 @LCL
 A=M+D 
 D=M 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
//add
 @SP 
 M=M-1 
 A=M 
 D=M 
 @SP 
 M=M-1 
 A=M 
 M=M+D 
 @SP 
 M=M+1 
//not
 @SP 
 M=M-1 
 A=M 
 M=!M 
 @SP 
 M=M+1 
//push argument 0
 @0
 D=A 
 @ARG
 A=M+D 
 D=M 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
//add
 @SP 
 M=M-1 
 A=M 
 D=M 
 @SP 
 M=M-1 
 A=M 
 M=M+D 
 @SP 
 M=M+1 
//push argument 1
 @1
 D=A 
 @ARG
 A=M+D 
 D=M 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
//sub
 @SP 
 M=M-1 
 A=M 
 D=M 
 @SP 
 M=M-1 
 A=M 
 M=M-D 
 @SP 
 M=M+1 
//return
 //Give the return value to the caller
 @SP
 M=M-1
 A=M
 D=M
 @ARG
 A=M
 M=D
 //Reposition SP to recycle the memory
 @ARG
 D=M
 @SP
 M=D+1
 //Reposition THAT
 @LCL
 D=M
 @1
 A=D-A
 D=M
 @THAT
 M=D
 //Reposition THIS
 @LCL
 D=M
 @2
 A=D-A
 D=M
 @THIS
 M=D
 //Reposition ARG
 @LCL
 D=M
 @3
 A=D-A
 D=M
 @ARG
 M=D
 //Reposition LCL
 @LCL
 D=M
 @4
 A=D-A
 D=M
 @LCL
 M=D
 //Reposition return address
 @LCL
 D=M
 @5
 A=D-A
 D=M
 @R15
 M=D
 //return to caller
 @R15
 A=M
 0;JMP
