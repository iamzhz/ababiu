type → int | char | float | string | void
idList → id | id, idList
varDef → type idList
varDefArgs → type id | type id, varDefArgs
add → value
value → intValue | charValue | floatValue | stringValue | id | code
code → value ;
codes → code | code code
func → fn type (varDefArgs) co




















type -> 'int' | 'char' | 'float' | 'string'
value_head -> number
            | + value | - value | !value | ~value | * value | '(' type ')' value
value_tail -> = value | ε
value -> value_head value_tail




































value -> int value_tail
value_tail -> + value
            | - value
            | * value
            | / value
            | ε