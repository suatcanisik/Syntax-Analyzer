#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"

using namespace std;
int SyntaxAnalyzer::getTokenPosition() {
	return TokenPos;
}
void SyntaxAnalyzer::setTokenPosition(int i) {
	this->TokenPos = i;
}

void SyntaxAnalyzer::Accept(TokenCodes t) {
	if (la->getCurrentToken()->getTokenCode() == t) {
		cout << " Good token : " << la->getCurrentToken()->getLexemeString() << endl;
		la->nextToken();
		if (la->getCurrentToken()->getTokenCode() == EOI) {
			cout << "File is gramatically correct"<< endl;
			exit(0);
		}
	}
	else {
		
		ErrorMessege();
		string s = "";
		if (t == PLUS) {
			s = "plus";
		}else if (t == MINUS) {
			s = "minus";
		}else if (t == TIMES) {
			s = "times";
		}
		else if (t == SLASH) {
			s = "slash";
		}
		else if (t == EQL) {
			s = "equal sign";
		}
		else if (t == LPAREN) {
			s = "left parenthesis";
		}
		else if (t == RPAREN) {
			s = "right parenthesis";
		}
		else if (t == PERIOD) {
			s = "period";
		}
		else if (t == COMMA) {
			s = "comma";
		}
		else if (t == SEMICOLON) {
			s = "comm";
		}
		else if (t ==COLON) {
			s = "colon";
		}
		else if (t == BECOMES) {
			s = "becomes";
		}
		else if (t == LSS) {
			s = "less than sign";
		}
		else if (t == LEQ) {
			s = "less then or equal to";
		}
		else if (t == NEQ) {
			s = "not equal";
		}
		else if (t == GTR) {
			s = "greater than";
		}
		else if (t == GEQ) {
			s = "greater than or equal to";
		}
		else if (t == ANDSYM) {
			s = "and";
		}
		else if (t == BEGINSYM) {
			s = "begin";
		}
		else if (t == BOOLSYM) {
			s = "boolean";
		}
		else if (t == DIVSYM) {
			s = "div";
		}
		else if (t == DOSYM) {
			s = "do";
		}
		else if (t == DOWNTOSYM) {
			s = "downto";
		}
		else if (t == ELSESYM) {
			s = "else";
		}
		else if (t == ENDSYM) {
			s = "end";
		}
		else if (t == FALSESYM) {
			s = "false";
		}
		else if (t == FORSYM) {
			s = "for";
		}
		else if (t == IFSYM) {
			s = "if";
		}
		else if (t == INTSYM) {
			s = "int";
		}
		else if (t == MODSYM) {
			s = "mod";
		}
		else if (t == NOTSYM) {
			s = "not";
		}
		else if (t == ORSYM) {
			s = "or";
		}
		else if (t == PROGSYM) {
			s = "program";
		}
		else if (t == READSYM) {
			s = "read";
		}
		else if (t == READLNSYM) {
			s = "readln";
		}
		else if (t == REALSYM) {
			s = "real";
		}
		else if (t == REPEATSYM) {
			s = "repeat";
		}
		else if (t == THENSYM) {
			s = "then";
		}
		else if (t ==TOSYM) {
			s = "to";
		}
		else if (t == TRUESYM) {
			s = "true";
		}
		else if (t == UNTILSYM) {
			s = "until";
		}
		else if (t == VARSYM) {
			s = "var";
		}
		else if (t == WHILESYM) {
			s = "while";
		}
		else if (t == WRITESYM) {
			s = "write";
		}
		else if (t == WRITELNSYM) {
			s = "writeln";
		}
		else if (t == IDENT) {
			s = "identifier";
		}
		else if (t ==NUMLIT) {
			s = "numeric litteral";
		}
		//cout << "=========" << la->getCurrentToken()->getTokenCode() << "  -  " << s << endl;
		cout << "Error: " << s << " expected. But token is "<< la->getCurrentToken()->getLexemeString() << endl;
		exit(0);
	}
}
void SyntaxAnalyzer::Program()
{
	cout << endl << "--------------------------------------program" << endl;

	la->nextToken();

	Accept(PROGSYM);
	Accept(IDENT);
	Accept(SEMICOLON);
	DECPART();
	COMPSTMT();
	Accept(PERIOD);
	Accept(EOI);
}

SyntaxAnalyzer::SyntaxAnalyzer(LexicalAnalyzer *l)
{
	this->la = l;
	cout << "---------------------------------------------syntex analyzer " << endl;
	Program();
}

void SyntaxAnalyzer::ErrorMessege() {
	cout << endl << la->getCurrentLine() << endl;

	for (int i = 0; i < la->getcurrentTokenPosition();i++) {
		cout << " ";
	}
	cout << "^"<< endl;
	la->setcurrentTokenPosition(la->getnextTokenPosition());
}


void SyntaxAnalyzer::DECPART() {
	if (la->getCurrentToken()->getTokenCode() == VARSYM) {
		Accept(VARSYM);
		DECLARATIONS();
	}
}
void SyntaxAnalyzer::DECLARATIONS() {
	DECLARATION();
	if (la->getCurrentToken()->getTokenCode() == IDENT) {
		DECLARATION();
		DECLARATIONS();
	}
}
void SyntaxAnalyzer::DECLARATION() {
	IDENTLIST();
	Accept(COLON);
	if (la->getCurrentToken()->getTokenCode() == BOOLSYM) {
		Accept(BOOLSYM);
		Accept(SEMICOLON);
	}
	else if (la->getCurrentToken()->getTokenCode() == INTSYM) {
		Accept(INTSYM);
		Accept(SEMICOLON);
	}
	else if (la->getCurrentToken()->getTokenCode() == REALSYM) {
		Accept(REALSYM);
		Accept(SEMICOLON);
	}
}
void SyntaxAnalyzer::IDENTLIST() {
	Accept(IDENT);
	if (la->getCurrentToken()->getTokenCode() == COMMA) {
		Accept(COMMA);
		IDENTLIST();
	}
}
void SyntaxAnalyzer::COMPSTMT() {
	Accept(BEGINSYM);
	SEQOFSTMT();
	Accept(ENDSYM);
}
void SyntaxAnalyzer::SEQOFSTMT() {
	STATEMENT();
	if (la->getCurrentToken()->getTokenCode() == SEMICOLON) {
		Accept(SEMICOLON);
		SEQOFSTMT();
	}
}
void SyntaxAnalyzer::BLOCK() {
	if (la->getCurrentToken()->getTokenCode() == BEGINSYM) {
		COMPSTMT();
	}
	else {
		STATEMENT();
	}
}
void SyntaxAnalyzer::STATEMENT() {
	if (la->getCurrentToken()->getTokenCode() == FORSYM) {
		Accept(FORSYM);
		Accept(IDENT);
		Accept(BECOMES);
		EXPRESSION();
		if (la->getCurrentToken()->getTokenCode() == TOSYM) {
			Accept(TOSYM);
			EXPRESSION();
			Accept(DOSYM);
			BLOCK();
		}else{
			Accept(DOWNTOSYM);
			EXPRESSION();
			Accept(DOSYM);
			BLOCK();
		}
	}
	else if (la->getCurrentToken()->getTokenCode() == IDENT) {
		Accept(IDENT);
		Accept(BECOMES);
		EXPRESSION();
	}
	else if (la->getCurrentToken()->getTokenCode() == IFSYM) {
		Accept(IFSYM);
		EXPRESSION();
		Accept(THENSYM);
		BLOCK();
		if (la->getCurrentToken()->getTokenCode() == ELSESYM) {
			Accept(ELSESYM);
			BLOCK();
		}
	}
	else if (la->getCurrentToken()->getTokenCode() == REPEATSYM) {
		Accept(REPEATSYM);
		SEQOFSTMT();
		Accept(UNTILSYM);
		EXPRESSION();
	}	
	else if (la->getCurrentToken()->getTokenCode() == WHILESYM) {
		Accept(WHILESYM);
		EXPRESSION();
		Accept(DOSYM);
		BLOCK();
	}
	else if (la->getCurrentToken()->getTokenCode() == READSYM) {
		Accept(READSYM);
		Accept(LPAREN);
		IDENTLIST();
		Accept(RPAREN);
	}
	else if (la->getCurrentToken()->getTokenCode() == READLNSYM) {
		Accept(READLNSYM);
		Accept(LPAREN);
		IDENTLIST();
		Accept(RPAREN);
	}
	else if (la->getCurrentToken()->getTokenCode() == WRITESYM) {
		Accept(WRITESYM);
		Accept(LPAREN);
		IDENTLIST();
		Accept(RPAREN);
	}
	else if (la->getCurrentToken()->getTokenCode() == WRITELNSYM) {
		Accept(WRITELNSYM);
		Accept(LPAREN);
		IDENTLIST();
		Accept(RPAREN);
	}
}
void SyntaxAnalyzer::EXPRESSION() {
	SIMPEXPR();
	if (la->getCurrentToken()->getTokenCode() == EQL) {
		Accept(EQL);
		SIMPEXPR();
	}
	else if (la->getCurrentToken()->getTokenCode() == LSS) {
		Accept(LSS);
		if (la->getCurrentToken()->getTokenCode() == GTR) {
			Accept(GTR);
		}
		SIMPEXPR();
	}
	else if (la->getCurrentToken()->getTokenCode() == LEQ) {
		Accept(LEQ);
		SIMPEXPR();
	}
	else if (la->getCurrentToken()->getTokenCode() == GTR) {
		Accept(GTR);
		SIMPEXPR();
	}
	else if (la->getCurrentToken()->getTokenCode() == GEQ) {
		Accept(GEQ);
		SIMPEXPR();
	}
}
void SyntaxAnalyzer::SIMPEXPR() {
	if (la->getCurrentToken()->getTokenCode() == NOTSYM ||
		la->getCurrentToken()->getTokenCode() == IDENT ||
		la->getCurrentToken()->getTokenCode() == NUMLIT ||
		la->getCurrentToken()->getTokenCode() == TRUESYM ||
		la->getCurrentToken()->getTokenCode() == FALSESYM
		) {
		TERM();
	}
	else if (la->getCurrentToken()->getTokenCode() == PLUS) {
		Accept(PLUS);
		TERM();
	}
	else if (la->getCurrentToken()->getTokenCode() == MINUS) {
		Accept(MINUS);
		TERM();
	}
	else if (la->getCurrentToken()->getTokenCode() == ORSYM) {
		Accept(ORSYM);
		TERM();
	}
	
}
void SyntaxAnalyzer::TERM() {
	if (la->getCurrentToken()->getTokenCode() == NOTSYM ||
		la->getCurrentToken()->getTokenCode() == IDENT ||
		la->getCurrentToken()->getTokenCode() == NUMLIT ||
		la->getCurrentToken()->getTokenCode() == TRUESYM ||
		la->getCurrentToken()->getTokenCode() == FALSESYM
		) {
		FACTOR();
	}else if(la->getCurrentToken()->getTokenCode() ==	TIMES){
		Accept(TIMES);
		FACTOR();
	}
	else if (la->getCurrentToken()->getTokenCode() == SLASH) {
		Accept(SLASH);
		FACTOR();
	}
	else if (la->getCurrentToken()->getTokenCode() == DIVSYM) {
		Accept(DIVSYM);
		FACTOR();
	}
	else if (la->getCurrentToken()->getTokenCode() == MODSYM) {
		Accept(MODSYM);
		FACTOR();
	}
	else if (la->getCurrentToken()->getTokenCode() == ANDSYM) {
		Accept(ANDSYM);
		FACTOR();
	}
}
void SyntaxAnalyzer::FACTOR() {
	if(la->getCurrentToken()->getTokenCode() == NOTSYM) {
		Accept(NOTSYM);
	}
	PRIMARY();
}
void SyntaxAnalyzer::PRIMARY() {
	if (la->getCurrentToken()->getTokenCode() == LPAREN) {
		Accept(LPAREN);
		EXPRESSION();
		Accept(RPAREN);
	}
	else if (la->getCurrentToken()->getTokenCode() == IDENT) {
		Accept(IDENT);
	}
	else if (la->getCurrentToken()->getTokenCode() == NUMLIT) {
		Accept(NUMLIT);
	}
	else if (la->getCurrentToken()->getTokenCode() == TRUESYM) {
		Accept(TRUESYM);
	}
	else if (la->getCurrentToken()->getTokenCode() == FALSESYM) {
		Accept(FALSESYM);
	}

}

