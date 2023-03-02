#ifndef SYNTAXANALYZER_H
#define SYNTAXANALYZER_H

#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"

using namespace std;

class SyntaxAnalyzer
{
  private:
    LexicalAnalyzer *la;
    Token *currentToken;
    TokenCodes nextTokenCode;
    int TokenPos = 0;
    bool error = false;

  public:
    Token* GetToken();
    int getTokenPosition();
    void setTokenPosition(int i);
    void Accept(TokenCodes t);
    SyntaxAnalyzer(LexicalAnalyzer*);
    void Program();
    void ErrorMessege();

    void DECPART();
    void DECLARATIONS();
    void DECLARATION();
    void IDENTLIST();
    void COMPSTMT();
    void SEQOFSTMT();
    void BLOCK();
    void STATEMENT();
    void EXPRESSION();
    void SIMPEXPR();
    void TERM();
    void FACTOR();
    void PRIMARY();
};

#endif
