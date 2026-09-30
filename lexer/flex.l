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
    void deleteUnderscores(char* src, char* result);
%}

%{
    char tmp[1000] = "";
%}

%{
    #define MAX_STRING_LENGTH 200
    char stringStack[MAX_STRING_LENGTH];
    int stringStackTop = -1;

    void pushStringChar(char c) {
        if (stringStackTop < MAX_STRING_LENGTH - 1)
            stringStack[++stringStackTop] = c;
    }

    char popStringChar() {
        if (stringStackTop >= 0)
            return stringStack[stringStackTop--];
        return 0;
    }

    char peekStringChar() {
        if (stringStackTop >= 0)
            return stringStack[stringStackTop];
        return 0;
    }
%}

%{
    #define MAX_STRING_BUFFER 1000
    char stringBuffers[100][MAX_STRING_BUFFER];
    int stringBufferTop = -1;

    void pushStringBuffer() {
        stringBufferTop++;
        stringBuffers[stringBufferTop][0] = '\0';
    }

    void popStringBuffer() {
        if (stringBufferTop > 0) {
            stringBufferTop--;
        }
    }

    void addTextToCurrentString(char* text) {
        if (stringBufferTop >= 0) {
            strcat(stringBuffers[stringBufferTop], text);
        }
    }

    char* peekStringBuffer() {
        if (stringBufferTop >= 0) {
            return stringBuffers[stringBufferTop];
        }
        return NULL;
    }

    void clearTopStringBuffer() {
        if (stringBufferTop >= 0) {
            stringBuffers[stringBufferTop][0] = '\0';
        }
    }

%}

%%


assert       { printf("keyword: %s\n", yytext); }
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
with         { printf("keyword: %s\n", yytext); }
while        { printf("keyword: %s\n", yytext); }
true         { printf("boolean_literal: %d\n", true); }
false        { printf("boolean_literal: %d\n", false); }
null         { printf("null_literal: %s\n", yytext); }

await        { printf("keyword_contextual: %s\n", yytext); }
yield        { printf("keyword_contextual: %s\n", yytext); }

abstract     { printf("keyword: %s\n", yytext); }
as           { printf("keyword: %s\n", yytext); }
covariant    { printf("keyword: %s\n", yytext); }
deferred     { printf("keyword: %s\n", yytext); }
dynamic      { printf("keyword: %s\n", yytext); }
export       { printf("keyword: %s\n", yytext); }
extension    { printf("keyword: %s\n", yytext); }
external     { printf("keyword: %s\n", yytext); }
factory      { printf("keyword: %s\n", yytext); }
get          { printf("keyword: %s\n", yytext); }
implements   { printf("keyword: %s\n", yytext); }
import       { printf("keyword: %s\n", yytext); }
interface    { printf("keyword: %s\n", yytext); }
late         { printf("keyword: %s\n", yytext); }
library      { printf("keyword: %s\n", yytext); }
mixin        { printf("keyword: %s\n", yytext); }
operator     { printf("keyword: %s\n", yytext); }
part         { printf("keyword: %s\n", yytext); }
required     { printf("keyword: %s\n", yytext); }
set          { printf("keyword: %s\n", yytext); }
static       { printf("keyword: %s\n", yytext); }
type         { printf("keyword: %s\n", yytext); }
typedef      { printf("keyword: %s\n", yytext); }
Function     { printf("builtin_type: %s\n", yytext); }

async        { printf("keyword_contextual: %s\n", yytext); }
base         { printf("keyword_contextual: %s\n", yytext); }
hide         { printf("keyword_contextual: %s\n", yytext); }
of           { printf("keyword_contextual: %s\n", yytext); }
on           { printf("keyword_contextual: %s\n", yytext); }
sealed       { printf("keyword_contextual: %s\n", yytext); }
show         { printf("keyword_contextual: %s\n", yytext); }
sync         { printf("keyword_contextual: %s\n", yytext); }
when         { printf("keyword_contextual: %s\n", yytext); }


num         { printf("type: %s\n", yytext); }
int         { printf("type: %s\n", yytext); }
double      { printf("type: %s\n", yytext); }

String      { printf("type: %s\n", yytext); }
bool        { printf("type: %s\n", yytext); }


<INITIAL>"{"     { printf("curly_bracket_open: %s\n", yytext); }
<INITIAL>"}"     { printf("curly_bracket_close: %s\n", yytext); }
"("     { printf("round_bracket_open: %s\n", yytext); }
")"     { printf("round_bracket_close: %s\n", yytext); }
"["     { printf("square_bracket_open: %s\n", yytext); }
"]"     { printf("square_bracket_close: %s\n", yytext); }

"++"    { printf("increment: %s\n", yytext); }
"--"    { printf("decrement: %s\n", yytext); }

"??="   { printf("null_coalescing_assignment: %s\n", yytext); }
">>>="  { printf("unsigned_shift_right_assignment: %s\n", yytext); }
"<<="   { printf("shift_left_assignment: %s\n", yytext); }
">>="   { printf("shift_right_assignment: %s\n", yytext); }
"~/="   { printf("integer_division_assignment: %s\n", yytext); }
"*="    { printf("multiplication_assignment: %s\n", yytext); }
"/="    { printf("division_assignment: %s\n", yytext); }
"+="    { printf("addition_assignment: %s\n", yytext); }
"-="    { printf("subtraction_assignment: %s\n", yytext); }
"&="    { printf("bitwise_and_assignment: %s\n", yytext); }
"^="    { printf("bitwise_xor_assignment: %s\n", yytext); }
"%="    { printf("remainder_assignment: %s\n", yytext); }
"|="    { printf("bitwise_or_assignment: %s\n", yytext); }

">>>"   { printf("unsigned_shift_right: %s\n", yytext); }
"<<"    { printf("shift_left: %s\n", yytext); }
">>"    { printf("shift_right: %s\n", yytext); }

"~/"    { printf("integer_division: %s\n", yytext); }
"*"     { printf("multiplication: %s\n", yytext); }
"/"     { printf("division: %s\n", yytext); }
"+"     { printf("addition: %s\n", yytext); }
"-"     { printf("subtraction: %s\n", yytext); }
"%"     { printf("remainder: %s\n", yytext); }

"&"     { printf("bitwise_and: %s\n", yytext); }
"^"     { printf("bitwise_xor: %s\n", yytext); }
"|"     { printf("bitwise_or: %s\n", yytext); }
"~"     { printf("bitwise_not: %s\n", yytext); }

">="    { printf("greater_equal: %s\n", yytext); }
"<="    { printf("less_equal: %s\n", yytext); }
"=="    { printf("equal: %s\n", yytext); }
"!="    { printf("not_equal: %s\n", yytext); }
">"     { printf("greater: %s\n", yytext); }
"<"     { printf("less: %s\n", yytext); }

"&&"    { printf("logical_and: %s\n", yytext); }
"||"    { printf("logical_or: %s\n", yytext); }
"!"     { printf("logical_not: %s\n", yytext); }

"??"    { printf("null_coalescing: %s\n", yytext); }

"=>"    { printf("function_arrow: %s\n", yytext); }

"?."    { printf("null_aware_access: %s\n", yytext); }
"?.."   { printf("null_aware_cascade: %s\n", yytext); }
".."    { printf("cascade: %s\n", yytext); }

"="     { printf("assignment: %s\n", yytext); }

"."     { printf("dot: %s\n", yytext); }
","     { printf("comma: %s\n", yytext); }
":"     { printf("colon: %s\n", yytext); }
";"     { printf("semicolon: %s\n", yytext); }


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
<MULTILINE_COMMENT_STATE>"/*" {yy_push_state(MULTILINE_COMMENT_STATE); printf("Start of a multi-line comment (yytext = %s)\n", yytext);}
<MULTILINE_COMMENT_STATE>"*/" {yy_pop_state(); printf("End of multi-line comment (yytext = %s)\n", yytext);}
<MULTILINE_COMMENT_STATE>[^*/]+ {}
<MULTILINE_COMMENT_STATE>"*"+[^*/]* {}
<MULTILINE_COMMENT_STATE>"/"+[^*/]* {}
<MULTILINE_COMMENT_STATE><<EOF>> {printf("Error: multi-line comment not closed (line #%d)\n", yylineno); yy_pop_state();}

"//"[^\n]* {printf("A standard comment (yytext = %s)\n", yytext);}




"r'" {pushStringChar('\''); pushStringBuffer(); yy_push_state(RAW_STRING_SINGLE_STATE); printf("START of a RAW string with a SINGLE quote (yytext = %s)\n", yytext); }
"r\"" {pushStringChar('\"'); pushStringBuffer(); yy_push_state(RAW_STRING_DOUBLE_STATE); printf("START of a RAW string with a DOUBLE quote (yytext = %s)\n", yytext); }

<RAW_STRING_SINGLE_STATE>"'" {
    popStringChar();
    char* str = peekStringBuffer();
    if (str != NULL) 
        printf("%s\n", str);

    popStringBuffer();
    yy_pop_state();
    printf("END of a RAW string with a SINGLE quote (yytext = %s)\n", yytext);
}
<RAW_STRING_DOUBLE_STATE>"\"" {
    popStringChar();
    char* str = peekStringBuffer();
    if (str != NULL) 
        printf("%s\n", str);

    popStringBuffer();
    yy_pop_state();
    printf("END of a RAW string with a DOUBLE quote (yytext = %s)\n", yytext);
}
<RAW_STRING_SINGLE_STATE>[^']+ {addTextToCurrentString(yytext);}
<RAW_STRING_DOUBLE_STATE>[^"]+ {addTextToCurrentString(yytext);}

<RAW_STRING_SINGLE_STATE,RAW_STRING_DOUBLE_STATE><<EOF>> {printf("Error: no end of RAW string in (line #%d)\n", yylineno); yy_pop_state();}


"'" {pushStringChar('\''); pushStringBuffer(); yy_push_state(STRING_SINGLE_STATE); printf("START of a STRING with a SINGLE quote (yytext = %s)\n", yytext); }
"\"" {pushStringChar('\"'); pushStringBuffer(); yy_push_state(STRING_DOUBLE_STATE); printf("START of a STRING with a DOUBLE quote (yytext = %s)\n", yytext); }


<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\\n" {addTextToCurrentString("\n");}
<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\\t" {addTextToCurrentString("\t");}
<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\\r" {addTextToCurrentString("\r");}
<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\\b" {addTextToCurrentString("\b");}
<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\\\\" {addTextToCurrentString("\\");}
<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\\'" {addTextToCurrentString("\'");}
<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\\\"" {addTextToCurrentString("\"");}
<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\\\$" {addTextToCurrentString("\$");}
<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\\u"[0-9a-fA-F]{4} {}
<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\\u{"[0-9a-fA-F]+"}" {}
<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\\". {}

<STRING_SINGLE_STATE>"'" {
    popStringChar();
    char* str = peekStringBuffer();
    if (str != NULL) 
        printf("%s\n", str);

    popStringBuffer();
    yy_pop_state();
    printf("END of a STRING with a SINGLE quote (yytext = %s)\n", yytext);
}
<STRING_DOUBLE_STATE>"\"" {
    popStringChar();
    char* str = peekStringBuffer();
    if (str != NULL) 
        printf("%s\n", str);

    popStringBuffer();
    yy_pop_state();
    printf("END of a STRING with a DOUBLE quote (yytext = %s)\n", yytext);
}

<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\$"[a-zA-Z_][a-zA-Z0-9_]* {printf("Simple interpolation (yytext = %s)\n", yytext); }
<STRING_SINGLE_STATE,STRING_DOUBLE_STATE>"\${" {pushStringChar('\$'); yy_push_state(INTERPOLATION_STATE); printf("START of INTERPOLATION (yytext = %s)\n", yytext); }

<STRING_SINGLE_STATE>[^'\\$]+ {addTextToCurrentString(yytext);}
<STRING_DOUBLE_STATE>[^"\\$]+ {addTextToCurrentString(yytext);}

<STRING_SINGLE_STATE,STRING_DOUBLE_STATE><<EOF>> {
    printf("Error: no end of STRING in (line #%d)\n", yylineno);
    while (peekStringChar() != 0) {
        popStringChar();
    } 
    yy_pop_state(); }




<INTERPOLATION_STATE>"{" {pushStringChar('{'); printf("Opening curly brace in interpolation\n");}
<INTERPOLATION_STATE>"}" {
    if (peekStringChar() == '{') {
        popStringChar();
        printf("Closing curly brace in interpolation\n");
    }
    else if (peekStringChar() == '\$') {
        popStringChar();
        yy_pop_state();
        printf("END of INTERPOLATION\n");
    }
    else {
        printf("Unexpected } in interpolation");
    }
}

<INTERPOLATION_STATE><<EOF>> {
    printf("Error: no end of INTERPOLATION in (line #%d)\n", yylineno);
    while (peekStringChar() != '"' && peekStringChar() != '\'' && peekStringChar() != 0) {
        popStringChar();
    }
    yy_pop_state();
}

%%

//Delete '_'
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