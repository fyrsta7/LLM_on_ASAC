int: n;
array[1..n] of int: S;
array[1..n] of int: A;
array[1..n, 1..n] of var 0..1: choose;
array[1..n] of var 1..n: r;
array[1..n] of var int: c;
predicate valid(var 1..n: i) =
  choose[i, r[i]] == 1 /\ sum(j in 1..r[i]) (choose[i, j]) == i;
predicate cost(var 1..n: i, var int: w) =
  w == sum(j in 1..r[i]) (choose[i, j] * A[j]) + S[r[i]] * 2;
constraint forall (i in 1.. n) (valid(i) /\ cost(i, c[i]));
solve maximize sum(i in 1..n) (c[i]);
output["\(c)"];
