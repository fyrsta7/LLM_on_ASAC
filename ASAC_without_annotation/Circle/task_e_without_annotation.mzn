int: n;
int: k;
int: len = pow(10, k);
array[1..len] of var int: suffix;
constraint forall(i in 1..len)(suffix[i] = pow(n, i) mod pow(10, k));
solve satisfy;
var set of int: out_set = {i | i in 2..len where suffix[i] = suffix[1]};
output[if (fix(suffix[1]) in array2set(fix(suffix[2..len]))) then "\(min(fix(out_set))-1)" else "-1" endif];
