E   ->  TE'
E'  ->  + TE' | ε
T   ->  FT'
T'  ->  * FT' | ε
F   ->  ( E ) | int

value -> term add_op_tail
term -> factor mul_op_tail
factor -> int | (value)
add_op_tail -> + term add_op_tail
              | - term add_op_tail
              | ε
mul_op_tail -> * factor mul_op_tail
              | / factor mul_op_tail
              | ε