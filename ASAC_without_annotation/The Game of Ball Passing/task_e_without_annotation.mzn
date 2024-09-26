int: n;
int: m;
int: bound = pow(2, m);
array[1..bound, 1..m+1] of var 1..n: balls;
var int: num;
constraint num >= 0 /\ num < bound;
predicate neighbor(var int: a, var int: b) =
    abs(a - b) = 1 \/ (a = n /\ b = 1) \/ (a = 1 /\ b = n);
constraint forall(i in 1..num)
    (balls[i, 1] = 1 /\ balls[i, m+1] = 1 /\ forall(j in 1..m)(neighbor(balls[i, j], balls[i, j+1])));
constraint forall(j, k in 1..num where j < k)(exists(l in 1..m+1)(balls[j, l] != balls[k, l]));
solve maximize num;
output[show(num) ++ "\n"];
