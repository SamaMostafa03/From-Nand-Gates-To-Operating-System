//BootStrap code : SP=256 , call sys.init
 @256
 D=A
 @0
 M=D
 //Push return address
 @Sys.init$Ret0
 D=A
 @SP
 A=M
 M=D
 @SP
 M=M+1
 //Push LCL of the caller
 @LCL
 D=M
 @SP
 A=M
 M=D
 @SP
 M=M+1
 //Push ARG of the caller
 @ARG
 D=M
 @SP
 A=M
 M=D
 @SP
 M=M+1
 //Push THIS of the caller
 @THIS
 D=M
 @SP
 A=M
 M=D
 @SP
 M=M+1
 //Push THAT of the caller
 @THAT
 D=M
 @SP
 A=M
 M=D
 @SP
 M=M+1
 //Reposition ARG of callee
 @SP
 D=M
 @5
 D=D-A
 @0
 D=D-A
 @ARG
 M=D
 //Reposition LCL of callee
 @SP
 D=M
 @LCL
 M=D
 //jump to callee
 @Sys.init
 0;JMP
(Sys.init$Ret0)
//function Main.fibonacci 0
(Main.fibonacci)
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
//push constant 2
 @2
 D=A 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
//lt
 @SP 
 M=M-1 
 A=M 
 D=M 
 @SP 
 M=M-1 
 A=M 
 D=M-D 
 @TRUE-0
 D;JLT 
 @SP 
 A=M 
 M=0 
 @INCR-SP0
 0;JMP 
(TRUE-0)
 @SP 
 A=M 
 M=-1 
(INCR-SP0)
 @SP 
 M=M+1 
//if-goto N_LT_2
 @SP
 M=M-1
 A=M
 D=M
 @N_LT_2
 D;JNE
//goto N_GE_2
 @N_GE_2
 0;JMP
//label N_LT_2
(N_LT_2)
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
//return
 //Reposition return address
 @LCL
 D=M
 @5
 A=D-A
 D=M
 @R15
 M=D
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
 //return to caller
 @R15
 A=M
 0;JMP
//label N_GE_2
(N_GE_2)
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
//push constant 2
 @2
 D=A 
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
//call Main.fibonacci 1
 //Push return address
 @Main.fibonacci$Ret1
 D=A
 @SP
 A=M
 M=D
 @SP
 M=M+1
 //Push LCL of the caller
 @LCL
 D=M
 @SP
 A=M
 M=D
 @SP
 M=M+1
 //Push ARG of the caller
 @ARG
 D=M
 @SP
 A=M
 M=D
 @SP
 M=M+1
 //Push THIS of the caller
 @THIS
 D=M
 @SP
 A=M
 M=D
 @SP
 M=M+1
 //Push THAT of the caller
 @THAT
 D=M
 @SP
 A=M
 M=D
 @SP
 M=M+1
 //Reposition ARG of callee
 @SP
 D=M
 @5
 D=D-A
 @1
 D=D-A
 @ARG
 M=D
 //Reposition LCL of callee
 @SP
 D=M
 @LCL
 M=D
 //jump to callee
 @Main.fibonacci
 0;JMP
(Main.fibonacci$Ret1)
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
//push constant 1
 @1
 D=A 
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
//call Main.fibonacci 1
 //Push return address
 @Main.fibonacci$Ret2
 D=A
 @SP
 A=M
 M=D
 @SP
 M=M+1
 //Push LCL of the caller
 @LCL
 D=M
 @SP
 A=M
 M=D
 @SP
 M=M+1
 //Push ARG of the caller
 @ARG
 D=M
 @SP
 A=M
 M=D
 @SP
 M=M+1
 //Push THIS of the caller
 @THIS
 D=M
 @SP
 A=M
 M=D
 @SP
 M=M+1
 //Push THAT of the caller
 @THAT
 D=M
 @SP
 A=M
 M=D
 @SP
 M=M+1
 //Reposition ARG of callee
 @SP
 D=M
 @5
 D=D-A
 @1
 D=D-A
 @ARG
 M=D
 //Reposition LCL of callee
 @SP
 D=M
 @LCL
 M=D
 //jump to callee
 @Main.fibonacci
 0;JMP
(Main.fibonacci$Ret2)
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
//return
 //Reposition return address
 @LCL
 D=M
 @5
 A=D-A
 D=M
 @R15
 M=D
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
 //return to caller
 @R15
 A=M
 0;JMP
//function Sys.init 0
(Sys.init)
//push constant 4
 @4
 D=A 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
//call Main.fibonacci 1
 //Push return address
 @Main.fibonacci$Ret3
 D=A
 @SP
 A=M
 M=D
 @SP
 M=M+1
 //Push LCL of the caller
 @LCL
 D=M
 @SP
 A=M
 M=D
 @SP
 M=M+1
 //Push ARG of the caller
 @ARG
 D=M
 @SP
 A=M
 M=D
 @SP
 M=M+1
 //Push THIS of the caller
 @THIS
 D=M
 @SP
 A=M
 M=D
 @SP
 M=M+1
 //Push THAT of the caller
 @THAT
 D=M
 @SP
 A=M
 M=D
 @SP
 M=M+1
 //Reposition ARG of callee
 @SP
 D=M
 @5
 D=D-A
 @1
 D=D-A
 @ARG
 M=D
 //Reposition LCL of callee
 @SP
 D=M
 @LCL
 M=D
 //jump to callee
 @Main.fibonacci
 0;JMP
(Main.fibonacci$Ret3)
//label END
(END)
//goto END
 @END
 0;JMP
