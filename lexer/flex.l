%{
#include <stdio.h>
%}

%option yylineno



%x MULTILINE_COMMENT_STATE

%x STRING_STATE
%x RAW_STRING_STATE

%{
    #define MAX_STRING_LENGTH = 100;
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
"/*"  {yy_push_state(MULTILINE_COMMENT_STATE); printf("Start of a multi-line comment\n");}
<MULTILINE_COMMENT_STATE>"/*" {yy_push_state(MULTILINE_COMMENT_STATE); printf("Start of a multi-line comment\n");}
<MULTILINE_COMMENT_STATE>"*/" {yy_pop_state(); printf("End of multi-line comment\n");}
<MULTILINE_COMMENT_STATE>(.|\n) {}
<MULTILINE_COMMENT_STATE><<EOF>> {printf("Error: multi-line comment not closed (line #%d)\n", yylineno); yy_pop_state();}

"//"[^\n]* {printf("A standard comment\n");}


/*Состояние строки raw*/

"r'" {pushStringChar('\''); yy_push_state(RAW_STRING_STATE); printf("START of a RAW string with a SINGLE quote\n"); }
"r\"" {pushStringChar('\"'); yy_push_state(RAW_STRING_STATE); printf("START of a RAW string with a DOUBLE quote\n"); }

<RAW_STRING_STATE>"'" {
    if (peekStringChar() == '\'') {
        popStringChar();
        yy_pop_state();
        printf("END of a RAW string with a SINGLE quote\n");
    }
}
<RAW_STRING_STATE>"\"" {
    if (peekStringChar() == '"') {
        popStringChar();
        yy_pop_state();
        printf("END of a RAW string with a DOUBLE quote\n");
    }
}
<RAW_STRING_STATE>[^"'] {}
<RAW_STRING_STATE><<EOF>> {printf("Error: no end of RAW string in (line #%d)\n, yylineno"); }



%%



void main( int argc, char** argv )
{
    ++argv, --argc;
    if ( argc > 0 )
        yyin = fopen( argv[0], "r" );
    else
        yyin = stdin;

    yylex();
}