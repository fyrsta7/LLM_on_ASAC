int: n;
int: m;
array[1..n-1, 1..3] of int: road;
array[1..m] of var set of 1..n-1: race;
constraint forall(i, j in 1..m where i != j)(race[i] intersect race[j] = {});
predicate connected(var set of 1..n-1: s) =
    exists(i, j in 1..n where i != j)(sum(r in s where road[r,1] = i)(1) + sum(r in s where road[r,2] = i)(1) = 1 /\
    sum(r in s where road[r,1] = j)(1) + sum(r in s where road[r,2] = j)(1) = 1 /\
    forall(k in 1..n where k != i /\ k != j)(sum(r in s where road[r,1] = k)(1) + sum(r in s where road[r,2] = k)(1) = 2
    \/ sum(r in s where road[r,1] = k)(1) + sum(r in s where road[r,2] = k)(1) = 0));
constraint forall(i in 1..m)(connected(race[i]));
var int: min_len;
constraint min_len = min(i in 1..m)(sum(r in race[i])(road[r,3]));
solve maximize min_len;
output[show(min_len)];
