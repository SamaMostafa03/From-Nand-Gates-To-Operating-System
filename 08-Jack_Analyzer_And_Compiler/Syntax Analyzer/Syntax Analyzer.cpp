// Jack Syntax Analyzer.cpp built to translates Jack code into a XML parse tree.
//TODO: Rewrite main
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <filesystem>
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
        this->cout.open(this->currentPath + "\\" + this->currentFile + "Test.txt");
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

class CompileEngine
{
private:
    ofstream cout;
    ifstream cin;
    string currentLine, word;
    vector<string>v, op = { "+","-","*","/","&amp;","|","&gt;","&lt;","=" };
    int tabs = 0;
    void getNextLine()
    {
        v.clear();
        getline(cin, this->currentLine);
        istringstream streamLine(this->currentLine);
        while (streamLine >> word) v.push_back(word);
    }
    void process(string token, string tokenType)
    {
        if (v[0] != tokenType || (v[1] != token && (tokenType == "keyword" || tokenType == "symbol"))) { cout << "wroooong process" << endl; return; }
        this->printXML(this->currentLine);
        getNextLine();
    }
    void printXML(string line)
    {
        for (int i = 0; i < this->tabs; i++)cout << "\t";
        cout << line << endl;
    }
    void compileClass()
    {
        printXML("<class>");
        tabs++;
        process("class", "<keyword>");
        process("className", "<identifier>");
        process("{", "<symbol>");
        while (v[1] == "static" || v[1] == "field")this->compileClassVarDec();
        while (v[1] == "constructor" || v[1] == "function" || v[1] == "method")this->compileSubroutineDec();
        process("}", "<symbol>");
        tabs--;
        printXML("</class>");
    }
    void compileClassVarDec()
    {
        printXML("<classVarDec>");
        tabs++;
        this->printXML(this->currentLine);
        getNextLine();
        processType();
        checkMoreVars();
        tabs--;
        printXML("</classVarDec>");
    }
    void processType(bool functionType = false)
    {
        if (v[1] == "int" || v[1] == "char" || v[1] == "boolean" || v[0] == "<identifier>")this->printXML(this->currentLine);
        else if (v[1] == "void" && functionType)this->printXML(this->currentLine);
        else cout << "wroong type";
        getNextLine();
    }
    void checkMoreVars()
    {
        process("varName", "<identifier>");
        while (v[1] == ",") { process(",", "<symbol>"); process("varName", "<identifier>"); }
        process(";", "<symbol>");
    }
    void processVarDec()
    {
        printXML("<varDec>");
        tabs++;
        process("var", "<keyword>");
        processType();
        checkMoreVars();
        tabs--;
        printXML("</varDec>");
    }
    void compileSubroutineDec()
    {
        printXML("<subroutineDec>");
        tabs++;
        this->printXML(this->currentLine);
        getNextLine();
        processType(true);
        process("subroutineName", "<identifier>");
        process("(", "<symbol>");
        processParameterList();
        process(")", "<symbol>");
        processSubroutineBody();
        tabs--;
        printXML("</subroutineDec>");
    }
    void processParameterList()
    {
        printXML("<parameterList>");
        tabs++;
        while (v[1] != ")")
        {
            processType();
            process("varName", "<identifier>");
            if (v[1] == ",") { process(",", "<symbol>"); }
        }
        tabs--;
        printXML("</parameterList>");
    }
    void processSubroutineBody()
    {
        printXML("<subroutineBody>");
        tabs++;
        process("{", "<symbol>");
        while (v[1] == "var") { processVarDec(); }
        processStatments();
        process("}", "<symbol>");
        tabs--;
        printXML("</subroutineBody>");
    }
    void processStatments()
    {
        printXML("<statements>");
        tabs++;
        while (v[1] != "}")
        {
            if (v[1] == "let")processLetStatment();
            else if (v[1] == "if")processIfStatment();
            else if (v[1] == "do")processDoStatment();
            else if (v[1] == "while")processWhileStatment();
            else if (v[1] == "return")processReturnStatment();
            else break;
        }
        tabs--;
        printXML("</statements>");
    }
    void processLetStatment()
    {
        printXML("<letStatement>");
        tabs++;
        process("let", "<keyword>");
        process("varName", "<identifier>");
        if (v[1] == "[") { process("[", "<symbol>"); processExpression("]"); process("[", "<symbol>"); }
        process("=", "<symbol>");
        processExpression(";");
        process(";", "<symbol>");
        tabs--;
        printXML("</letStatement>");
    }
    void processExpression(string endSymbol)
    {
        printXML("<expression>");
        tabs++;
        while (v[1] != endSymbol)
        {
            processTerm();
            bool check = false;
            for (auto it : op)
            {
                if (v[1] == it) { check = true; printXML(this->currentLine); getNextLine(); break; }
            }
            if (!check)break;
        }
        tabs--;
        printXML("</expression>");
    }
    void processTerm()
    {
        printXML("<term>");
        tabs++;
        printXML(this->currentLine);
        if (v[1] == "(") { getNextLine(); processExpression(")"); process(")", "<symbol>"); }
        else
        {
            if (v[0] == "<identifier>")
            {
                getNextLine();
                if (v[1] == "[") { process("[", "<symbol>"); processExpression("]");  process("]", "<symbol>"); }
                else if (v[1] == "." || v[1] == "(") { processSubroutineCall(); }
            }
            else if (v[1] == "~" || v[1] == "-") { getNextLine(); processTerm(); }
            else getNextLine();
        }
        tabs--;
        printXML("</term>");
    }
    void processSubroutineCall()
    {
        printXML(this->currentLine);
        string curSymbol = v[1];
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
        printXML("<expressionList>");
        tabs++;
        while (v[1] != ")") { processExpression(","); if (v[1] == ",") process(",", "<symbol>"); }
        tabs--;
        printXML("</expressionList>");
    }
    void processIfStatment()
    {
        printXML("<ifStatement>");
        tabs++;
        process("if", "<keyword>");
        process("(", "<symbol>");
        processExpression(")");
        process(")", "<symbol>");
        process("{", "<symbol>");
        processStatments();
        process("}", "<symbol>");
        checkElseStatment();
        tabs--;
        printXML("</ifStatement>");
    }
    void checkElseStatment()
    {
        if (v[1] == "else")
        {
            process("else", "<keyword>");
            process("{", "<symbol>");
            processStatments();
            process("}", "<symbol>");
        }
    }
    void processDoStatment()
    {
        printXML("<doStatement>");
        tabs++;
        process("do", "<keyword>");
        process("subroutineName", "<identifier>");
        processSubroutineCall();
        process(";", "<symbol>");
        tabs--;
        printXML("</doStatement>");
    }
    void processWhileStatment()
    {
        printXML("<whileStatement>");
        tabs++;
        process("while", "<keyword>");
        process("(", "<symbol>");
        processExpression(")");
        process(")", "<symbol>");
        process("{", "<symbol>");
        processStatments();
        process("}", "<symbol>");
        tabs--;
        printXML("</whileStatement>");
    }
    void processReturnStatment()
    {
        printXML("<returnStatement>");
        tabs++;
        process("return", "<keyword>");
        if (v[1] != ";")processExpression(";");
        process(";", "<symbol>");
        tabs--;
        printXML("</returnStatement>");
    }
public:
    CompileEngine(string currentPath, string currentFile)
    {
        this->cin.open(currentPath + "\\" + currentFile + "Test.txt");
        this->cout.open(currentPath + "\\" + currentFile + ".xml");
        getNextLine();
        this->compileClass();
    }
};

int main()
{
    vector<string>jackFiles;
    string ext = ".jack";
    string path = "D:\\nand2tetris\\nand2tetris\\projects\\11\\ConvertToBin";
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