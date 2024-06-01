[![Open Source Society University - Computer Science](https://img.shields.io/badge/OSSU-computer--science-blue.svg)](https://github.com/ossu/computer-science)

# From-Nand-Gates-To-Operating-System

This project's goal is to build a full computer from scratch by using only a `Nand` gate abstraction to go from implementing the CPU , RAM all the way till the Assembler , Compiler and finally a basic Operating System.

## Computer Layers
![Computer Layers](https://github.com/SamaMostafa03/From-Nand-Gates-To-Operating-System/blob/main/Images/Computer%20Layers.jpg?raw=true)

This project was done in 9 subprojects, each in their respective folder. Since this project is focused on Computer Science, the computer was built on my own PC, using a software-based hardware simulator without any need for physical materials.

## 1 - Logic Gates

Creating elementary logic gates which will be the foundation of the Hack computer (this project's computer architecture). The Hardware Description Language (HDL) was used to create the following 15 elementary logic gates:

- `Not.hdl` - Inverts the input bit.
- `And.hdl` - Outputs 1 if both inputs are 1.
- `Or.hdl` - Outputs 1 if either input is 1.
- `Xor.hdl` - Outputs 1 if only one input is 1.
- `Mux.hdl` - Has two inputs, one selector bit and one output. The selector bit chooses which input to output.
- `DMux.hdl` - Has one input, one selector bit and two outputs. The selector bit chooses which output the input will go through. In case it chooses the `a` output, the `b` output will be 0.
- `Not16.hdl` - `Not` gate for 16-bit integer.
- `And16.hdl` - `And` gate for 16-bit integer.
- `Or16.hdl` - `Or` gate for 16-bit integer.
- `Mux16.hdl` - `Mux` gate for 16-bit integer.
- `Or8Way.hdl` - `Or` gate for 8-bit integer.
- `Mux4Way16.hdl` - `Mux` gate for 16-bit integer with 4 inputs instead of 2.
- `Mux8Way16.hdl` - `Mux` gate for 16-bit integer with 8 inputs instead of 2.
- `DMux4Way.hdl` - `DMux` gate with 4 outputs instead of 2.
- `DMux8Way.hdl` - `DMux` gate with 8 outputs instead of 2.

All of these gates were built either from the primitive `Nand` gate or from previously built gates.

## 2 - Arithmetic Gates And ALU

Creating arithmetic gates to implement the computer's Arithmetic Logic Unit (ALU):

- `HalfAdder.hdl` - Sums two input bits and outputs the sum and the carry bit.
- `FullAdder.hdl` - Sums two input bits and one carry bit and outputs the sum and the carry bit.
- `Add16.hdl` - Adds two 16-bit integers in Two's complement.
- `Inc16.hdl` - Adds 1 to 16-bit integers.
- `ALU.hdl` - Arithmetic Logic Unit, used to compute various operations, according to the following table:

![ALU](https://github.com/SamaMostafa03/From-Nand-Gates-To-Operating-System/blob/main/Images/ALU.png?raw=true)

## 3 - Memory Chips

Creating the memory chips of the Hack computer using the abstraction of the Data Flip-Flop gate (DFF):

- `Bit.hdl` - 1-bit Register.
- `Register.hdl` - 16-bit Register.
- `RAM8.hdl` - 16-bit RAM with 8 register of memory.
- `RAM64.hdl` - 16-bit RAM with 64 register of memory.
- `RAM512.hdl` - 16-bit RAM with 512 register of memory.
- `RAM4K.hdl` - 16-bit RAM with 4096 register of memory.
- `RAM16K.hdl` - 16-bit RAM with 16384 register of memory.
- `PC.hdl` - 16-bit program counter.

## 4 - Machine Language Programs

In this part, i wrote some assembly programs in order to start learning the Hack Assembly language that will eventually run on the Hack computer:

- `Fill.asm` - Runs an infinite loop that listens to the keyboard input. When a key is pressed (any key), the program blackens the screen and should remain fully black as long as the key is pressed. When no key is pressed, the program clears the screen. The screen should remain fully clear as long as no key is pressed.
- `Mult.asm` - Multiplies `RAM[0]` and `RAM[1]` and stores the result in `RAM[2]`.
- `add.asm` - Sums `RAM[0]` and `RAM[1]` and stores the result in `RAM[2]`.
- `max.asm` - Gets the maximum of `RAM[0]` and `RAM[1]` and stores the result in `RAM[2]`.
- `sum1toN.asm` - Sums from 1 to `RAM[0]` and stores the result in `RAM[1]`: R1<-1+2+3+..+R0
- `sumArray.asm` - Stores the summation of all array elements in variable 'sum'

## 5 - Computer Architecture

Creating CPU and RAM of the Hack computer and applying the `Harvard Architecture` where the CPU has separate buses and memory for data and instructions, this is applied through the following chips:

- `Memory.hdl` - Entire RAM address space for the computer (`RAM16K`, Keyboard and Screen).
- `CPU.hdl` - The Hack CPU.
- `Computer.hdl` - The Hack computer platform.

`Harvard Architecture` :

![Computer Architecture](https://github.com/SamaMostafa03/From-Nand-Gates-To-Operating-System/blob/main/Images/Computer%20Arch.png?raw=true)

`Memory Design` :

![Memory](https://github.com/SamaMostafa03/From-Nand-Gates-To-Operating-System/blob/main/Images/Memory.png?raw=true)

`CPU Design` :

![CPU](https://github.com/SamaMostafa03/From-Nand-Gates-To-Operating-System/blob/main/Images/CPU.png?raw=true)