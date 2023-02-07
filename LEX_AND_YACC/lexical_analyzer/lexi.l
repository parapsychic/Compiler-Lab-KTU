%{
  int COMMENT = 0;
%}

IDENTIFIER [a-zA-Z][a-zA-Z0-9]*

%%
#.* {printf("%s is a preprocessor directive\n", yytext);}
"/*".* {COMMENT=1;}
.*"*/" {if(COMMENT) COMMENT=0;}
"//".* {}
int |
float |
char |
double |
void |
struct |
typedef |
if |
else |
switch |
for |
while |
do |
break |
continue |
goto |
return {if(!COMMENT) printf("%s is a keyword\n", yytext);}
{IDENTIFIER}\( {if(!COMMENT) printf("%s is a FUNCTION\n", yytext);}
\{ {if(!COMMENT) printf("BLOCK START\n");}
\} {if(!COMMENT) printf("BLOCK END\n");}
\".*\" {if(!COMMENT) printf("STRING: %s\n", yytext);}
[0-9]+ {if(!COMMENT) printf("NUMBER: %s\n", yytext);}
{IDENTIFIER} {if(!COMMENT) printf("%s is an identifier.\n", yytext);}
[\+\-\*/] {if(!COMMENT) printf("%s is an operator\n", yytext);}
[=] {if(!COMMENT) printf("%s is a assignment operator\n", yytext);}
\<= |
\>= |
\> |
== |
\< {if(!COMMENT) printf("%s is relational operator\n",yytext);}
[\),;" "\n\t\.] {}
%%

int main(void){
  FILE * file = fopen("file.c", "r");
  if(!file){
    printf("NO SUCH FILE");
    return -1;
  }
  yyin = file;
  yylex();
  printf("\0");
  return 0;
}

int yywrap(){
  return 1;
}
