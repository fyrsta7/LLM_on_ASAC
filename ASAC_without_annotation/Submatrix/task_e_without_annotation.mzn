int: N;
int: M;
int: R;
int: C;
array[1 .. N, 1 .. M] of int: a;
array[1 .. R] of var int: b;
array[1 .. C] of var int: c;
constraint 1 <= b[1] /\ b[R] <= N;
constraint forall(i in 1 .. R-1)(b[i] < b[i+1]);
constraint 1 <= c[1] /\ c[C] <= M;
constraint forall(i in 1 .. C-1)(c[i] < c[i+1]);
var int: score;
score = sum(i in 1 .. R-1, j in 1 .. C)(abs(a[b[i], c[j]] - a[b[i + 1], c[j]]))
      + sum(i in 1 .. R, j in 1 .. C-1)(abs(a[b[i], c[j]] - a[b[i], c[j + 1]]));
solve minimize score;
output ["score=" ++ show(score)];
