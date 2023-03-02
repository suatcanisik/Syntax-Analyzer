#include <fstream>
#include <iostream>

#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"

using namespace std;

int main(int argc, char *argv[])
{
  ifstream sourceCodeFile;
  LexicalAnalyzer *la;
  SyntaxAnalyzer *parser;
  cout << "hello" << endl;
  sourceCodeFile.open(argv[1], ifstream::in);
  if  (sourceCodeFile.is_open())
  { 
      cout << "----------------------------------file is open" << endl;
    la = new LexicalAnalyzer(&sourceCodeFile);
    parser = new SyntaxAnalyzer(la);
    parser->Program();
  }
  else
    printf("ERROR - cannot open input file \n");

  return 0;
}
