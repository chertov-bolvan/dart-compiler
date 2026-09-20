%{
#include <stdio.h>
%}

%option yylineno



%x MULTILINE_COMMENT_STATE
%{
    int commentDepth = 0;
}%

%%




"/*"  {BEGIN(MULTILINE_COMMENT_STATE); commentDepth++; printf("Начало многострочного комментария");}
<MULTILINE_COMMENT_STATE>"*/" {
    commentDepth--; if(commentDepth == 0) { 
        BEGIN(INITIAL); 
        printf("Конец многострочного комментария");
    }}
<MULTILINE_COMMENT_STATE>(.|\n) {}

"//"[^\n]* {printf("Обычный комментарий");}



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