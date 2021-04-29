// Preston Zimmerman
#include <iomanip>
#include <cstdlib>
#include "LexicalAnalyzer.h"
#include <fstream>

using namespace std;

static string token_names[] = {	"EOF_T" };

LexicalAnalyzer::LexicalAnalyzer (char * filename)
{
	// This function will initialize the lexical analyzer class

	input.open (filename);
	if(input.fail()){
		cout << "Input failed to open please retype input file" << endl;
		exit(1);
	}
	fName = filename;
	GetFileName();
	listingFile.open(oNameLst);
	tokenFile.open(oNameP1);
	countyCountCount = 0;
	listingFile << "Input file: " << filename << endl;
}

LexicalAnalyzer::~LexicalAnalyzer ()
{
	// This function will complete the execution of the lexical analyzer class
	input.close();
	listingFile.close();
	tokenFile.close();
	cout << errors << " errors found in input file" << endl;
}

token_type LexicalAnalyzer::GetToken ()
{
	// This function will find the next lexeme int the input file and return
	// the token_type value associated with that lexeme
	static string text = " ";
	static int pos = 0;
	static int lineNumber = 1;
	static int numErrors = 0;
	while(isspace (text[pos])){
		pos++;
		if(pos >= text.length()){
			getline (input, text);
			if(input.fail()){
				PushToVec("", EOF_T);
				listingFile << numErrors << " errors found in input file" << endl;
				return EOF_T;
			}
			text += " ";
			listingFile << "   " << lineNumber << ": " << text << endl;
			lineNumber++;
			text += " ";
			pos = 0;
		}
	}
	int state = 1;
	string temp = "";
	// IM dead inside
	while (state > 0){
		int col= 0;
		for(col = 0; *matches[col] && *matches[col] != text[pos]; col++);
		temp += text[pos];
		//THIS IS NECCESARRY BECAUSE OF HOW I DO MY ALAPHABET, IT ACCOUNTS FOR THE DIGIT AND CHAR OFFSET
		if(col > 14 && col < 24){
			col = col - (col - 14);
		}
		else if(col >= 24 && col < 28){
			col = col - 9;
		}
		else if(col >= 28 && col < 80){
			col = col - (col - 19);
		}
		else if(col >= 80){
			col = col - 60;
		}
		//cout << "col: " << col << endl;
	//	cout << "current state: " << state << endl;
		state = transitions[state][col];
	//	cout << "next state: " << state << endl;
		pos++;
	}

	if(state == IDENT_T || state == NUMLIT_T || state == MINUS_T || state == PLUS_T || state == GT_T || state == LT_T || state == ERROR_T){
		if(temp == "?" ||  temp == "$" || temp == "," || temp == ":" || temp == "&" || temp == "%" || temp == "#" || temp == "!" || temp == "^" || temp == "~" || temp == "|" || temp == "{" || temp == "}" || temp == "@" || temp == "_"){
			state = -22;
		}
		else if(temp == "number?" || temp == "list?" || temp == "zero?" || temp == "null?" || temp == "string?"){
			if(temp == "number?")
				state = -44;
			else if(temp == "list?")
				state = -45;
			else if(temp == "zero?")
				state = -46;
			else if(temp == "null?")
				state = -47;
			else if(temp == "string?")
				state = -48;
		}
		else{
			pos--;
			temp = temp.substr(0, temp.size()-1);
			if(IsListOp(temp))
				state = -31;
			else if(isalpha(temp[0]) && isalpha(temp[temp.length()-1]))
				state = -30;
		}
		if(temp == "modulo")
			state = -49;
		else if(temp == "round")
			state = -50;
		else if(temp == "cons")
			state = -33;
		else if(temp == "if")
			state = -34;
		else if(temp == "cond")
			state = -35;
		else if(temp == "else")
			state = -36;
		else if(temp == "display")
			state = -37;
		else if(temp == "and")
			state = -39;
		else if(temp == "or")
			state = -40;
		else if(temp == "not")
			state = -41;
		else if(temp == "define")
			state = -42;
		else if(temp == "let")
			state = -43;
		else if(temp == "newline")
			state = -38;
	} // END RED STATE IFF STATEMENT

	token_type token = (token_type) state;
	tokieToks.push_back(make_pair(temp, token));
	currLexmeme = temp;
	if(state == -22 && temp != ""){
		numErrors++;
		errors = numErrors;
		listingFile << "Error at " << lineNumber-1 << "," << pos << ": Invalid character found: " << temp << endl;
	}
  return token;
}

string LexicalAnalyzer::GetTokenName (token_type t) const
{
	// The GetTokenName function returns a string containing the name of the
	// token passed to it.
	auto iter = token_type_names.begin();
	bool flag = false;
	while(iter != token_type_names.end() && flag != true){
		if(iter->first == t){
			flag = true;
		}
		else{
			iter++;
		}
	}
	string temp = (string)iter->second;
	//cout << "temp is: " << temp <<  endl;
	return temp;
}

string LexicalAnalyzer::GetLexeme () const
{
	// This function will return the lexeme found by the most recent call to
	// the get_token function

	return currLexmeme;
}

void LexicalAnalyzer::ReportError (const string & msg)
{
	// This function will be called to write an error message to a file
}

void LexicalAnalyzer::Print () {
	for(int i = 0; i < tokieToks.size(); i++){
		auto iter = token_type_names.begin();
		bool flag = false;
		for (iter; iter != token_type_names.end() && flag != true; iter++) {
			if(iter->first == tokieToks[i].second){
					tokenFile << iter->second << "        ";
					flag = true;
			}
		 }
		 tokenFile << tokieToks[i].first << endl;
	}
}

void LexicalAnalyzer::PushToVec(string tmp, token_type t){
	tokieToks.push_back(make_pair(tmp, t));
}

void LexicalAnalyzer::GetFileName() {
	string temp = "";
	int i = 0;
	while(fName[i] != '.'){
		temp.push_back(fName[i]);
		i++;
	}
	oNameP1 = temp + ".p1";
	oNameLst = temp + ".lst";
}

bool LexicalAnalyzer::IsListOp(string s) {
	// Check if cad*r or cd*r (1 d req)
	if(s[0] == 'c'){
		if(s[1] == 'a'){
			bool isD = true;
			int counter = 2;
			while(isD && counter < s.length()){
				if(s[counter] == 'd'){
					counter++;
				}
				else{
					isD = false;
				}
			}
			if(s[counter] == 'r' && counter == s.length()-1)
				return true;
			else
				return false;
		}
		else{
			if(s[1] == 'd'){
				bool isD = true;
				int counter = 2;
				while(isD && counter < s.length()){
					if(s[counter] == 'd'){
						counter++;
					}
					else{
						isD = false;
					}
				}
				if(s[counter] == 'r' && counter == s.length()-1)
					return true;
				else
					return false;
			}
			else
				return false;
		}
	}
	else
		return false;
}
