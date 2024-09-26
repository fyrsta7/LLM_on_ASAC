int: N;
array[1..N] of int: T;
var 1..N: turns;
var 1..N: x;
array[0..N] of var int: y;
constraint y[0] = x /\ y[turns] = x;
constraint forall(i in 1..turns)(y[i] = T[y[i - 1]]);
solve minimize turns;
output["turns=" ++ show(turns)];
