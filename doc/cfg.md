/* IMPORTANT NOTE: {}, () and @ will not record to Tree */
Expr -> Assign
Assign -> Compare Assign'
Assign' -> = Compare | ε
Compare -> Add Compare'
Compare' -> == Add | > Add | < Add | >= Add |  <= Add | != Add | ε
Add   -> Times Add'
Add'  -> + Times Add' | - Times Add' | ε
Times   -> Power Times'
Times'  -> * Power Times' | / Power Times' | ε
Power   -> Factor Power'
Power'  -> ** Factor | ε
Factor -> ( Expr ) | Int | DefineVariable | FunctionCall
ExprList -> Expr ExprList' | ε
ExprList' -> , Expr ExprList' | ε
FunctionCall -> @ Id ( ExprList )
Sentence -> Expr ; | If | Else | While | DoWhile | For | Break | Continue | Return

Statements -> { Sentences | Sentence
Sentences -> Sentence ... }

DefineFuction -> fn Type Id ( ExprList ) Statements
DefineVariable -> Type Id

/* ATTENTION: if, else, while, do and for will not record to Tree */
If -> if ( Expr ) Statements Else
Else -> else Statements | ε
While -> while ( Expr ) Statements
DoWhile -> do Statements while ( Expr ) ;
For -> for (Expr ; Expr ; Expr ) Statements

Break -> break ;
Continue -> continue ;
Return -> return Expr ;
