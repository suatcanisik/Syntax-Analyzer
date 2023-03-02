#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCodes.h"


using namespace std;




void LexicalAnalyzer::nextToken(){

	currentToken = getNextToken();
	while (currentToken->getLexemeString() == " " || currentToken->getLexemeString() == "NEW_LINE") {
		currentToken = getNextToken();
	}
}

LexicalAnalyzer::LexicalAnalyzer(ifstream* scf)
{

	cout << "-------------------In the LexicalAnalyzer" << endl;
	nextTokenPosition = 0;
	this->sourceCodeFile = scf;
	string line;
	while (getline(*sourceCodeFile, line)) {
		lines.push_back(line);
	}
	printLines();

}

void LexicalAnalyzer::printLines() {
	for (int i = 0; i <= lines.size() - 1; i++) {
		cout << getLine(i) << endl;
	}
}

string LexicalAnalyzer::getLine(int s) {
	list<string>::iterator t = lines.begin();
	for (int i = 0; i < s; i++) {
		++t;
	}
	return *t;
}

string LexicalAnalyzer::getCurrentLine() {
	list<string>::iterator t = lines.begin();
	for (int i = 0; i < currentLine; i++) {
		++t;
	}
	return *t;
}

bool LexicalAnalyzer::isToken(string str) {
	if (
		str == " " ||
		str == "+" ||
		str == "." ||
		str == "%" ||
		str == "-" ||
		str == "*" ||
		str == "=" ||
		str == "(" ||
		str == ")" ||
		str == "," ||
		str == ";" ||
		str == "/" ||
		str == "/=" ||
		str == "!=" ||
		str == ":" ||
		str == ":=" ||
		str == "<" ||
		str == "<=" ||
		str == ">" ||
		str == ">=") {
		//cout << str << " is token" << endl;
		return true;
	}
	else {
		//cout << str << " is not token" << endl;
		return false;
	}
}

bool isDouble(string t)
{
	string::const_iterator num = t.begin();
	while (num != t.end() && isdigit(*num)) ++num;
	return !t.empty() && num == t.end();
}

Token* LexicalAnalyzer::getNextToken()
{

	lexeme = "";

	//end of input
	if (currentLine >= lines.size()) {
		Token* t = new Token(EOI, "EOI");
		return t;
	}

	string lexeme = getNextString();


	//cout << "lexeme :"  << lexeme << endl;
	
	//end of line
	if (lexeme == "NEW_LINE") {
		currentLine++;
		Token* t = new Token(NAL, "NEW_LINE");
		return t;
	}
	else if (lexeme == " ") {
		Token* t = new Token(NAL, " ");
		return t;
	}
	else if (lexeme == "or") {
		Token* t = new Token(NAL, "or");
		return t;
	}
	else if (lexeme == "&") {
		Token* t = new Token(NAL, "&");
		return t;
	}
	else if (lexeme == "+") {
		Token* t = new Token(PLUS, "+");
		return t;
	}
	else if (lexeme == "-") {
		Token* t = new Token(MINUS, "-");
		return t;
	}
	else if (lexeme == "*") {
		Token* t = new Token(TIMES, "*");
		return t;
	}
	else if (lexeme == "=") {
		Token* t = new Token(EQL, "=");
		return t;
	}
	else if (lexeme == "(") {
		Token* t = new Token(LPAREN, "(");
		return t;
	}
	else if (lexeme == ")") {
		Token* t = new Token(RPAREN, ")");
		return t;
	}
	else if (lexeme == ",") {
		Token* t = new Token(COMMA, ",");
		return t;
	}
	else if (lexeme == ";") {
		Token* t = new Token(SEMICOLON, ";");
		return t;
	}
	else if (lexeme == "/") {
		Token* t = new Token(SLASH, "/");
		return t;
	}
	else if (lexeme == "/=") {
		Token* t = new Token(NEQ, "/=");
		return t;
	}
	else if (lexeme == ":") {
		Token* t = new Token(COLON, ":");
		return t;
	}
	else if (lexeme == ":=") {
		Token* t = new Token(BECOMES, ":=");
		return t;
	}
	else if (lexeme == "<") {
		Token* t = new Token(LSS, "<");
		return t;
	}
	else if (lexeme == "<=") {
		Token* t = new Token(LEQ, "<=");
		return t;
	}
	else if (lexeme == ">") {
		Token* t = new Token(GTR, ">");
		return t;
	}
	else if (lexeme == ">=") {
		Token* t = new Token(GEQ, ">=");
		return t;
	}
	else if (lexeme == "begin") {
		Token* t = new Token(BEGINSYM, "begin");
		return t;
	}
	else if (lexeme == "boolean") {
		Token* t = new Token(BOOLSYM, "boolean");
		return t;
	}
	else if (lexeme == "else") {
		Token* t = new Token(ELSESYM, "else");
		return t;
	}
	else if (lexeme == "end") {
		Token* t = new Token(ENDSYM, "end");
		return t;
	}
	else if (lexeme == "false") {
		Token* t = new Token(FALSESYM, "false");
		return t;
	}
	else if (lexeme == "if") {
		Token* t = new Token(IFSYM, "if");
		return t;
	}
	else if (lexeme == "integer") {
		Token* t = new Token(INTSYM, "integer");
		return t;
	}
	else if (lexeme == "not" || lexeme == "!") {
		Token* t = new Token(NOTSYM, "not");
		return t;
	}
	else if (lexeme == "then") {
		Token* t = new Token(THENSYM, "begin");
		return t;
	}
	else if (lexeme == "true") {
		Token* t = new Token(TRUESYM, "begin");
		return t;
	}
	else if (lexeme == "while") {
		Token* t = new Token(
			WHILESYM, "begin");
		return t;
	}
	else if (lexeme == ".") {
		Token* t = new Token(PERIOD, ".");
		return t;
	}
	else if (lexeme == ":") {
		Token* t = new Token(COLON, ":");
		return t;
	}
	else if (lexeme == "!=") {
		Token* t = new Token(NEQ, "!=");
		return t;
	}
	else if (lexeme == "and") {
		Token* t = new Token(

			ANDSYM, "and");
		return t;
	}
	else if (lexeme == "%") {
		Token* t = new Token(DIVSYM, "%");
		return t;
	}
	else if (lexeme == "do") {
		Token* t = new Token(

			DOSYM, "do");
		return t;
	}
	else if (lexeme == "downto") {
		Token* t = new Token(

			DOWNTOSYM, "downto");
		return t;
	}
	else if (lexeme == "for") {
		Token* t = new Token(FORSYM, "for");
		return t;
	}
	else if (lexeme == "mod") {
		Token* t = new Token(

			MODSYM, "mod");
		return t;
	}
	else if (lexeme == "or") {
		Token* t = new Token(

			ORSYM, "or");
		return t;
	}
	else if (lexeme == "program") {
		Token* t = new Token(

			PROGSYM, "program");
		return t;
	}
	else if (lexeme == "read") {
		Token* t = new Token(

			READSYM, "read");
		return t;
	}
	else if (lexeme == "readln") {
		Token* t = new Token(

			READLNSYM, "readln");
		return t;
	}
	else if (lexeme == "real") {
		Token* t = new Token(

			REALSYM, "real");
		return t;
	}
	else if (lexeme == "repeat") {
		Token* t = new Token(

			REPEATSYM, "repeat");
		return t;
	}
	else if (lexeme == "to") {
		Token* t = new Token(

			TOSYM, "to");
		return t;
	}
	else if (lexeme == "until") {
		Token* t = new Token(

			UNTILSYM, "until");
		return t;
	}
	else if (lexeme == "var") {
		Token* t = new Token(

			VARSYM, "var");
		return t;
	}
	else if (lexeme == "write") {
		Token* t = new Token(

			WRITESYM, "write");
		return t;
	}
	else if (lexeme == "writeln") {
		Token* t = new Token(WRITELNSYM, "writeln");
		return t;
	}
	else if (lexeme == "end") {
		Token* t = new Token(ENDSYM, "end");
		return t;
	}
	else {
		if (isDouble(lexeme)) {
			Token* t = new Token(NUMLIT, lexeme);
			return t;

		}
		Token* t = new Token(IDENT, lexeme);
		return t;
	}


}

string LexicalAnalyzer::getNextString() {
	if (nextTokenPosition == getLine(currentLine).length()) { //if end of line then return L and currentLine++
		nextTokenPosition = 0;
		currentTokenPosition = 0;
		return "NEW_LINE";
	}
	string line = getLine(currentLine);
	string str = "";

	if (line.substr(nextTokenPosition, 1) == " ") {
		str = " ";
	}
	else if (line.substr(nextTokenPosition, 1) == "+") {
		str = "+";
	}
	else if (line.substr(nextTokenPosition, 1) == "-") {
		str = "-";
	}
	else if (line.substr(nextTokenPosition, 1) == "*") {
		str = "*";
	}
	else if (line.substr(nextTokenPosition, 1) == "=") {
		str = "=";
	}
	else if (line.substr(nextTokenPosition, 1) == ".") {
		str = ".";
	}
	else if (line.substr(nextTokenPosition, 1) == "%") {
		str = "%";
	}
	else if (line.substr(nextTokenPosition, 1) == "(") {
		str = "(";
	}
	else if (line.substr(nextTokenPosition, 1) == ")") {
		str = ")";
	}
	else if (line.substr(nextTokenPosition, 1) == ",") {
		str = ",";
	}
	else if (line.substr(nextTokenPosition, 1) == ";") {
		str = ";";
	}
	else if (line.substr(nextTokenPosition, 1) == "/") {
		if (line.substr(nextTokenPosition, 2) == "/=") {
			str = "/=";
		}
		else {
			str = "/";
		}
	}
	else if (line.substr(nextTokenPosition, 1) == ":") {
		if (line.substr(nextTokenPosition, 2) == ":=") {
			str = ":=";
		}
		else {
			str = ":";
		}
	}
	else if (line.substr(nextTokenPosition, 1) == "<") {
		if (line.substr(nextTokenPosition, 2) == "<=") {
			str = "<=";
		}
		else {
			str = "<";
		}
	}
	else if (line.substr(nextTokenPosition, 1) == ">") {
		if (line.substr(nextTokenPosition, 2) == ">=") {
			str = ">=";
		}
		else {
			str = ">";

		}

	}
	else if (line.substr(nextTokenPosition, 1) == "&") {
		if (line.substr(nextTokenPosition, 2) == "&&") {
			str = "&&";
		}
		else {
			str = "&";

		}

	}
	else if (line.substr(nextTokenPosition, 1) == "!") {
		if (line.substr(nextTokenPosition, 2) == "!=") {
			str = "!=";
		}
		else {
			str = "!";

		}

	}
	else {
		for (int i = nextTokenPosition; i <= line.length(); i++) {

			if (isToken(line.substr(i, 1))) {
				break;
			}
			else {
				str = str + line.substr(i, 1);
			}
		}

	}
	currentTokenPosition = nextTokenPosition;
	nextTokenPosition = nextTokenPosition + str.length();

	//cout << nextTokenPosition <<" = " << nextTokenPosition <<"+"<< str.length();
	if (nextTokenPosition > line.length()) {
		currentLine++;
		nextTokenPosition = 0;
		currentTokenPosition = 0;
	}

	//cout << endl << "            line : " << currentLine << ", str: " << str << ", str length : " << str.length() << ", inline counter : " << nextTokenPosition << "  line length : " << line.length() << endl <<endl;
	return str;
}

int LexicalAnalyzer::getcurrentTokenPosition() {
	return currentTokenPosition;
}
void LexicalAnalyzer::setcurrentTokenPosition(int i) {
	this->currentTokenPosition = i;
}
int LexicalAnalyzer::getnextTokenPosition()
{
	return nextTokenPosition;
}
Token* LexicalAnalyzer::getCurrentToken() {
	return currentToken;
}