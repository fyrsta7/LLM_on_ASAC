int: n;
int: m;
array[1..n+1] of int: coefficient;
array[1..m] of var bool: if_solution;
constraint forall(i in 1..m) (if_solution[i] = (sum([coefficient[j+1] * pow(i, j) | j in 0..n]) == 0));
var int: solution_num = count(i in 1..m)(if_solution[i]);
solve satisfy;
output[show(solution_num) ++ "\n"];
output[if fix(if_solution[i]) then "\(i)\n" else "" endif | i in 1..m];
