Expr -> Assign
Assign -> Compare Assign'
Assign' -> = Compare | ε
Compare -> Add Compare'
Compare' -> == Add | > Add | < Add | >= Add |  <= Add | != Add | ε
Add   -> Term Expr'
Add'  -> + Term Expr' | - Term Expr' | ε
Term   -> Factor Term'
Term'  -> * Factor Term' | / Factor Term' | ε
Factor -> ( Expr ) | Int | DefineVariable
ExprList -> Expr ExprList' | ε
ExprList' -> , Expr ExprList' | ε
FunctionCall -> @ Id ( ExprList )
Sentence -> Expr ; | If | Else | While | DoWhile | For | Break | Continue | Return

/* IMPORTANT NOTE: { and } will not record to Tree */
Statements -> { Sentences | Sentence
Sentences -> Sentence Sentences | Sentence | }

DefineFuction -> fn Type Id ( ExprList ) Statements
DefineVariable -> Type Id

If -> if ( Expr ) Statements
Else -> else Statements
While -> while ( Expr ) Statements
DoWhile -> do Statements while ( Expr ) ;
For -> for (Expr ; Expr ; Expr ) Statements

Break -> break ;
Continue -> continue ;
Return -> return Expr ;
