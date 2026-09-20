%{
#include <stdio.h>
%}

%option yylineno



%x MULTILINE_COMMENT_STATE

%%




"/*"  {yy_push_state(MULTILINE_COMMENT_STATE); printf("Start of a multi-line comment\n");}
<MULTILINE_COMMENT_STATE>"/*" {yy_push_state(MULTILINE_COMMENT_STATE); printf("Start of a multi-line comment\n");}
<MULTILINE_COMMENT_STATE>"*/" {yy_pop_state(); printf("End of multi-line comment\n");}
<MULTILINE_COMMENT_STATE>(.|\n) {}
<MULTILINE_COMMENT_STATE><<EOF>> {printf("Error: multi-line comment not closed (line #%d)\n", yylineno); yy_pop_state();}

"//"[^\n]* {printf("A standard comment\n");}



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