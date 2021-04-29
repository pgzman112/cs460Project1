#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "SyntacticalAnalyzer.h"

using namespace std;

SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)
{
	lex = new LexicalAnalyzer (filename);
	token_type t;
	//**************** THIS IS IF YOU're RUNNING OG PROJECT***************
	while ((t = lex->GetToken()) != EOF_T)
	{

	}
	//*********************************************************************
	//lex->PushToVec("", t);
	// t = lex->GetToken ();
	// while (t != EOF_T)
	// {
	// 	cout << setw (16) << left << lex->GetLexeme();
	// 	cout << setw (10) << left << lex->GetTokenName(t) << endl;
	// 	t = lex->GetToken ();
	// }
	// cout << setw (12) << left << lex->GetTokenName(t) << endl;
	// cout << "========================\n";
	lex->Print();


}

SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
	delete lex;
}
