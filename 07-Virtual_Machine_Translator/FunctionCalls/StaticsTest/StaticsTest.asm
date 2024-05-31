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
//function Class1.set 0
(Class1.set)
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
//pop static 0
 @SP 
 M=M-1 
 A=M 
 D=M 
 @Class1.16
 M=D 
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
//pop static 1
 @SP 
 M=M-1 
 A=M 
 D=M 
 @Class1.17
 M=D 
//push constant 0
 @0
 D=A 
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
//function Class1.get 0
(Class1.get)
//push static 0
 @Class1.16
 D=M 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
//push static 1
 @Class1.17
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
//function Class2.set 0
(Class2.set)
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
//pop static 0
 @SP 
 M=M-1 
 A=M 
 D=M 
 @Class2.16
 M=D 
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
//pop static 1
 @SP 
 M=M-1 
 A=M 
 D=M 
 @Class2.17
 M=D 
//push constant 0
 @0
 D=A 
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
//function Class2.get 0
(Class2.get)
//push static 0
 @Class2.16
 D=M 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
//push static 1
 @Class2.17
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
//push constant 6
 @6
 D=A 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
//push constant 8
 @8
 D=A 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
//call Class1.set 2
 //Push return address
 @Class1.set$Ret1
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
 @2
 D=D-A
 @ARG
 M=D
 //Reposition LCL of callee
 @SP
 D=M
 @LCL
 M=D
 //jump to callee
 @Class1.set
 0;JMP
(Class1.set$Ret1)
//pop temp 0
 @SP 
 M=M-1 
 A=M 
 D=M 
 @5
 M=D 
//push constant 23
 @23
 D=A 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
//push constant 15
 @15
 D=A 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
//call Class2.set 2
 //Push return address
 @Class2.set$Ret2
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
 @2
 D=D-A
 @ARG
 M=D
 //Reposition LCL of callee
 @SP
 D=M
 @LCL
 M=D
 //jump to callee
 @Class2.set
 0;JMP
(Class2.set$Ret2)
//pop temp 0
 @SP 
 M=M-1 
 A=M 
 D=M 
 @5
 M=D 
//call Class1.get 0
 //Push return address
 @Class1.get$Ret3
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
 @Class1.get
 0;JMP
(Class1.get$Ret3)
//call Class2.get 0
 //Push return address
 @Class2.get$Ret4
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
 @Class2.get
 0;JMP
(Class2.get$Ret4)
//label END
(END)
//goto END
 @END
 0;JMP
