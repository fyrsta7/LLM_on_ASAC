int: n;
int: k;
int: p;
array[1..n, 1..2] of int: hotel;
array[1..n*n div 2, 1..2] of var 1..n: plans;
var 1..n*n div 2: num;
constraint forall(i in 1..num)(plans[i, 1] < plans[i, 2] /\ hotel[plans[i, 1], 1] = hotel[plans[i, 2], 1]
/\ exists(t in plans[i, 1]..plans[i, 2])(hotel[t, 2] <= p));
constraint forall(i, j in 1..num where i != j)(not(plans[i, 1] = plans[j, 1] /\ plans[i, 2] = plans[j, 2]));
solve maximize num;
output[show(num)];
