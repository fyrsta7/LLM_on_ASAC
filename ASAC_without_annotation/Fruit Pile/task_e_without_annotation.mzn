int: n;
array[1..n] of int: fruit;
array[1..n,1..n] of var int: stat;
array[2..n,1..2] of var 1..n: merge;
var int: stamina;
constraint forall(i in 2..n)(merge[i,1] != merge[i,2] /\ stat[i-1,merge[i,1]] != 0 /\ stat[i-1,merge[i,2]] != 0);
constraint stat[1,1..n] = fruit;
constraint forall(i in 2..n)(stat[i,merge[i,1]] = stat[i-1,merge[i,1]] + stat[i-1,merge[i,2]] /\ stat[i,merge[i,2]] = 0 /\ forall(j in 1..n where j != merge[i,1] /\ j != merge[i,2])(stat[i,j] = stat[i-1,j]) );
constraint stamina = sum([ stat[i-1,merge[i,1]] + stat[i-1,merge[i,2]] | i in 2..n]);
solve minimize stamina;
output[show(stamina)];
