%{
#include <stdio.h>
%}

%option yylineno



%x MULTILINE_COMMENT_STATE
%{
    int commentDepth = 0;
}%

%%




"/*"  {BEGIN(MULTILINE_COMMENT_STATE); commentDepth++; printf("Start of a multi-line comment\n");}
<MULTILINE_COMMENT_STATE>"*/" {
    commentDepth--; if(commentDepth == 0) { 
        BEGIN(INITIAL); 
        printf("End of multi-line comment\n");
    }}
<MULTILINE_COMMENT_STATE>(.|\n) {}
<MULTILINE_COMMENT_STATE><<EOF>> {printf("Error: multi-line comment not closed (line #%d)\n", yylineno); BEGIN(INITIAL);}

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