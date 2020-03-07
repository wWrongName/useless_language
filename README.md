# useless_language
Interpreter for little esoteric language

#### The structure.
* numbers (number 0)
* variable tables and buffer:
    1. table of variables (number 1)
    2. temporary buffer for compiler
* permanent tables
    1. key symbols(mathematical, loop, logical, system)
- Table2 (mathematical):
0. :) plus
1. :( minus
2. :D multiply
3. :x divide
- Table3 (loop):
0. < assignment
1. @ beginning of a condition and beginning of a loop
2. > end of a condition (all actions of a loop announce after main function)
3. @> end of loop
- Table4 (logical):
0. :b greater
1. :p less
2. :e equal
3. :! not equal
- Table5 (system):
0. :wow show character
1. :lol show digit
2. <-

#### Conditions.
- name of loop must be numbered (@1 or @2 etc.)
- :lol comand show only one variable

#### Example.
- ->
- {1}<25}
- {2}<50}
- {2}<{1}:){2} 
- @1}{1}:!65}>
- :lol{1}
- <-
- @1}
- {1}<{1}:(5}
- @>
