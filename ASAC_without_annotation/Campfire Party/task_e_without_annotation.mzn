include "alldifferent.mzn";
int: n;
array[1..n, 1..2] of int: like;
array[1..n, 1..n] of var 1..n: shift;
array[1..n] of var 1..n: M;
array[1..n, 1..n] of var 1..n: position;
function var int: precede(int: i) =
  if i > 1 then i - 1 else n endif;
function var int: follow(int: i) =
  if i < n then i + 1 else 1 endif;
predicate move(array[1..n] of var int: before, array[1..n] of var int: after, array[1..n] of var int: shift_list, var 1..n: m) =
  forall(i in 1..m-1)(before[shift_list[i]] = after[shift_list[i+1]]) /\
  before[shift_list[m]] = after[shift_list[1]] /\
  forall(j in 1..n where forall(k in 1..m)(j != shift_list[k]))(after[j] = before[j]);
var 1..n: steps;
constraint forall(i in 1..steps)(alldifferent(shift[i, 1..n]));
constraint forall(i in 1..n)(alldifferent(position[i, 1..n]));
constraint forall(i in 1..n)(position[1, i] = i);
constraint forall(i in 1..n)(position[steps, precede(i)] = like[position[steps, i], 1] /\
  position[steps, follow(i)] = like[position[steps, i], 2] \/
  position[steps, precede(i)] = like[position[steps, i], 2] /\
  position[steps, follow(i)] = like[position[steps, i], 1]);
constraint forall(i in 1..steps-1)(move(position[i, 1..n], position[i+1, 1..n], shift[i, 1..n], M[i]));
var int: ans;
constraint ans = sum([M[i] | i in 1..steps-1]);
solve minimize ans;
output[show(ans)];
