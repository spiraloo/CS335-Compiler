%{
    #include <iostream>
    #include <bits/stdc++.h>
    #include "parser.tab.h"
    #include <stack>
    using namespace std;

    #define YY_DECL extern "C" int yylex()
    extern void yyerror(const char *s);
    stack<int> indent_stack;
    int indent = 0;
    void yylval_set_str(const char* ID){
        char* str = new char[sizeof(ID)+3+yyleng];
        sprintf(str, "%s (%s)", ID,(char*)yytext);
        yylval.str = str;
        // cout << yylval.str << endl;
        return;
    }

%}
%option noyywrap
%option yylineno
DIGIT [0-9]
BINDIGIT [01]
OCTDIGIT [0-7]
HEXDIGIT [0-9a-fA-F]
NONZERODIGIT [1-9]
HEXINTEGER 0[xX](("_")?{HEXDIGIT})+
OCTINTEGER 0[oO](("_")?{OCTDIGIT})+
BININTEGER 0[bB](("_")?{BINDIGIT})+
DECINTEGER {NONZERODIGIT}(("_")?{DIGIT})*|"0"(("_")?"0")*
INTEGER {DECINTEGER}|{BININTEGER}|{OCTINTEGER}|{HEXINTEGER}

DIGIT_PART {DIGIT}(("_")?{DIGIT})*
FRACTION "."{DIGIT_PART}
EXPONENT [eE]([+-]?){DIGIT_PART}
POINT_FLOAT {DIGIT_PART}?{FRACTION}|{DIGIT_PART}"."
EXPONENT_FLOAT ({DIGIT_PART}|{POINT_FLOAT}){EXPONENT}
FLOAT_NUMBER {POINT_FLOAT}|{EXPONENT_FLOAT}

IMAG_NUMBER ({FLOAT_NUMBER}|{DIGIT_PART})[Jj]

LONG_STRING_CHAR [^\\]
SHORT_STRING_CHAR [^\\'\n\"]
ESCAPE_SEQUENCE \\(.|\n)
LONG_STRING_ITEM {LONG_STRING_CHAR}|{ESCAPE_SEQUENCE}
SHORT_STRING_ITEM {SHORT_STRING_CHAR}|{ESCAPE_SEQUENCE}
SHORT_STRING "'"{SHORT_STRING_ITEM}*"'"|\"{SHORT_STRING_ITEM}*\"
LONG_STRING "'''"{LONG_STRING_ITEM}*"'''"|\"\"\"{LONG_STRING_ITEM}*\"\"\"
STRING_LITERAL {SHORT_STRING}|{LONG_STRING}

IDENTIFIER [_a-zA-Z][_a-zA-Z0-9]*

COMMENTS "#"[^\n]*

%%

  if(indent_stack.empty()){
        indent_stack.push(0);
  }
  static deque<int> tokenq;
  if (!tokenq.empty()) {
    int token = tokenq.front();
    tokenq.pop_front();
    if (token == INDENT) {
    //   yylval.str = strdup("INDENT");
    // sprintf(yylval.str, "INDENT");
    char* str = new char[7];
    sprintf(str, "INDENT");
    yylval.str = str;
      return token;
    }
    if (token == DEDENT) {
    //   yylval.str = strdup("DEDENT");
    // sprintf(yylval.str, "DEDENT");
    char* str = new char[7];
    sprintf(str, "DEDENT");
    yylval.str = str;
      return token;
    }
  }

"False" {yylval_set_str("KEYWORD"); return KEYWORD_FALSE;}
"None" {yylval_set_str("KEYWORD"); return KEYWORD_NONE;}
"True" {yylval_set_str("KEYWORD"); return KEYWORD_TRUE;}
"and" {yylval_set_str("KEYWORD"); return KEYWORD_AND;}
"assert" {yylval_set_str("KEYWORD"); return KEYWORD_ASSERT;}
"break" {yylval_set_str("KEYWORD"); return KEYWORD_BREAK;}
"class" {yylval_set_str("KEYWORD"); return KEYWORD_CLASS;}
"continue" {yylval_set_str("KEYWORD"); return KEYWORD_CONTINUE;}
"def" {yylval_set_str("KEYWORD"); return KEYWORD_DEF;}
"elif" {yylval_set_str("KEYWORD"); return KEYWORD_ELIF;}
"else" {yylval_set_str("KEYWORD"); return KEYWORD_ELSE;}
"for" {yylval_set_str("KEYWORD"); return KEYWORD_FOR;}
"from" {yylval_set_str("KEYWORD"); return KEYWORD_FROM;}
"global" {yylval_set_str("KEYWORD"); return KEYWORD_GLOBAL;}
"if" {yylval_set_str("KEYWORD"); return KEYWORD_IF;}
"in" {yylval_set_str("KEYWORD"); return KEYWORD_IN;}
"nonlocal" {yylval_set_str("KEYWORD"); return KEYWORD_NONLOCAL;}
"not" {yylval_set_str("KEYWORD"); return KEYWORD_NOT;}
"or" {yylval_set_str("KEYWORD"); return KEYWORD_OR;}
"raise" {yylval_set_str("KEYWORD"); return KEYWORD_RAISE;}
"return" {yylval_set_str("KEYWORD"); return KEYWORD_RETURN;}
"while" {yylval_set_str("KEYWORD"); return KEYWORD_WHILE;}

"**" {yylval_set_str("OPERATOR"); return OP_POWER;}
"//=" {yylval_set_str("OPERATOR"); return OP_INT_DIVIDE_EQUALS;}
"**=" {yylval_set_str("OPERATOR"); return OP_POWER_EQUALS;}
">>=" {yylval_set_str("OPERATOR"); return OP_RIGHT_SHIFT_EQUALS;}
"<<=" {yylval_set_str("OPERATOR"); return OP_LEFT_SHIFT_EQUALS;}
"^=" {yylval_set_str("OPERATOR"); return OP_XOR_EQUALS;}
"|=" {yylval_set_str("OPERATOR"); return OP_OR_EQUALS;}
"&=" {yylval_set_str("OPERATOR"); return OP_AND_EQUALS;}
"%=" {yylval_set_str("OPERATOR"); return OP_MOD_EQUALS;}
"/=" {yylval_set_str("OPERATOR"); return OP_DIVIDE_EQUALS;}
"*=" {yylval_set_str("OPERATOR"); return OP_MULTIPLY_EQUALS;}
"-=" {yylval_set_str("OPERATOR"); return OP_MINUS_EQUALS;}
"+=" {yylval_set_str("OPERATOR"); return OP_PLUS_EQUALS;}
"!=" {yylval_set_str("OPERATOR"); return OP_NOT_EQUALS;}
"==" {yylval_set_str("OPERATOR"); return OP_EQUALS;}
">>" {yylval_set_str("OPERATOR"); return OP_RIGHT_SHIFT;}
"<<" {yylval_set_str("OPERATOR"); return OP_LEFT_SHIFT;}
"//" {yylval_set_str("OPERATOR"); return OP_INT_DIVIDE;}
">=" {yylval_set_str("OPERATOR"); return OP_GREATER_THAN_EQUALS;}
"<=" {yylval_set_str("OPERATOR"); return OP_LESS_THAN_EQUALS;}
"->" {yylval_set_str("OPERATOR"); return OP_ARROW;}

":" {yylval_set_str("DELIMITER"); return ':';}
"(" {yylval_set_str("DELIMITER"); return '(';}
")" {yylval_set_str("DELIMITER"); return ')';}
"*" {yylval_set_str("OPERATOR"); return '*';}
"=" {yylval_set_str("OPERATOR"); return '=';}
"," {yylval_set_str("DELIMITER"); return ',';}
";" {yylval_set_str("DELIMITER"); return ';';}
">" {yylval_set_str("OPERATOR"); return '>';}
"<" {yylval_set_str("OPERATOR"); return '<';}
"|" {yylval_set_str("OPERATOR"); return '|';}
"^" {yylval_set_str("OPERATOR"); return '^';}
"&" {yylval_set_str("OPERATOR"); return '&';}
"+" {yylval_set_str("OPERATOR"); return '+';}
"-" {yylval_set_str("OPERATOR"); return '-';}
"/" {yylval_set_str("OPERATOR"); return '/';}
"%" {yylval_set_str("OPERATOR"); return '%';}
"~" {yylval_set_str("OPERATOR"); return '~';}
"]" {yylval_set_str("DELIMITER"); return ']';}
"[" {yylval_set_str("DELIMITER"); return '[';}
"." {yylval_set_str("DELIMITER"); return '.';}

{INTEGER} {yylval_set_str("INT");return NUMBER;}
{FLOAT_NUMBER} {yylval_set_str("FLOAT");return NUMBER;}
{IMAG_NUMBER} {yylval_set_str("IMAG");return NUMBER;}
{IDENTIFIER} {yylval_set_str("NAME");return NAME;}
{STRING_LITERAL} {yylval_set_str("STRING");return STRING;}

{COMMENTS} {}


[\n][ \t]* {
    string s = yytext;
    int i = 1;
    int indent_length = 0;
    while(i<s.length()){
        if(s[i] == ' '){
            indent_length++;
        }
        else if(s[i] == '\t'){
            cout << "IndentationError: unexpected tab" << endl;
            yyerror(yytext);
        }
        else{
            break;
        }
        i++;
    }

    if(indent_length%2 != 0){
        cout << "IndentationError: indent is not a multiple of 2" << endl;
        yyerror(yytext);
    }

    indent_length = indent_length/2;
    if(indent_length > indent_stack.top()){
        indent_stack.push(indent_length);
        tokenq.push_back(INDENT);
    }
    else if(indent_length < indent_stack.top()){
        while(indent_length < indent_stack.top()){
            indent_stack.pop();
            tokenq.push_back(DEDENT);
        }

        if(indent_length != indent_stack.top()){
            cout << "IndentationError: unindent does not match any outer indentation level" << endl;
            yyerror(yytext);
        }

    }
    
    // yylval.str = strdup("NEWLINE");
    // sprintf(yylval.str, "NEWLINE");
    char *str = new char[8];
    sprintf(str, "NEWLINE");
    yylval.str = str;
    return NEWLINE;
    
}
[\n]([ \t]|{COMMENTS})*[\n] {
    string s = yytext;
    yyless(s.length()-1);
}

[\t ]* {/*ignore whitespace in between lines*/}
<<EOF>> {
    while(indent_stack.top() != 0){
        tokenq.push_back(DEDENT);
        indent_stack.pop();
    }
    // yylval.str = strdup("ENDMARKER");
    // sprintf(yylval.str, "ENDMARKER");
    char* str = new char[9];
    sprintf(str, "ENDMARKER");
    yylval.str = str;
    return ENDMARKER;
    }
. {cout << "Invalid character" << endl; 
    yyerror(yytext);}

%%
