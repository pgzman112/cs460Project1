#ifndef LEX_H
#define LEX_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <locale>

using namespace std;

enum token_type{
    DIV_T = -14,
    MULT_T = -15,
    LPAREN_T = -16,
    RPAREN_T = -17,
    SQUOTE_T = -18,
    EQUALTO_T = -19,
    LBRACK_T = -20,
    RBRACK_T = -21,
    ERROR_T = -22,
    GT_T = -23,
    GTE_T = -24,
    LT_T = -25,
    LTE_T = -26,
    NUMLIT_T = -27,
    MINUS_T = -28,
    PLUS_T = -29,
    IDENT_T = -30,
    LISTOP_T = -31,
    STRLIT_T = -32,
    CONS_T = -33,
    IF_T = -34,
    COND_T = -35,
    ELSE_T = -36,
    DISPLAY_T = -37,
    NEWLINE_T = -38,
    AND_T = -39,
    OR_T = -40,
    NOT_T = -41,
    DEFINE_T = -42,
    LET_T = -43,
    NUMBERP_T = -44,
    LISTP_T = -45,
    ZEROP_T = -46,
    NULLP_T = -47,
    STRINGP_T = -48,
    MODULO_T = -49,
    ROUND_T = -50,
    EOF_T = -51,
    NONE = -52,

};

static const std::map<token_type, std::string> token_type_names = {
  { AND_T, "AND_T" },
  { COND_T, "COND_T" },
  { CONS_T, "CONS_T" },
  { DEFINE_T, "DEFINE_T" },
  { DISPLAY_T, "DISPLAY_T" },
  { DIV_T, "DIV_T" },
  { ELSE_T, "ELSE_T" },
  { EOF_T, "EOF_T" },
  { EQUALTO_T, "EQUALTO_T" },
  { ERROR_T, "ERROR_T" },
  { GTE_T, "GTE_T" },
  { GT_T, "GT_T" },
  { IDENT_T, "IDENT_T" },
  { IF_T, "IF_T" },
  { LBRACK_T, "LBRACK_T" },
  { LET_T, "LET_T" },
  { LISTOP_T, "LISTOP_T" },
  { LISTP_T, "LISTP_T" },
  { LPAREN_T, "LPAREN_T" },
  { LTE_T, "LTE_T" },
  { LT_T, "LT_T" },
  { MINUS_T, "MINUS_T" },
  { MODULO_T, "MODULO_T" },
  { MULT_T, "MULT_T" },
  { NEWLINE_T, "NEWLINE_T" },
  { NONE, "NONE" },
  { NOT_T, "NOT_T" },
  { NULLP_T, "NULLP_T" },
  { NUMBERP_T, "NUMBERP_T" },
  { NUMLIT_T, "NUMLIT_T" },
  { OR_T, "OR_T" },
  { PLUS_T, "PLUS_T" },
  { RBRACK_T, "RBRACK_T" },
  { ROUND_T, "ROUND_T" },
  { RPAREN_T, "RPAREN_T" },
  { SQUOTE_T, "SQUOTE_T" },
  { STRINGP_T, "STRINGP_T" },
  { STRLIT_T, "STRLIT_T" },
  { ZEROP_T, "ZEROP_T" },
};

static const char* matches[84] = {
  " ", // 0
  "/", // 1
  "*", // 2
  "=", // 3
  "(", // 4
  ")", // 5
  "'", //6
  "[", // 7
  "]", //8
  ">",//9
  "<", //10
  "+",//11
  "-",//12
  ".",  //13
  "0", // subtract 10 here NO //14
  "1",//15
  "2",//16
  "3",//17
  "4",//18
  "5",//19
  "6",//20
  "7",//21
  "8",//22
  "9",//23
  "c",//24 -> SHOULD B 15
  "a",//25 -> SHOULD B 16
  "d",//26 -> SHOULD B 17
  "r", // 27 -> SHOULD B 18
  "A", // 28
  "B", // 29
  "C", // 30
  "D", // 31
  "E", //32
  "F", // 33
  "G", //34
  "H",//35
  "I", //36
  "J",//37
  "K",//38
  "L",//39
  "M",//40
  "N",//41
  "O",//42
  "P",//43
  "Q",//44
  "R",//45
  "S",//46
  "T",//47
  "U",//48
  "V",//49
  "W",//50
  "X",//51
  "Y",//52
  "Z",//53
  "a",//54
  "b",//55
  "c",//56
  "d",//57
  "e",//58
  "f",//59
  "g",//60
  "h",//61
  "i",//62
  "j",//63
  "k",//64
  "l",//65
  "m",//66
  "n",//67
  "o",//68
  "p",//69
  "q",//70
  "r",//71
  "s",//72
  "t",//73
  "u",//74
  "v",//75
  "w",//76
  "x",//77
  "y",//78
  "z",//79
  "?",//80
  "_",//81
  "\"", //82
  "", // 83
};


static const char transitions[16][24] ={
  // ROW OF ZEROS TO OFF SET
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  //state 1
  {1, -14, -15, -19, -16, -17, -18, -20, -21, 2, 3, 4, 5, 6, 7, 9, 13, 13, 13, 13, -22, -22, 14, -22},
  //state 2
  {-23, -23, -23, -24, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23},
  //state 3
  {-25, -25, -25, -26, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25},
  //state 4
  {-29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, 6, 7, -29, -29, -29, -29, -29, -29, -29, -29, -29},
  //state 5
  {-28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, 6, 7, -28, -28, -28, -28, -28, -28, -28, -28, -28},
  //state 6
  {-22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, 8, -22, -22, -22, -22, -22, -22, -22, -22, -22},
  //state 7
  {-27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, 8, 7, -27, -27, -27, -27, -27, -27, -27, -27, -27},
  //state 8
  {-27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, 8, -27, -27, -27, -27, -27, -27, -27, -27, -27},
  //state 9
  {-30, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 10, 11, 13, 13, 13, 13, 13, 13},
  //state 10 CHANGING 10 18 TO POINT TO STATE 15
  {13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 10, 15, 13, 13, 13, 13, 13},
  //state 11 CHANGING 11 18 TO POINT TO STATE 15
  {13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 12, 11, 15, 13, 13, 13, 13, 13},
  //state 12 CHANGING 12 18 TO POINT TO STATE 15
  {13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 15, 13, 13, 13, 13, 13},
  //state 13
  {-30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, 13, 13, 13, 13, 13, 13, -22, 13, -30, -30},
  //state 14
  {14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, -32, 14},
  //state 15
  {-31, -22, -22, 13, -22, 13, -22, 13, 13, 13, 13, -29, -28, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, -31},
};

class LexicalAnalyzer
{
    public:
	LexicalAnalyzer (char * filename);
  char * fName;
  string oNameLst;
  string oNameP1;
  void PushToVec(string tmp, token_type t);
	~LexicalAnalyzer ();
	token_type GetToken ();
	string GetTokenName (token_type t) const;
	string GetLexeme () const;
	void ReportError (const string & msg);
  bool IsListOp(string s);
  void Print();
	ofstream debugFile;	// .dbg
  int countyCountCount;
    private:
  void GetFileName();
	ifstream input; 	// .ss
	ofstream listingFile;	// .lst
	ofstream tokenFile;	// .p1
	token_type token;
	string line;
	int linenum;
	int pos;
	string lexeme;
	int errors;
  string currLexmeme;

  vector<pair<string, token_type>> tokieToks;

};


#endif
