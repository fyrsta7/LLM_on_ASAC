include "alldifferent.mzn";
int: N;
array[1..3, 1..N] of string: add;
array[1..26] of string: alphabet=["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"];
array[1..N] of var 0..N-1: result;
constraint alldifferent(result);
array[1..3, 1..N] of var 1..N: add_num;
constraint forall(i in 1..3, j in 1..N)(add_num[i, j] = min([l | l in 1..N where alphabet[l] = add[i, j]]));
predicate calculate(array[1..3, 1..N] of var int: cal, var int: i, var int: flag) =
  i = 0 \/ ((cal[1, i] + cal[2, i] + flag) mod N = cal[3, i] /\ calculate(cal, i - 1, (cal[1, i] + cal[2, i] + flag) div N));
constraint let{
  array[1..3, 1..N] of var int: tmp;
  constraint forall(i in 1..3, j in 1..N)(tmp[i, j] = result[add_num[i, j]]);
} in calculate(tmp, N, 0);
solve satisfy;
output[show(result[1..N])];
