int: n;
int: m;
array[1..n] of int: A;
array[1..n] of var 0..m: B;
constraint forall(i in 1..n)(
  B[i] <= A[i]
);
constraint sum(i in 1..n)(B[i]) = m;
solve satisfy;
