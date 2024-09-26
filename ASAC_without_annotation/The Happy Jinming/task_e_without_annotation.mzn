int: n;
int: m;
array[1..m] of int: V;
array[1..m] of int: P;
array[1..m] of var 0..1: buy;
constraint (sum(i in 1..m)(V[i]*buy[i])) <= n;
var int: obj = (sum(i in 1..m)(V[i]*P[i]*buy[i]));
solve maximize obj;
output["\(obj)\n"]
