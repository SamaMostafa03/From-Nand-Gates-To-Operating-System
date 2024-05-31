//Hack Assembler.cpp built to translate .asm files into .hack files.
//TODO : optimize comp,dest,jump tables
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <filesystem>
#include <map> 
#include <bitset>
using namespace std;

map<string, int>symbolTable;
map<string, string>comp, dest, jump;

void addSymbol(string symbol, int address)
{
    symbolTable[symbol] = address;
}

bool isExistedSymbol(string symbol)
{
    for (auto it : symbolTable)
    {
        if (it.first == symbol)return true;
    }
    return false;
}

void initializeSymbolTable()
{
    for (int i = 0; i < 16; i++)
    {
        addSymbol('R' + to_string(i), i);
    }
    addSymbol("SCREEN", 16384);
    addSymbol("KBD", 24576);
    addSymbol("SP", 0);
    addSymbol("LCL", 1);
    addSymbol("ARG", 2);
    addSymbol("THIS", 3);
    addSymbol("THAT", 4);
}

string getInstructionType(string instruction)
{
    if (instruction[0] == '(')return"L-instruction";
    if (instruction[0] == '@')return"A-instruction";
    return"C-instruction";
}

void initializeCTables()
{
    dest["null"] = "000";
    dest["M"] = "001";
    dest["D"] = "010";
    dest["DM"] = "011";
    dest["MD"] = "011";
    dest["A"] = "100";
    dest["AM"] = "101";
    dest["MA"] = "101";
    dest["AD"] = "110";
    dest["DA"] = "110";
    dest["ADM"] = "111";
    dest["AMD"] = "111";
    dest["MDA"] = "111";
    dest["MAD"] = "111";
    dest["DAM"] = "111";
    dest["DMA"] = "111";
    jump["null"] = "000";
    jump["JGT"] = "001";
    jump["JEQ"] = "010";
    jump["JGE"] = "011";
    jump["JLT"] = "100";
    jump["JNE"] = "101";
    jump["JLE"] = "110";
    jump["JMP"] = "111";
    comp["0"] = "0101010";
    comp["1"] = "0111111";
    comp["-1"] = "0111010";
    comp["D"] = "0001100";
    comp["M"] = "1110000";
    comp["A"] = "0110000";
    comp["!D"] = "0001101";
    comp["!M"] = "1110001";
    comp["!A"] = "0110001";
    comp["-D"] = "0001111";
    comp["-M"] = "1110011";
    comp["-A"] = "0110011";
    comp["D+1"] = "0011111";
    comp["M+1"] = "1110111";
    comp["A+1"] = "0110111";
    comp["D-1"] = "0001110";
    comp["M-1"] = "1110010";
    comp["A-1"] = "0110010";
    comp["D+M"] = "1000010";
    comp["D+A"] = "0000010";
    comp["D-M"] = "1010011";
    comp["D-A"] = "0010011";
    comp["M-D"] = "1000111";
    comp["A-D"] = "0000111";
    comp["D&M"] = "1000000";
    comp["D&A"] = "0000000";
    comp["D|M"] = "1010101";
    comp["D|A"] = "0010101";
}

void firstPass()
{
    ifstream cin("Prog.asm");
    ofstream tempFile("cleanedAsm.txt");
    int instructionCounter = 0;
    while (!cin.eof())
    {
        string line;
        getline(cin, line);
        if (line.length()) //skip empty lines
        {
            string instruction;
            for (int i = 0; i < line.length(); i++)
            {
                if (line[i] == ' ')continue;
                if (i != line.length() - 1 && line[i] == '/' && line[i + 1] == '/')break;
                instruction += line[i];
            }
            if (instruction.length())
            {
                if (getInstructionType(instruction) == "L-instruction")
                {
                    addSymbol(instruction.substr(1, instruction.length() - 2), instructionCounter);
                }
                else
                {
                    if (instructionCounter)tempFile << endl;
                    tempFile << instruction;
                    instructionCounter++;
                }
            }
        }
    }
    cin.close();
    tempFile.close();
}

void secondPass()
{
    ifstream asmFile("cleanedAsm.txt");
    ofstream cout("Prog.hack");
    int variableAddress = 16;
    while (!asmFile.eof())
    {
        string instruction;
        getline(asmFile, instruction);
        if (getInstructionType(instruction) == "A-instruction")
        {
            instruction = instruction.substr(1, instruction.length() - 1);
            if (instruction[0] >= 48 && instruction[0] <= 57)//address
            {
                cout << bitset<16>(stoi(instruction)).to_string() << endl;//binary code of the instruction
            }
            else //either a variable or a label
            {
                if (isExistedSymbol(instruction))
                {
                    cout << bitset<16>(symbolTable[instruction]).to_string() << endl;
                }
                else //new variable
                {
                    addSymbol(instruction, variableAddress);
                    cout << bitset<16>(variableAddress).to_string() << endl;//binary code of the instruction
                    variableAddress++;
                }
            }
        }
        else //C-instruction
        {
            string binaryInstruction = "111", field, destField, jumpField, compField;
            int index = 0;
            while (instruction[index] != '=' && instruction[index] != ';')
            {
                field += instruction[index++];
            }
            if (instruction[index] == '=')
            {
                destField = field;
                jumpField = "null";
                for (int i = index + 1; i < instruction.length(); i++)compField += instruction[i];
            }
            else
            {
                compField = field;
                destField = "null";
                for (int i = index + 1; i < instruction.length(); i++)jumpField += instruction[i];
            }
            binaryInstruction += comp[compField];
            binaryInstruction += dest[destField];
            binaryInstruction += jump[jumpField];
            cout << binaryInstruction << endl;
        }
    }
    asmFile.close();
    cout.close();
}

int main()
{
    initializeSymbolTable(); //initialize predefined variables
    initializeCTables(); //initialize dest/comp/jump tables
    firstPass(); //add labels in the symbolic table
    secondPass(); //add variables and generate binary code
}
