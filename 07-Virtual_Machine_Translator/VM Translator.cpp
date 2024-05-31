//VM Translator.cpp built to translate Virtual Machine code into Hack assembly.
//TODO : rewrite main() , optimize eq/lt/gt jump , check if default string, int = null,0 in Parser.setArg()
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <filesystem>
using namespace std;

//class CommandParser to define the VM command type and its arguments
class CommandParser {
private:
    string currentFile,command, commandType, firstArg, lexicalComponents[3];
    int secondArg = 0;
    void setLexicalComponents()
    {
        stringstream streamLine(this->command);
        string word;
        for (int i = 0; getline(streamLine, word, ' '); i++)
        {
            this->lexicalComponents[i] = word;
        }
    }
    void setCommandType()
    {
        string firstComponent = lexicalComponents[0];
        transform(firstComponent.begin(), firstComponent.end(), firstComponent.begin(), ::toupper);
        if (firstComponent == "ADD" || firstComponent == "SUB" || firstComponent == "NEG" ||
            firstComponent == "OR" || firstComponent == "AND" || firstComponent == "NOT" ||
            firstComponent == "EQ" || firstComponent == "LT" || firstComponent == "GT")this->commandType = "ARITHMETIC";
        else this->commandType = firstComponent;
    }
    void setArguments()
    {
        this->firstArg = "";
        this->secondArg = 0;
        if (this->commandType == "ARITHMETIC")this->firstArg = this->lexicalComponents[0];
        else if (this->commandType != "RETURN")this->firstArg = this->lexicalComponents[1];
        if (this->commandType == "PUSH" ||
            this->commandType == "POP" ||
            this->commandType == "FUNCTION" ||
            this->commandType == "CALL")this->secondArg = stoi(this->lexicalComponents[2]);
    }
public:
    void setCurrentFile(string currentFile)
    {
        this->currentFile = currentFile;
    }
    string getCurrentFile()
    {
        return this->currentFile;
    }
    void processParcing(string command)
    {
        this->command = command;
        this->setLexicalComponents();
        this->setCommandType();
        this->setArguments();
    }
    string getCommandType()
    {
        return this->commandType;
    }
    string getFirstArg()
    {
        return this->firstArg;
    }
    int getSecArg()
    {
        return this->secondArg;
    }
    string getCommand()
    {
        return this->command;
    }
};

//class CodeWriter to translate the VM command into hack assembly instruction
class CodeWriter {
private:
    CommandParser parser;
    ofstream cout;
    int labelID = 0, callID = 0; //unique id for eq,le,gt commands/call function command
    void setWriteOperation(string commandType)
    {
        string symbol = this->parser.getFirstArg();
        int index = this->parser.getSecArg();
        //write comment to define the VM command in asm file
        cout << "//" << this->parser.getCommand() << endl;
        //generate asm code of the VM command
        if (commandType == "ARITHMETIC")this->writeArithmitic(symbol);
        else if (commandType == "PUSH" || commandType == "POP")this->writePushPop(commandType, symbol, index);
        else if (commandType == "LABEL" || commandType == "GOTO" || commandType == "IF-GOTO")this->writeBranching(commandType, symbol);
        else if (commandType == "FUNCTION")this->writeFunction(symbol, index);
        else if (commandType == "CALL")this->writeCall(symbol, index);
        else this->writeReturn();
    }
    void writeArithmitic(string symbol)
    {
        transform(symbol.begin(), symbol.end(), symbol.begin(), ::toupper);
        if (symbol == "NOT" || symbol == "NEG")
        {
            cout << " @SP \n M=M-1 \n A=M \n";
            if (symbol == "NOT")cout << " M=!M \n";
            else cout << " M=-M \n";
            cout << " @SP \n M=M+1 \n";
        }
        else if (symbol == "ADD" || symbol == "SUB" || symbol == "AND" || symbol == "OR")
        {
            cout << " @SP \n M=M-1 \n A=M \n D=M \n @SP \n M=M-1 \n A=M \n";
            if (symbol == "ADD")cout << " M=M+D \n";
            else if (symbol == "SUB")cout << " M=M-D \n";
            else if (symbol == "AND")cout << " M=M&D \n";
            else cout << " M=M|D \n";
            cout << " @SP \n M=M+1 \n";
        }
        else //eq , it, gt
        {
            cout << " @SP \n M=M-1 \n A=M \n D=M \n @SP \n M=M-1 \n A=M \n D=M-D \n @TRUE-" << labelID << "\n";
            if (symbol == "EQ")cout << " D;JEQ \n";
            else if (symbol == "GT")cout << " D;JGT \n";
            else cout << " D;JLT \n";
            cout << " @SP \n A=M \n M=0 \n @INCR-SP" << labelID << "\n 0;JMP \n(TRUE-" << labelID << ")\n @SP \n A=M \n M=-1 \n(INCR-SP" << labelID << ")\n @SP \n M=M+1 \n";
            this->labelID++;
        }
    }
    void writePushPop(string commandType, string segment, int segIndex)
    {
        transform(segment.begin(), segment.end(), segment.begin(), ::toupper);
        if (segment == "CONSTANT") //push constant i : RAM[SP]=i; SP++;
        {
            cout << " @" << segIndex << "\n D=A \n @SP \n A=M \n M=D \n @SP \n M=M+1 \n";
        }
        else if (segment == "TEMP" || segment == "POINTER" || segment == "STATIC")
        {
            string newIndex;
            if (segment == "TEMP")newIndex = to_string(segIndex + 5);
            else if (segment == "POINTER")newIndex = to_string(segIndex + 3);
            else newIndex = this->parser.getCurrentFile() +"."+ to_string(segIndex + 16);
            if (commandType == "PUSH")//RAM[SP]=RAM[DESIRED LOCATION]; SP++;
            {
                cout << " @" << newIndex << "\n D=M \n @SP \n A=M \n M=D \n @SP \n M=M+1 \n";
            }
            else //POP : SP--; RAM[DESIRED LOCATION]=RAM[SP];
            {
                cout << " @SP \n M=M-1 \n A=M \n D=M \n @" << newIndex << "\n M=D \n";
            }
        }
        else //LCL,ARG,THIS,THAT
        {
            if (segment == "LOCAL")segment = "LCL";
            else if (segment == "ARGUMENT")segment = "ARG";
            cout << " @" << segIndex << "\n D=A \n @" << segment << "\n";
            if (commandType == "PUSH") //RAM[SP]=RAM[DESIRED LOCATION]; SP++;
            {
                cout << " A=M+D \n D=M \n @SP \n A=M \n M=D \n @SP \n M=M+1 \n";
            }
            else //POP : RAM[13]=DESIRED LOCATION; SP--; RAM[RAM[13]]=RAM[SP];
            {
                cout << " D=M+D \n @R13 \n M=D \n @SP \n M=M-1 \n A=M \n D=M \n @R13 \n A=M \n M=D \n";
            }
        }
    }
    void writeBranching(string commandType, string label)
    {
        if (commandType == "LABEL")cout << "(" << label << ")\n";
        else if (commandType == "GOTO")cout << " @" << label << "\n 0;JMP\n";
        else cout << " @SP\n M=M-1\n A=M\n D=M\n @" << label << "\n D;JNE\n"; //command if-goto
    }
    void writeFunction(string fName, int nVars)
    {
        cout<< "(" << fName << ")\n";
        if (nVars!=0)
        {
            cout << " @SP\n A=M\n";
            for (int i = 0; i < nVars; i++)
            {
                cout << " M=0\n A=A+1\n";
            }
            cout << " D=A\n @SP\n M=D\n";
        }
    }
    void writeCall(string fName, int nArg)
    {
        cout << " //Push return address\n @" << fName << "$Ret" << this->callID << "\n D=A\n @SP\n A=M\n M=D\n @SP\n M=M+1\n";
        cout << " //Push LCL of the caller\n @LCL\n D=M\n @SP\n A=M\n M=D\n @SP\n M=M+1\n";
        cout << " //Push ARG of the caller\n @ARG\n D=M\n @SP\n A=M\n M=D\n @SP\n M=M+1\n";
        cout << " //Push THIS of the caller\n @THIS\n D=M\n @SP\n A=M\n M=D\n @SP\n M=M+1\n";
        cout << " //Push THAT of the caller\n @THAT\n D=M\n @SP\n A=M\n M=D\n @SP\n M=M+1\n";
        cout << " //Reposition ARG of callee\n @SP\n D=M\n @5\n D=D-A\n @" << nArg << "\n D=D-A\n @ARG\n M=D\n";
        cout << " //Reposition LCL of callee\n @SP\n D=M\n @LCL\n M=D\n";
        cout << " //jump to callee\n @" << fName << "\n 0;JMP\n";
        cout << "(" << fName << "$Ret" << this->callID << ")\n";
        this->callID++;
    }
    void writeReturn()
    {
        cout << " //Reposition return address\n @LCL\n D=M\n @5\n A=D-A\n D=M\n @R15\n M=D\n";
        cout << " //Give the return value to the caller\n @SP\n M=M-1\n A=M\n D=M\n @ARG\n A=M\n M=D\n";
        cout << " //Reposition SP to recycle the memory\n @ARG\n D=M\n @SP\n M=D+1\n";
        cout << " //Reposition THAT\n @LCL\n D=M\n @1\n A=D-A\n D=M\n @THAT\n M=D\n";
        cout << " //Reposition THIS\n @LCL\n D=M\n @2\n A=D-A\n D=M\n @THIS\n M=D\n";
        cout << " //Reposition ARG\n @LCL\n D=M\n @3\n A=D-A\n D=M\n @ARG\n M=D\n";
        cout << " //Reposition LCL\n @LCL\n D=M\n @4\n A=D-A\n D=M\n @LCL\n M=D\n";
        cout << " //return to caller\n @R15\n A=M\n 0;JMP\n";
    }
    void writeBootStrap()
    {
        cout << "//BootStrap code : SP=256 , call sys.init\n @256\n D=A\n @0\n M=D\n";
        this->writeCall("Sys.init", 0);
    }
public:
    CodeWriter(const string& writeFile , bool systemInitExist)
    {
        this->cout.open(writeFile);
        if(systemInitExist)this->writeBootStrap();
    }
    void generateCode(CommandParser parser)
    {
        this->parser = parser;
        this->setWriteOperation(this->parser.getCommandType());
    }
};

int main()
{
    vector<string>vmFiles;
    bool systemInitExist = false;
    string path = "D:\\test";
    try {
        //to get all vm files in the path directory
        for (const auto& entry : filesystem::directory_iterator(path)) {
            filesystem::path systemPath = entry.path();
            string fileName = systemPath.filename().string();
            if (fileName[fileName.size() - 1] == 'm' && fileName[fileName.size() - 2] == 'v' && fileName[fileName.size() - 3] == '.')
            {
                fileName.erase(fileName.size()-3);
                vmFiles.push_back(fileName);
                if (fileName == "Sys")systemInitExist = true;
            }
        }
    }
    catch (const filesystem::filesystem_error& e) {
        cerr<<"Filesystem error: "<<e.what()<<endl;
    }
    CommandParser parser;
    CodeWriter writer(path + "\\StaticsTest.asm" , systemInitExist);
    for (string vmFile : vmFiles)
    {
        ifstream cin(path+"\\"+vmFile+".vm");
        parser.setCurrentFile(vmFile);
        while (!cin.eof())
        {
            string line;
            getline(cin, line);
            if (line.length()) //skip empty lines
            {
                istringstream streamLine(line);
                string word,command;
                while (streamLine >> word) {
                    if (word.find("//") != std::string::npos)break;
                    command += word+" ";
                }      
                if (command.length())
                {
                    command.erase(command.size() - 1);
                    parser.processParcing(command); //parse the VM command
                    writer.generateCode(parser); //generate assembly code
                }
            }
        }
        cin.close();
    }
}
