%{
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
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
        s.f_id = strdup(str);
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

break        { printf("keyword: %s\n", yytext); }
case         { printf("keyword: %s\n", yytext); }
catch        { printf("keyword: %s\n", yytext); }
class        { printf("keyword: %s\n", yytext); }
const        { printf("keyword: %s\n", yytext); }
continue     { printf("keyword: %s\n", yytext); }
default      { printf("keyword: %s\n", yytext); }
do           { printf("keyword: %s\n", yytext); }
else         { printf("keyword: %s\n", yytext); }
enum         { printf("keyword: %s\n", yytext); }
extends      { printf("keyword: %s\n", yytext); }
final        { printf("keyword: %s\n", yytext); }
finally      { printf("keyword: %s\n", yytext); }
for          { printf("keyword: %s\n", yytext); }
if           { printf("keyword: %s\n", yytext); }
in           { printf("keyword: %s\n", yytext); }
is           { printf("keyword: %s\n", yytext); }
is!          { printf("keyword: %s\n", yytext); }
new          { printf("keyword: %s\n", yytext); }
rethrow      { printf("keyword: %s\n", yytext); }
return       { printf("keyword: %s\n", yytext); }
super        { printf("keyword: %s\n", yytext); }
switch       { printf("keyword: %s\n", yytext); }
this         { printf("keyword: %s\n", yytext); }
throw        { printf("keyword: %s\n", yytext); }
try          { printf("keyword: %s\n", yytext); }
var          { printf("keyword: %s\n", yytext); }
void         { printf("keyword: %s\n", yytext); }
while        { printf("keyword: %s\n", yytext); }
true         { printf("boolean_literal: %d\n", true); }
false        { printf("boolean_literal: %d\n", false); }
null         { printf("null_literal: %s\n", yytext); }

abstract     { printf("keyword: %s\n", yytext); }
as           { printf("keyword: %s\n", yytext); }
export       { printf("keyword: %s\n", yytext); }
factory      { printf("keyword: %s\n", yytext); }
get          { printf("keyword: %s\n", yytext); }
import       { printf("keyword: %s\n", yytext); }
required     { printf("keyword: %s\n", yytext); }
set          { printf("keyword: %s\n", yytext); }
static       { printf("keyword: %s\n", yytext); }

when         { printf("keyword_contextual: %s\n", yytext); }


<INITIAL>"{"     { printf("curly_bracket_open: %s\n", yytext); }
<INITIAL>"}"     { printf("curly_bracket_close: %s\n", yytext); }
"("     { printf("round_bracket_open: %s\n", yytext); }
")"     { printf("round_bracket_close: %s\n", yytext); }
"["     { printf("square_bracket_open: %s\n", yytext); }
"]"     { printf("square_bracket_close: %s\n", yytext); }

"++"    { printf("increment: %s\n", yytext); }
"--"    { printf("decrement: %s\n", yytext); }

"*="    { printf("multiplication_assignment: %s\n", yytext); }
"/="    { printf("division_assignment: %s\n", yytext); }
"+="    { printf("addition_assignment: %s\n", yytext); }
"-="    { printf("subtraction_assignment: %s\n", yytext); }
"%="    { printf("remainder_assignment: %s\n", yytext); }
"~/="   { printf("integer_division_assignment: %s\n", yytext); }

"~/"    { printf("integer_division: %s\n", yytext); }
"*"     { printf("multiplication: %s\n", yytext); }
"/"     { printf("division: %s\n", yytext); }
"+"     { printf("addition: %s\n", yytext); }
"-"     { printf("subtraction: %s\n", yytext); }
"%"     { printf("remainder: %s\n", yytext); }

">="    { printf("greater_equal: %s\n", yytext); }
"<="    { printf("less_equal: %s\n", yytext); }
"=="    { printf("equal: %s\n", yytext); }
"!="    { printf("not_equal: %s\n", yytext); }
">"     { printf("greater: %s\n", yytext); }
"<"     { printf("less: %s\n", yytext); }

"&&"    { printf("logical_and: %s\n", yytext); }
"||"    { printf("logical_or: %s\n", yytext); }
"!"     { printf("logical_not: %s\n", yytext); }

"="     { printf("assignment: %s\n", yytext); }

"."     { printf("dot: %s\n", yytext); }
","     { printf("comma: %s\n", yytext); }
":"     { printf("colon: %s\n", yytext); }
";"     { printf("semicolon: %s\n", yytext); }
"?"     {}


{DOUBLE}    { 
  deleteUnderscores(yytext, tmp);
  double doubleValue = strtod(tmp, NULL);
  printf("double_literal: %f\n", doubleValue); 
  }

{INT_HEX}   { 
  deleteUnderscores(yytext, tmp);
  long decimalValue = strtol(tmp + 2, NULL, 16);
  printf("integer_literal: %ld\n", decimalValue); 
  }

{INT_DEC}   { 
  deleteUnderscores(yytext, tmp);
  printf("integer_literal: %d\n", atoi(tmp)); 
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
  printf("identifier: %s\n", yytext); 
  }


"/*"  {yy_push_state(MULTILINE_COMMENT_STATE); printf("Start of a multi-line comment (yytext = %s)\n", yytext);}
<MULTILINE_COMMENT_STATE>"/"+"*" {yy_push_state(MULTILINE_COMMENT_STATE); printf("Start of a multi-line comment (yytext = %s)\n", yytext);}
<MULTILINE_COMMENT_STATE>"*"+"/" {yy_pop_state(); printf("End of multi-line comment (yytext = %s)\n", yytext);}
<MULTILINE_COMMENT_STATE>[^*/]+ {}
<MULTILINE_COMMENT_STATE>"*"+[^*/]* {}
<MULTILINE_COMMENT_STATE>"/"+[^*/]* {}
<MULTILINE_COMMENT_STATE><<EOF>> {printf("Error: multi-line comment not closed (line #%d)\n", yylineno);}

"//"[^\n]* {printf("A standard comment (yytext = %s)\n", yytext);}


"r'" {yy_push_state(RAW_STRING_SINGLE_STATE); stringBuffer[0] = '\0';}
"r\"" {yy_push_state(RAW_STRING_DOUBLE_STATE); stringBuffer[0] = '\0';}

<RAW_STRING_SINGLE_STATE>"'" {
    yy_pop_state();
    char* copy = strdup(stringBuffer);
    stringBuffer[0] = '\0';
    return copy;
}
<RAW_STRING_DOUBLE_STATE>"\"" { 
    yy_pop_state();
    char* copy = strdup(stringBuffer);
    stringBuffer[0] = '\0';
    return copy;
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
<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\\". {strcat(stringBuffer, yytext[1]); }

<STRING_SINGLE_STATE>"'" {yy_pop_state(); char* copy = strdup(stringBuffer); stringBuffer[0] = '\0'; return copy;}
<STRING_DOUBLE_STATE>"\"" {yy_pop_state(); char* copy = strdup(stringBuffer); stringBuffer[0] = '\0'; return copy;}

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
    return copy;
}

<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\${" {
    pushTokenNoValue('(');
    pushTokenNoValue('+');
    char* copy = strdup(stringBuffer);
    stringBuffer[0] = '\0';

    yy_push_state(INTERPOLATION_STATE);
    return copy; 
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
    pushTokenNoValue(')');
    char* copy = strdup(stringBuffer);

    stringBuffer[0] = '\0';
    yy_pop_state();
    return copy;
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

void main( int argc, char** argv )
{
    ++argv, --argc;
    if ( argc > 0 )
        yyin = fopen( argv[0], "r" );
    else
        yyin = stdin;

    yylex();

    if (yyin != stdin)
        fclose(yyin);
}