#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <fstream>
#include <list>
#include "Token.h"
#include "TokenCodes.h"

using namespace std;

class LexicalAnalyzer
{
private:
    ifstream* sourceCodeFile;

    list<string> lines;
    Token* currentToken;
    int currentLine = 0;        //save current line
    string lexeme;              //one getting returned
    int count = 0;
    int nextTokenPosition = 0;
    int currentTokenPosition = 0;



public:
    LexicalAnalyzer(ifstream*);
    Token* getNextToken();
    string getNextString();

    string getLine(int i);
    string getCurrentLine();
    Token* getCurrentToken();
    void nextToken();

    void printLines();
    bool isToken(string str);

    int getnextTokenPosition();
    int getcurrentTokenPosition();
    void setcurrentTokenPosition(int);

};

#endif
