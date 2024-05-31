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
//function Sys.init 0
(Sys.init)
//push constant 4000
 @4000
 D=A 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
//pop pointer 0
 @SP 
 M=M-1 
 A=M 
 D=M 
 @3
 M=D 
//push constant 5000
 @5000
 D=A 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
//pop pointer 1
 @SP 
 M=M-1 
 A=M 
 D=M 
 @4
 M=D 
//call Sys.main 0
 //Push return address
 @Sys.main$Ret1
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
 @Sys.main
 0;JMP
(Sys.main$Ret1)
//pop temp 1
 @SP 
 M=M-1 
 A=M 
 D=M 
 @6
 M=D 
//label LOOP
(LOOP)
//goto LOOP
 @LOOP
 0;JMP
//function Sys.main 5
(Sys.main)
 @SP
 A=M
 M=0
 A=A+1
 M=0
 A=A+1
 M=0
 A=A+1
 M=0
 A=A+1
 M=0
 A=A+1
 D=A
 @SP
 M=D
//push constant 4001
 @4001
 D=A 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
//pop pointer 0
 @SP 
 M=M-1 
 A=M 
 D=M 
 @3
 M=D 
//push constant 5001
 @5001
 D=A 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
//pop pointer 1
 @SP 
 M=M-1 
 A=M 
 D=M 
 @4
 M=D 
//push constant 200
 @200
 D=A 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
//pop local 1
 @1
 D=A 
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
//push constant 40
 @40
 D=A 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
//pop local 2
 @2
 D=A 
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
//push constant 6
 @6
 D=A 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
//pop local 3
 @3
 D=A 
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
//push constant 123
 @123
 D=A 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
//call Sys.add12 1
 //Push return address
 @Sys.add12$Ret2
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
 @Sys.add12
 0;JMP
(Sys.add12$Ret2)
//pop temp 0
 @SP 
 M=M-1 
 A=M 
 D=M 
 @5
 M=D 
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
//push local 2
 @2
 D=A 
 @LCL
 A=M+D 
 D=M 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
//push local 3
 @3
 D=A 
 @LCL
 A=M+D 
 D=M 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
//push local 4
 @4
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
//function Sys.add12 0
(Sys.add12)
//push constant 4002
 @4002
 D=A 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
//pop pointer 0
 @SP 
 M=M-1 
 A=M 
 D=M 
 @3
 M=D 
//push constant 5002
 @5002
 D=A 
 @SP 
 A=M 
 M=D 
 @SP 
 M=M+1 
//pop pointer 1
 @SP 
 M=M-1 
 A=M 
 D=M 
 @4
 M=D 
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
//push constant 12
 @12
 D=A 
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
