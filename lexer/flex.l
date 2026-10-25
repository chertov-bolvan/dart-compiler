%{
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "parser.hpp"
%}


%option yylineno
%option noyywrap
%option never-interactive
%option stack


DIGIT     [0-9]
INT_DEC   {DIGIT}+(_+{DIGIT}+)*
INT_HEX   0[xX][0-9a-fA-F]+(_+[0-9a-fA-F]+)*
ID	      [a-zA-Z_$][a-zA-Z0-9_$]*
EXPONENT  [eE][+-]?{INT_DEC}
DOUBLE    ({INT_DEC}\.{INT_DEC}{EXPONENT}?)|(\.{INT_DEC}{EXPONENT}?)|({INT_DEC}{EXPONENT})


%x MULTILINE_COMMENT_STATE
%x STRING_SINGLE_STATE
%x STRING_DOUBLE_STATE
%x RAW_STRING_SINGLE_STATE
%x RAW_STRING_DOUBLE_STATE
%s INTERPOLATION_STATE


%{
    struct Token {
        int code;
        YYSTYPE semanticValue;
    };

    #define MAX_TOKEN_STACK 1000
    struct Token tokenStack[MAX_TOKEN_STACK];
    int tokenTop = -1;

    void pushToken(int code, YYSTYPE sV) {
        if (tokenTop >= MAX_TOKEN_STACK - 1)
            return;
        
        tokenTop++;
        tokenStack[tokenTop].code = code;
        tokenStack[tokenTop].semanticValue = sV;  
    }

    void pushTokenNoValue(int code) {
        if (tokenTop >= MAX_TOKEN_STACK - 1)
            return;
        
        tokenTop++;
        tokenStack[tokenTop].code = code;
    }

    struct Token popToken() {
        return tokenStack[tokenTop--];
    }

    YYSTYPE svID(char* str) {
        YYSTYPE s;
        s.Identifier = strdup(str);
        return s;
    }
%}

%{
    void deleteUnderscores(char* src, char* result);
%}

%%

%{
    char tmp[1000] = "";
%}

%{
    char stringBuffer[4000];
%}

%{
    if (tokenTop > -1) {
        struct Token t = popToken();
        yylval = t.semanticValue;
        return t.code;
    }
%}

break        { return BREAK_KW; }
catch        { return CATCH_KW; }
class        { return CLASS_KW; }
const        { return CONST_KW; }
continue     { return CONTINUE_KW; }
default      { return DEFAULT_KW; }
do           { return DO_KW; }
else         { return ELSE_KW; }
enum         { return ENUM_KW; }
extends      { return EXTENDS_KW; }
final        { return FINAL_KW; }
finally      { return FINALLY_KW; }
for          { return FOR_KW; }
if           { return IF_KW; }
in           { return IN_KW; }
is           { return IS_KW; }
new          { return NEW_KW; }
rethrow      { return RETHROW_KW; }
return       { return RETURN_KW; }
super        { return SUPER_KW; }
this         { return THIS_KW; }
throw        { return THROW_KW; }
try          { return TRY_KW; }
var          { return VAR_KW; }
void         { return VOID_TYPE; }
while        { return WHILE_KW; }
true         { yylval.Bool = 1; return BOOL_LIT; }
false        { yylval.Bool = 0; return BOOL_LIT; }
null         { return NULL_KW; }

abstract     { return ABSTRACT_KW; }
as           { return AS_KW; }
export       { return EXPORT_KW; }
factory      { return FACTORY_KW; }
get          { return GET_KW; }
import       { return IMPORT_KW; }
required     { return REQUIRED_KW; }
set          { return SET_KW; }
static       { return STATIC_KW; }

when         { return WHEN_KW; }

List         { return LIST_KW; }


<INITIAL>"{"     { return '{'; }
<INITIAL>"}"     { return '}'; }
"("     { return '('; }
")"     { return ')'; }
"["     { return '['; }
"]"     { return ']'; }

"++"    { return INC; }
"--"    { return DEC; }

"*="    { return MUL_ASSIGN; }
"/="    { return DIV_ASSIGN; }
"+="    { return ADD_ASSIGN; }
"-="    { return SUB_ASSIGN; }
"%="    { return MOD_ASSIGN; }
"~/="   { return INTDIV_ASSIGN; }

"~/"    { return INTDIV; }
"*"     { return '*'; }
"/"     { return '/'; }
"+"     { return '+'; }
"-"     { return '-'; }
"%"     { return '%'; }

">="    { return GEQ; }
"<="    { return LEQ; }
"=="    { return EQ; }
"!="    { return NEQ; }
">"     { return '>'; }
"<"     { return '<'; }

"&&"    { return LOG_AND; }
"||"    { return LOG_OR; }
"!"     { return '!'; }

"="     { return '='; }

"."     { return '.'; }
","     { return ','; }
":"     { return ':'; }
";"     { return ';'; }
"?"     { return '?'; }


{DOUBLE}    { 
  deleteUnderscores(yytext, tmp);

  yylval.Double = strtod(tmp, NULL);
  return DOUBLE_LIT;
  }

{INT_HEX}   { 
  deleteUnderscores(yytext, tmp);
  long decimalValue = strtol(tmp + 2, NULL, 16);
   yylval.Int = (int)decimalValue;
   return INT_LIT;
  }

{INT_DEC}   { 
  deleteUnderscores(yytext, tmp);

  yylval.Int = atoi(tmp);
  return INT_LIT;
  }


{INT_DEC}_+ {
    printf("ERROR: invalid integer literal: %s\n", yytext);
}

0[xX]_+[0-9a-fA-F]+(_+[0-9a-fA-F]+)* {
    printf("ERROR: invalid hexadecimal integer literal: %s\n", yytext);
}

0[xX][0-9a-fA-F]+(_+[0-9a-fA-F]+)*_+ {
    printf("ERROR: invalid hexadecimal integer literal: %s\n", yytext);
}

0[xX]_+ {
    printf("ERROR: invalid hexadecimal integer literal: %s\n", yytext);
}

0[xX] {
    printf("ERROR: invalid hexadecimal integer literal: %s\n", yytext);
}

0[xX][0-9a-zA-Z_]+ {
    printf("ERROR: invalid hexadecimal integer literal: %s\n", yytext);
}

({INT_DEC}|{INT_DEC}\.{INT_DEC}|\.{INT_DEC})[eE][+-]?_+{INT_DEC} {
    printf("ERROR: invalid double literal: %s\n", yytext);
}

({INT_DEC}|{INT_DEC}\.{INT_DEC}|\.{INT_DEC})[eE][+-]?_+ {
    printf("ERROR: invalid double literal: %s\n", yytext);
}

({INT_DEC}|{INT_DEC}\.{INT_DEC}|\.{INT_DEC})[eE][+-]? {
    printf("ERROR: invalid double literal: %s\n", yytext);
}

{DOUBLE}_+ {
    printf("ERROR: invalid double literal: %s\n", yytext);
}

\.{EXPONENT} {
    printf("ERROR: invalid double literal: %s\n", yytext);
}


{ID}        { 
  char* copy = strdup(yytext);

  yylval.Identifier = copy;
  return ID;
  }


"/*"  {yy_push_state(MULTILINE_COMMENT_STATE);}
<MULTILINE_COMMENT_STATE>"/"+"*" {yy_push_state(MULTILINE_COMMENT_STATE);}
<MULTILINE_COMMENT_STATE>"*"+"/" {yy_pop_state();}
<MULTILINE_COMMENT_STATE>[^*/]+ {}
<MULTILINE_COMMENT_STATE>"*"+[^*/]* {}
<MULTILINE_COMMENT_STATE>"/"+[^*/]* {}
<MULTILINE_COMMENT_STATE><<EOF>> {printf("Error: multi-line comment not closed (line #%d)\n", yylineno);}

"//"[^\n]* {}


"r'" {yy_push_state(RAW_STRING_SINGLE_STATE); stringBuffer[0] = '\0';}
"r\"" {yy_push_state(RAW_STRING_DOUBLE_STATE); stringBuffer[0] = '\0';}

<RAW_STRING_SINGLE_STATE>"'" {
    yy_pop_state();
    char* copy = strdup(stringBuffer);
    stringBuffer[0] = '\0';
    yylval.String = copy;
    return STRING_LIT;
}
<RAW_STRING_DOUBLE_STATE>"\"" { 
    yy_pop_state();
    char* copy = strdup(stringBuffer);
    stringBuffer[0] = '\0';
    yylval.String = copy;
    return STRING_LIT;
}

<RAW_STRING_SINGLE_STATE>[^']+ {strcat(stringBuffer, yytext);}
<RAW_STRING_DOUBLE_STATE>[^"]+ {strcat(stringBuffer, yytext);}

<RAW_STRING_SINGLE_STATE,RAW_STRING_DOUBLE_STATE><<EOF>> {printf("Error: no end of RAW string in (line #%d)\n", yylineno); }


"'" {yy_push_state(STRING_SINGLE_STATE); stringBuffer[0] = '\0';}
"\"" {yy_push_state(STRING_DOUBLE_STATE); stringBuffer[0] = '\0';}

<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\\n" {strcat(stringBuffer, "\n"); }
<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\\t" {strcat(stringBuffer, "\t"); }
<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\\r" {strcat(stringBuffer, "\r"); }
<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\\b" {strcat(stringBuffer, "\b"); }
<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\\\\" {strcat(stringBuffer, "\\"); }
<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\\'" {strcat(stringBuffer, "\'"); }
<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\\\"" {strcat(stringBuffer, "\""); }
<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\\\$" {strcat(stringBuffer, "\$"); }
<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\\". {strncat(stringBuffer, &yytext[1], 1); }

<STRING_SINGLE_STATE>"'" {
    yy_pop_state();
    char* copy = strdup(stringBuffer);
    stringBuffer[0] = '\0';
    yylval.String = copy;
    return STRING_LIT;
}
<STRING_DOUBLE_STATE>"\"" {
    yy_pop_state();
    char* copy = strdup(stringBuffer);
    stringBuffer[0] = '\0';
    yylval.String = copy;
    return STRING_LIT;
}

<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\$"[a-zA-Z_][a-zA-Z0-9_]* {
    pushTokenNoValue('+');
    pushTokenNoValue(')');
    pushTokenNoValue('(');
    pushToken(ID, svID("toString"));
    pushTokenNoValue('.');
    pushToken(ID, svID(yytext + 1));
    pushTokenNoValue('+');
    char* copy = strdup(stringBuffer);

    stringBuffer[0] = '\0';
    yylval.String = copy;
    return STRING_LIT;
}

<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\${" {
    pushTokenNoValue('(');
    pushTokenNoValue('+');
    char* copy = strdup(stringBuffer);
    stringBuffer[0] = '\0';

    yy_push_state(INTERPOLATION_STATE);
    yylval.String = copy;
    return STRING_LIT;
}

<STRING_SINGLE_STATE>[^'\\$]+ {strcat(stringBuffer, yytext);}
<STRING_DOUBLE_STATE>[^"\\$]+ {strcat(stringBuffer, yytext);}

<STRING_SINGLE_STATE,STRING_DOUBLE_STATE><<EOF>> { printf("Error: no end of STRING in (line #%d)\n", yylineno); }

<INTERPOLATION_STATE>"}" {
    pushTokenNoValue('+');
    pushTokenNoValue(')');
    pushTokenNoValue('(');
    pushToken(ID, svID("toString"));
    pushTokenNoValue('.');

    yy_pop_state();
    return ')';
}

<INTERPOLATION_STATE><<EOF>> {printf("Error: no end of INTERPOLATION in (line #%d)\n", yylineno);}

%%

void deleteUnderscores(char* src, char* result) {
  result[0] = 0;
  int j = 0;

  for (int i = 0; src[i] != '\0'; i++) {
    if (src[i] != '_') {
      result[j] = src[i];
      j++;
    }
  }

  result[j] = '\0';
}