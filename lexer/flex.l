%{
#include <stdio.h>
#include <string.h>
%}

%option yylineno



%x MULTILINE_COMMENT_STATE

%x STRING_STATE
%x RAW_STRING_STATE

%x INTERPOLATION_STATE

%{
    #define MAX_STRING_LENGTH 200
    static char stringStack[MAX_STRING_LENGTH];
    static int stringStackTop = -1;

    static void pushStringChar(char c) {
        if (stringStackTop < MAX_STRING_LENGTH - 1)
            stringStack[++stringStackTop] = c;
    }

    static char popStringChar() {
        if (stringStackTop >= 0)
            return stringStack[stringStackTop--];
        return 0;
    }

    static char peekStringChar() {
        if (stringStackTop >= 0)
            return stringStack[stringStackTop];
        return 0;
    }
%}

%%



/*Состояние комментария*/
"/*"  {yy_push_state(MULTILINE_COMMENT_STATE); printf("Start of a multi-line comment (yytext = %s)\n", yytext);}
<MULTILINE_COMMENT_STATE>"/*" {yy_push_state(MULTILINE_COMMENT_STATE); printf("Start of a multi-line comment (yytext = %s)\n", yytext);}
<MULTILINE_COMMENT_STATE>"*/" {yy_pop_state(); printf("End of multi-line comment (yytext = %s)\n", yytext);}
<MULTILINE_COMMENT_STATE>(.|\n) {}
<MULTILINE_COMMENT_STATE><<EOF>> {printf("Error: multi-line comment not closed (line #%d)\n", yylineno); yy_pop_state();}

"//"[^\n]* {printf("A standard comment (yytext = %s)\n", yytext);}



/*Состояние строки raw*/

"r'" {pushStringChar('\''); yy_push_state(RAW_STRING_STATE); printf("START of a RAW string with a SINGLE quote (yytext = %s)\n", yytext); }
"r\"" {pushStringChar('\"'); yy_push_state(RAW_STRING_STATE); printf("START of a RAW string with a DOUBLE quote (yytext = %s)\n", yytext); }

<RAW_STRING_STATE>"'" {
    if (peekStringChar() == '\'') {
        popStringChar();
        yy_pop_state();
        printf("END of a RAW string with a SINGLE quote (yytext = %s)\n", yytext);
    }
}
<RAW_STRING_STATE>"\"" {
    if (peekStringChar() == '"') {
        popStringChar();
        yy_pop_state();
        printf("END of a RAW string with a DOUBLE quote (yytext = %s)\n", yytext);
    }
}
<RAW_STRING_STATE>[^"'] {}
<RAW_STRING_STATE><<EOF>> {printf("Error: no end of RAW string in (line #%d)\n", yylineno); yy_pop_state();}



/*Состояние обычной строки в формате "" и '' */

"'" {pushStringChar('\''); yy_push_state(STRING_STATE); printf("START of a STRING with a SINGLE quote (yytext = %s)\n", yytext); }
"\"" {pushStringChar('\"'); yy_push_state(STRING_STATE); printf("START of a STRING with a DOUBLE quote (yytext = %s)\n", yytext); }

// Служебные символы

<STRING_STATE>"\\n" {printf("Control characters \\n Newline (yytext = %s)\n", yytext); }
<STRING_STATE>"\\t" {printf("Control characters \\t Tab (yytext = %s)\n", yytext); }
<STRING_STATE>"\\r" {printf("Control characters \\r Carriage return (yytext = %s)\n", yytext); }
<STRING_STATE>"\\b" {printf("Control characters \\b Backspace (yytext = %s)\n", yytext); }
<STRING_STATE>"\\\\" {printf("Control characters \\\\ Backlash (yytext = %s)\n", yytext); }
<STRING_STATE>"\\'" {printf("Control characters \\' Single quote (yytext = %s)\n", yytext); }
<STRING_STATE>"\\\"" {printf("Control characters \\\" Double quote (yytext = %s)\n", yytext); }
<STRING_STATE>"\\\$" {printf("Control characters \\$ Dollar (yytext = %s)\n", yytext); }
<STRING_STATE>"\\u"[0-9a-fA-F]{4} {printf("Control characters unicod (yytext = %s)\n", yytext); }
<STRING_STATE>"\\u{"[0-9a-fA-F]+"}" {printf("Control characters unicod extended (yytext = %s)\n", yytext); }
<STRING_STATE>"\\". {printf("Control characters \\. escaping (yytext = %s)\n", yytext); }

<STRING_STATE>"'" {
    if (peekStringChar() == '\'') {
        popStringChar();
        yy_pop_state();
        printf("END of a STRING with a SINGLE quote (yytext = %s)\n", yytext);
    }
}
<STRING_STATE>"\"" {
    if (peekStringChar() == '"') {
        popStringChar();
        yy_pop_state();
        printf("END of a STRING with a DOUBLE quote (yytext = %s)\n", yytext);
    }
}

// правило интерполяции
<STRING_STATE>"\$"[a-zA-Z_][a-zA-Z0-9_]* {printf("Simple interpolation (yytext = %s)\n", yytext); }
<STRING_STATE>"\${" {pushStringChar('\$'); yy_push_state(INTERPOLATION_STATE); printf("START of INTERPOLATION (yytext = %s)\n", yytext); }

<STRING_STATE>[^'"\\] {}
<STRING_STATE><<EOF>> {
    printf("Error: no end of STRING in (line #%d)\n", yylineno);
    while (peekStringChar() != 0) {
        popStringChar();
    } 
    yy_pop_state(); }



/*Состояние интерполяции*/

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

// строки внутри интерполяции

<INTERPOLATION_STATE>"'" {pushStringChar('\''); yy_push_state(STRING_STATE); printf("START of a STRING with a SINGLE quote in INTERPOLATION (yytext = %s)\n", yytext);}
<INTERPOLATION_STATE>"\"" {pushStringChar('"'); yy_push_state(STRING_STATE); printf("START of a STRING with a DOUBLE quote in INTERPOLATION (yytext = %s)\n", yytext);}

// комментарии внутри интерполяции

<INTERPOLATION_STATE>"//"[^\n]* {printf("A standard comment (yytext = %s)\n", yytext);}
<INTERPOLATION_STATE>"/*" {yy_push_state(MULTILINE_COMMENT_STATE); printf("Start of a multi-line comment (yytext = %s)\n", yytext);}

<INTERPOLATION_STATE>(.|\n) {}
<INTERPOLATION_STATE><<EOF>> {
    printf("Error: no end of INTERPOLATION in (line #%d)\n", yylineno);
    while (peekStringChar() != '"' && peekStringChar() != '\'' && peekStringChar() != 0) {
        popStringChar();
    }
    yy_pop_state();
}

%%



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