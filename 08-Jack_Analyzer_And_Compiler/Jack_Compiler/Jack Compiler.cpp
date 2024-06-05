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
    int getIndex(string name)
    {
        return this->symbolTable[name][2];
    }
    void clearTabel()
    {
        this->symbolTable.clear();
        if (this->tableType == "class") { this->fieldCount = 0; this->staticCount = 0; }
        else { this->argCount = 0; this->lclCount = 0; }
    }
    bool checkIdentifier(string name)
    {
        for (auto it : symbolTable)
        {
            if (it.first == name)return true;
        }
        return false;
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
    void writeArithmitic(char symbol)
    {
        switch (symbol) {
        case '+':
            cout << "add";
            break;
        case '-':
            cout << "sub";
            break;
        case '=':
            cout << "eq";
            break;
        case '>':
            cout << "gt";
            break;        
        case '<':
            cout << "lt";
            break; 
        case '~':
            cout << "not";
            break; 
        case '&':
            cout << "and";
            break; 
        case '|':
            cout << "or";
            break; 
        case '*':
            this->writeCall("Math.multiply", 2);
            break;
        case '/':
            this->writeCall("Math.divide", 2);
            break;         
        default:
            cout << "neg";
        }
        cout << endl;
    }
    void writePushPop(string commandType, string segment, int segIndex)
    {
        cout << commandType << segment << " " << segIndex << endl;
    }
    void writeBranching(string commandType, string label)
    {
        if (commandType != "label")cout << "\t";
        cout << commandType << " " << label<< endl;
    }
    void writeFunction(string fName, int nVars)
    {
        cout << "function " << fname << " " << nVars<< endl;
    }
    void writeCall(string fName, int nArg)
    {
        cout << "\tcall " << fname << " " << nArg << endl;
    }
    void writeReturn()
    {
        cout << "\treturn";
    }
public:
    void setWriteOperation(string commandType, string symbol, int index)
    {
        //write comment to define the VM command in asm file
        cout << "//" << commandType << endl;
        //generate asm code of the VM command
        if (commandType == "ARITHMETIC")this->writeArithmitic(symbol[0]);
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
    string currentLine, word, className, identifier, index, kind;
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
        if (words[1] == "method")
        {
            //add row
        }
        getNextLine();
        processType(true);
        string fname = words[1];
        process("subroutineName", "<identifier>");
        process("(", "<symbol>");
        int nArg = processParameterList();
        process(")", "<symbol>");
        codeWriter.setWriteOperation("function", fname, index);
        processSubroutineBody();
    }
    int processParameterList()
    {
        int counter = 0;
        while (words[1] != ")")
        {
            counter++;
            this->classTable.setKind("arg");
            this->classTable.setType(words[1]);
            processType();
            this->classTable.addRow(words[1]);
            process("varName", "<identifier>");
            if (words[1] == ",") { process(",", "<symbol>"); }
        }
        return counter;
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
        identifier = words[1];
        process("varName", "<identifier>");
        if (words[1] == "[") { process("[", "<symbol>"); processExpression("]"); process("[", "<symbol>"); }
        codeWriter.setWriteOperation("ARITHMETIC", "=", 0);
        process("=", "<symbol>");
        processExpression(";");
        setIdentifier(identifier);
        codeWriter.setWriteOperation("pop",kind,index)
        process(";", "<symbol>");
    }
    void setIdentifier(string identifier)
    {
        if (classTable.checkIdentifier(identifier))
        {
            index = classTable.getIndex(identifier);
            kind = classTable.getKind(identifier);
        }
        else
        {
            index = subroutineTable.getIndex(identifier);
            kind = subroutineTable.getKind(identifier);
        }
    }
    void processExpression(string endSymbol)
    {
        string operator;
        bool check = false;
        while (words[1] != endSymbol)
        {
            processTerm();
            if (check)
            {
                if (operator=="&amp;")operator="&";
                else if (operator=="&gt;")operator=">";
                else if (operator=="&lt;")operator="<";
                codeWriter.setWriteOperation("ARITHMETIC", operator,0);
            }
            check = false;
            for (auto it : op)
            {
                if (words[1] == it) { check = true; operator = op; getNextLine(); break; }
            }
            if (!check)break;
        }
    }
    void processTerm()
    {
        if (words[1] == "(") { getNextLine(); processExpression(")"); process(")", "<symbol>"); }
        else
        {
            if (words[0] == "<identifier>")
            {
                identifier = words[1];
                getNextLine();
                if (words[1] == "[") 
                { 
                    process("[", "<symbol>"); 
                    processExpression("]");  
                    process("]", "<symbol>"); 
                }
                else if (words[1] == "." || words[1] == "(") 
                { 
                    processSubroutineCall(); 
                    codeWriter.setWriteOperation("call", identifier, index);
                }
                else
                {
                    setIdentifier(identifier);
                    codeWriter.setWriteOperation("push", kind, index);
                }
            }
            else if (words[1] == "~" || words[1] == "-") 
            { 
                string unaryOP = words[1]; 
                if (unaryOP == "-")unaryOP = "_";
                getNextLine(); 
                processTerm(); 
                codeWriter.setWriteOperation("ARITHMETIC", unaryOP, 0); 
            }
            else 
            {
                if (words[0] == "integerConstant")
                {
                    codeWriter.setWriteOperation("push", "constant", words[1]);
                }
                else if (words[0] == "stringConstant")
                {
                    identifier = words[1];
                    codeWriter.setWriteOperation("push", "constant", identifier.size());
                    codeWriter.setWriteOperation("call", "String.new", 1);
                    for (int i = 0; i < identifier.size(); i++)
                    {
                        codeWriter.setWriteOperation("push", "constant", identifier[i]-'0');
                        codeWriter.setWriteOperation("call", "String.appendChar", 1);
                    }
                }
                else
                {
                    if (words[1] == "true")
                    {
                        codeWriter.setWriteOperation("push", "constant", 1);
                        codeWriter.setWriteOperation("ARITHMETIC", "_", 0);
                    }
                    else if (words[1] == "false" || words[1]=="null")
                    {
                        codeWriter.setWriteOperation("push", "constant", 0);
                    }
                    else if(words[1] == "this")
                    {
                        codeWriter.setWriteOperation("push", "pointer", 0);
                    }
                }
                getNextLine();

            }
        }
    }
    void processSubroutineCall()
    {
        string curSymbol = words[1];
        getNextLine();
        if (curSymbol == "(") { processExpressionList(); process(")", "<symbol>"); }
        else if (curSymbol == ".")
        {
            identifier += "." + words[1];
            process("subroutineName", "<identifier>");
            process("(", "<symbol>");
            processExpressionList();
            process(")", "<symbol>");
        }
    }
    void processExpressionList()
    {
        index = 0;
        while (words[1] != ")") { index++; processExpression(","); if (words[1] == ",") process(",", "<symbol>"); }
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