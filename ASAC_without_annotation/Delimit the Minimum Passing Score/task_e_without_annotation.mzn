include "alldifferent.mzn";
int: n;
int: m;
array[1..n] of int: id;
array[1..n] of int: score;
var 1..100: split;
var int: num = floor(m * 1.5);
var int: actual;
array[1..n] of var 1..n: pass;
constraint count([score[i] >= split | i in 1..n]) = actual;
constraint actual >= num;
constraint alldifferent(pass);
constraint forall(i in 1..actual)(score[pass[i]] >= split);
constraint forall(i in 1..actual-1)(
  score[pass[i]] > score[pass[i+1]]
  \/
  (score[pass[i]] = score[pass[i+1]] /\ id[pass[i]] < id[pass[i+1]])
);
solve maximize split;
output[show(split) ++ " " ++ show(actual) ++ "\n"];
output[show(id[pass[i]]) ++ " " ++ show(score[pass[i]]) ++ "\n" | i in 1..fix(actual)];
