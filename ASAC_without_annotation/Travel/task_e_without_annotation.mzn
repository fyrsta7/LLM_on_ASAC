int: n;
int: m;
array[1..m, 1..2] of int: road;
array[1..2*n] of var 1..n: route;
var 1..2*n: length;
constraint route[length] = route[1];
constraint forall(i in 1..n)(exists(k in 1..length)(route[k] = i));
constraint forall(i in 2..length)(forall(j in 1..i-2)(route[i] != route[j])
\/ if min(j in 1..i-2 where route[j] = route[i-1])(j) >= 2 then route[i] = route[min(j in 1..i-2 where route[j] = route[i-1])(j) - 1] endif);
constraint forall(i in 2..length)
(exists(k in 1..m)((route[i] = road[k, 1] /\ route[i-1] = road[k, 2]) \/ (route[i] = road[k, 2] /\ route[i-1] = road[k, 1])));
array[1..n] of var 1..n: first;
constraint forall(i, j in 1..n where i < j)
    (min(k in 1..length where route[k] = first[i])(k) < min(k in 1..length where route[k] = first[j])(k));
var int: score;
constraint score = sum(i in 1..n)(pow(n, n - i) * first[i]);
solve minimize score;
output[show(first)];
