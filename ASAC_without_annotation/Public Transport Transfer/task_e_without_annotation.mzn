include "all_different.mzn";
int: n;
array[1..n] of int: ty;
array[1..n] of int: price;
array[1..n] of int: time;
array[1..n, 1..n] of var bool: used;
array[1..n] of var int: take;
var int: total;
predicate propagate(int: i, int: j) =
  if(ty[i] == 0) then (if j == i then true else if i > 1 then used[i-1, j] else false endif endif)
  else (if i == 1 then false else if j == i \/ j == take[i] then false else used[i-1, j] endif endif)
  endif;
predicate could(int: i, var int: j) = (j == i) \/ (ty[j] == 0 /\ time[i] - time[j] <= 45 /\ price[j] >= price[i] /\ used[i-1, j]);
predicate couldnot(int: i, var int: j) = forall(k in 1..j-1) (not could(i, k));
predicate take_bus(int: i) = could(i, take[i]) /\ couldnot(i, take[i]);
constraint forall(i in 1..n)(1 <= take[i] /\ take[i] <= i);
constraint total == sum(i in 1..n)(if take[i] == i then price[take[i]] else 0 endif);
constraint forall(i in 1..n)(if ty[i] == 0 then take[i] == i endif);
constraint forall(i in 1..n) (forall(j in 1..i) (used[i, j] == propagate(i, j)));
constraint forall(i in 1..n)(if ty[i] == 1 then take_bus(i) endif);
solve satisfy;
output["\(total)"];
