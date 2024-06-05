// Jack Compiler.cpp 
// Jack Syntax Analyzer.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <filesystem>
#include <map> 
using namespace std;
class JackTokinizer
{
private:
    ofstream cout;
    ifstream cin;
    string currentPath, currentFile, token, tokenType;
    vector<string>keywords = { "class", "constructor", "if", "else", "let", "field", "static", "var", "method", "function",
                                     "while", "do", "true", "false", "null", "this", "return", "boolean", "int", "char", "void" };
    vector<char>symbols = { '-', '>', '<', '=', '.', ',', ';', '~', '*', '+', '/', '|', '&', '(', ')', '{', '}', '[', ']' };
    void processInputFile()
    {
        this->cin.open(this->currentPath + "\\" + this->currentFile + ".jack");
        this->cout.open(this->currentPath + "\\" + this->currentFile + "Tokins.txt");
        string line, spacedLine, word;
        bool isBlockComment = false, existSymbol;
        int newI;
        while (!cin.eof())
        {
            getline(cin, line);
            if (line.length()) //skip empty lines 
            {
                spacedLine = " ";
                for (int i = 0; i < line.size(); i += newI)//to make a space after&before a symbol
                {
                    existSymbol = false;
                    newI = 1;
                    for (auto it : this->symbols)
                    {
                        if (line[i] == it || line[i] == '\"')
                        {
                            existSymbol = true; spacedLine += ' ';
                            if (line[i] == '/' && i < line.size() - 1)//check is it a comment symbol or not
                            {
                                if (line[i + 1] == '/') { spacedLine += "// "; newI++; }
                                else if (line[i + 1] == '*')
                                {
                                    if (i < line.size() - 2 && line[i + 2] == '*') { spacedLine += "/** "; newI += 2; }
                                    else { spacedLine += "/* "; newI++; }
                                }
                                else { spacedLine += line[i]; spacedLine += ' '; }
                            }
                            else if (line[i] == '*' && i < line.size() - 1 && line[i + 1] == '/') { newI++; spacedLine += "*/ "; }
                            else { spacedLine += line[i]; spacedLine += ' '; }
                            if (line[i] == '\"')break;
                        }
                    }
                    if (!existSymbol)spacedLine += line[i];
                }
                //cout << spacedLine << endl;
                bool isString = false;
                int charCount = 0, startIndex = 0;
                istringstream streamLine(spacedLine);
                while (streamLine >> word) //check for every word if it belongs to a comment or to a command
                {
                    if (word == "/*" || word == "/**") { isBlockComment = true; continue; }
                    if (word == "*/") { isBlockComment = false; continue; }
                    if (word == "//")break; //skip whole comment line
                    if (!isBlockComment)
                    {
                        if (word == "\"") //to handle the strings
                        {
                            size_t quoteIndex = spacedLine.find(word, charCount);
                            charCount = quoteIndex + 2;
                            if (!isString) { startIndex = charCount; isString = true; }
                            else { isString = false; word = "\"" + spacedLine.substr(startIndex, quoteIndex - startIndex - 1) + "\""; }
                        }
                        if (!isString)this->processToken(word);
                    }
                }
            }
        }
        cin.close();
        cout.close();
    }
    void processToken(string token)
    {
        this->tokenType = this->setTokenType(token);
        cout << "<" << tokenType << "> ";
        if (tokenType == "symbol")
        {
            if (token == ">")token = "&gt;";
            if (token == "<")token = "&lt;";
            if (token == "&")token = "&amp;";
            if (token == "\"")token = "&quot;";
        }
        if (tokenType == "stringConstant")token = token.substr(1, token.size() - 2); //remove first,last double quotes
        cout << token << " </" << tokenType << ">\n";
    }
    string setTokenType(string token)
    {
        for (auto it : this->keywords) if (token == it) return "keyword";
        for (auto it : this->symbols)if (token == string(1, it)) return "symbol";
        if (token[0] == '\"' && token[token.size() - 1] == '\"')return "stringConstant";
        if (token[0] == '_' || (token[0] >= 'A' && token[0] <= 'Z') || (token[0] >= 'a' && token[0] <= 'z'))return "identifier";
        return "integerConstant";
    }
public:
    JackTokinizer(string currentPath, string currentFile)
    {
        this->currentPath = currentPath;
        this->currentFile = currentFile;
        this->processInputFile();
    }
};
class SymbolTable
{
private:
    string type, kind, tableType;
    int fieldCount, staticCount, argCount, lclCount;
    map<string, vector<string>> symbolTable;
public:
    void setType(string type)
    {
        this->type = type;
    }    
    void setKind(string kind)
    {
        this->kind = kind;
    }
    void addRow(string name)
    {
        int index;
        if (this->kind == "field") { this->fieldCount++; index = fieldCount; }
        if (this->kind == "static") { this->staticCount++; index = staticCount; }
        if (this->kind == "arg") { this->argCount++; index = argCount; }
        else { this->lclCount++; index = lclCount; }
        vector<string>v = { this->type,this->kind,to_string(index))};
        this->symbolTable[name] = v;
    }
    string getType(string name)
    {
        return this->symbolTable[name][0];
    }    
    string getKind(string name)
    {
        return this->symbolTable[name][1];
    }
    void clearTabel()
    {
        this->symbolTable.clear();
        if (this->tableType == "class") { this->fieldCount = 0; this->staticCount = 0; }
        else { this->argCount = 0; this->lclCount = 0; }
    }
public:
    SymbolTable(string tableType)
    {
        this->tableType = tableType;
    }
};
class VMWriter {
private:
    int labelID = 0, callID = 0; //unique id for eq,le,gt commands/call function command
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
            else newIndex = this->parser.getCurrentFile() + "." + to_string(segIndex + 16);
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
        cout << "(" << fName << ")\n";
        if (nVars != 0)
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
    void setWriteOperation(string commandType, string symbol, int index)
    {
        //write comment to define the VM command in asm file
        cout << "//" << commandType << endl;
        //generate asm code of the VM command
        if (commandType == "ARITHMETIC")this->writeArithmitic(symbol);
        else if (commandType == "PUSH" || commandType == "POP")this->writePushPop(commandType, symbol, index);
        else if (commandType == "LABEL" || commandType == "GOTO" || commandType == "IF-GOTO")this->writeBranching(commandType, symbol);
        else if (commandType == "FUNCTION")this->writeFunction(symbol, index);
        else if (commandType == "CALL")this->writeCall(symbol, index);
        else this->writeReturn();
    }
};
class CompileEngine
{
private:
    ofstream cout;
    ifstream cin;
    VMWriter codeWriter;
    string currentLine, word, className;
    vector<string>words, op = { "+","-","*","/","&amp;","|","&gt;","&lt;","=" };
    SymbolTable classTable,subroutineTable;
    int tabs = 0;
    void getNextLine()
    {
        words.clear();
        getline(cin, this->currentLine);
        istringstream streamLine(this->currentLine);
        while (streamLine >> word) words.push_back(word);
    }
    void process(string token, string tokenType)
    {
        if (words[0] != tokenType || (words[1] != token && (tokenType == "keyword" || tokenType == "symbol"))) { cout << "syntax error" << endl; return; }
        getNextLine();
    }
    void compileClass()
    {
        process("class", "<keyword>");
        this->className = this->words[1];
        process("className", "<identifier>");
        process("{", "<symbol>");
        while (words[1] == "static" || words[1] == "field")this->compileClassVarDec();
        while (words[1] == "constructor" || words[1] == "function" || words[1] == "method")this->compileSubroutineDec();
        process("}", "<symbol>");
    }
    void compileClassVarDec()
    {
        this->classTable.setKind(words[1]);
        getNextLine();
        this->classTable.setType(words[1]);
        processType();
        this->classTable.addRow(words[1]);
        checkMoreVars();
    }
    void processType(bool functionType = false)
    {
        if (words[1] == "int" || words[1] == "char" || words[1] == "boolean" || 
            words[0] == "<identifier>" || (words[1] == "void" && functionType))getNextLine();
        else { cout << "syntax error" << endl; return; }
    }
    void checkMoreVars()
    {
        process("varName", "<identifier>");
        while (words[1] == ",") { process(",", "<symbol>"); this->classTable.addRow(words[1]); process("varName", "<identifier>"); }
        process(";", "<symbol>");
    }
    void processVarDec()
    {
        process("var", "<keyword>");
        this->classTable.setKind("local");
        this->classTable.setType(words[1]);
        processType();
        this->classTable.addRow(words[1]);
        checkMoreVars();
    }
    void compileSubroutineDec()
    {
        getNextLine();
        processType(true);
        process("subroutineName", "<identifier>");
        process("(", "<symbol>");
        processParameterList();
        process(")", "<symbol>");
        processSubroutineBody();
    }
    void processParameterList()
    {
        while (words[1] != ")")
        {
            this->classTable.setKind("arg");
            this->classTable.setType(words[1]);
            processType();
            this->classTable.addRow(words[1]);
            process("varName", "<identifier>");
            if (words[1] == ",") { process(",", "<symbol>"); }
        }
    }
    void processSubroutineBody()
    {
        process("{", "<symbol>");
        while (words[1] == "var") { processVarDec(); }
        processStatments();
        process("}", "<symbol>");
    }
    void processStatments()
    {
        while (words[1] != "}")
        {
            if (words[1] == "let")processLetStatment();
            else if (words[1] == "if")processIfStatment();
            else if (words[1] == "do")processDoStatment();
            else if (words[1] == "while")processWhileStatment();
            else if (words[1] == "return")processReturnStatment();
            else break;
        }
    }
    void processLetStatment()
    {
        process("let", "<keyword>");
        process("varName", "<identifier>");
        if (words[1] == "[") { process("[", "<symbol>"); processExpression("]"); process("[", "<symbol>"); }
        process("=", "<symbol>");
        processExpression(";");
        process(";", "<symbol>");
    }
    void processExpression(string endSymbol)
    {
        while (words[1] != endSymbol)
        {
            processTerm();
            bool check = false;
            for (auto it : op)
            {
                if (words[1] == it) { check = true; printXML(this->currentLine); getNextLine(); break; }
            }
            if (!check)break;
        }
    }
    void processTerm()
    {
        printXML(this->currentLine);
        if (words[1] == "(") { getNextLine(); processExpression(")"); process(")", "<symbol>"); }
        else
        {
            if (words[0] == "<identifier>")
            {
                getNextLine();
                if (words[1] == "[") { process("[", "<symbol>"); processExpression("]");  process("]", "<symbol>"); }
                else if (words[1] == "." || words[1] == "(") { processSubroutineCall(); }
            }
            else if (words[1] == "~" || words[1] == "-") { getNextLine(); processTerm(); }
            else getNextLine();
        }
    }
    void processSubroutineCall()
    {
        printXML(this->currentLine);
        string curSymbol = words[1];
        getNextLine();
        if (curSymbol == "(") { processExpressionList(); process(")", "<symbol>"); }
        else if (curSymbol == ".")
        {
            process("subroutineName", "<identifier>");
            process("(", "<symbol>");
            processExpressionList();
            process(")", "<symbol>");
        }
    }
    void processExpressionList()
    {
        while (words[1] != ")") { processExpression(","); if (words[1] == ",") process(",", "<symbol>"); }
    }
    void processIfStatment()
    {
        process("if", "<keyword>");
        process("(", "<symbol>");
        processExpression(")");
        process(")", "<symbol>");
        process("{", "<symbol>");
        processStatments();
        process("}", "<symbol>");
        checkElseStatment();
    }
    void checkElseStatment()
    {
        if (words[1] == "else")
        {
            process("else", "<keyword>");
            process("{", "<symbol>");
            processStatments();
            process("}", "<symbol>");
        }
    }
    void processDoStatment()
    {
        process("do", "<keyword>");
        process("subroutineName", "<identifier>");
        processSubroutineCall();
        process(";", "<symbol>");
    }
    void processWhileStatment()
    {
        process("while", "<keyword>");
        process("(", "<symbol>");
        processExpression(")");
        process(")", "<symbol>");
        process("{", "<symbol>");
        processStatments();
        process("}", "<symbol>");
    }
    void processReturnStatment()
    {
        process("return", "<keyword>");
        if (words[1] != ";")processExpression(";");
        process(";", "<symbol>");
    }
public:
    CompileEngine(string currentPath, string currentFile)
    {
        this->classTable = new SymbolTable("class");
        this->subroutineTable = new SymbolTable("subroutine");
        this->cin.open(currentPath + "\\" + currentFile + "Tokins.txt");
        this->cout.open(currentPath + "\\" + currentFile + ".vm");
        getNextLine();
        this->compileClass();
    }
};
int main()
{
    vector<string>jackFiles;
    string ext = ".jack";
    string path = "D:\\nand2tetris\\nand2tetris\\projects\\10\\Square";
    try { //to get all jack files in the path directory
        for (const auto& entry : filesystem::directory_iterator(path)) {
            filesystem::path systemPath = entry.path();
            string fileName = systemPath.filename().string();
            if (fileName.substr(fileName.size() - 5, 5) == ext)
            {
                fileName.erase(fileName.size() - 5);
                jackFiles.push_back(fileName);
            }
        }
    }
    catch (const filesystem::filesystem_error& e) {
        cerr << "Filesystem error: " << e.what() << endl;
    }
    for (string jackFile : jackFiles)
    {
        JackTokinizer tokinizer(path, jackFile);
        CompileEngine engine(path, jackFile);
    }
}