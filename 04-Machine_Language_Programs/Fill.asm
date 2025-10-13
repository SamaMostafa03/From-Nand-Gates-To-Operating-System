// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen
// by writing 'black' in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen by writing
// 'white' in every pixel;
// the screen should remain fully clear as long as no key is pressed.

//// Replace this comment with your code.
(LOOP)
    @SCREEN
    D=A
    @wordLocation
    M=D
    @KBD 
    D=M 
    @WHITE 
    D;JEQ
    @word
    M=-1
(LOOP-SCREEN)
    @wordLocation
    D=M 
    @KBD 
    D=D-A
    @LOOP
    D;JEQ
    @word
    D=M 
    @wordLocation
    A=M 
    M=D 
    @wordLocation
    M=M+1
    @LOOP-SCREEN
    0;JMP
(WHITE)
    @word
    M=0
    @LOOP-SCREEN
    0;JMP
