include "alldifferent.mzn";
int: n;
array[1..n] of int: a;
array[1..n] of int: b;
int: max_exchange = n * n;
predicate exchange(array[1..n] of var int: before, array[1..n] of var int: after, var 1..n-1: loc) =
forall(i in 1..loc-1)(after[i] = before[i]) /\ forall(i in loc+2..n)(after[i] = before[i]) /\ after[loc] = before[loc+1] /\ after[loc+1] = before[loc];
function int: factorial(int: f) =
if f == 0 then 1
else factorial(f-1) * f endif;
var int: min_distance =
let{
int: len = factorial(n);
array[1..len, 1..n] of var 1..n: tmp;
constraint forall(i in 1..len)(all_different(tmp[i, 1..n]));
constraint forall(i, j in 1..len where i != j)(not(forall(k in 1..n)(tmp[i, k] = tmp[j, k])));
var int: distance = min(i in 1..len)(sum(j in 1..n)(pow(a[j] - tmp[i, j], 2)));
} in distance;
var 0..max_exchange: times1;
var 0..max_exchange: times2;
array[0..max_exchange, 1..n] of var int: state1;
array[0..max_exchange, 1..n] of var int: state2;
array[0..max_exchange] of var 1..n-1: exchange1;
array[0..max_exchange] of var 1..n-1: exchange2;
constraint state1[0, 1..n] = a;
constraint state2[0, 1..n] = b;
constraint forall(i in 1..times1)(exchange(state1[i, 1..n], state1[i-1, 1..n], exchange1[i]));
constraint forall(i in 1..times2)(exchange(state2[i, 1..n], state2[i-1, 1..n], exchange2[i]));
constraint sum(i in 1..n)(pow(state1[times1, i] - state2[times2, i], 2)) = min_distance;
solve minimize times1 + times2;
output[show((times1 + times2) mod 99999997)];
