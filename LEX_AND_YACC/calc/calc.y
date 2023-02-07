%{
 #include <stdio.h>
 int flag = 0;
%}

%token NUMBER
%left '+' '-' '/' '*' '%' ')' '('

%%
 ArithmeticExpression: E{
        printf("Result=%d\n",$$);
        return 0;
 } 

E : E'+'E {$$ = $1 + $3;}
  | E'-'E {$$ = $1 - $3;}
  | E'*'E {$$ = $1 * $3;}
  | E'/'E {$$ = $1 / $3;}
  | E'%'E {$$ = $1 % $3;}
  | '('E')' {$$ = $2;}
  | NUMBER {$$ = $1;}
  ;
%%

int main(){
  printf("Enter the expression: ");
  yyparse();
  
  if(flag == 0)
  {
    printf("Expression is valid\n");
  }
}

int yyerror(){
  printf("Some error occured!") ;
  flag = 1;
  return 0;
}
