int: N;
array[1..N] of int: T;
array[1..N] of var bool: Select;
var int: discard_num = sum(Select);
constraint exists(i in 1..N where Select[i] == false)(
  forall(j in 1..N, k in 1..N)(
    (j >= k) \/ Select[j] \/ Select[k] \/ (((k > i) \/ (T[j] < T[k])) /\ ((j < i) \/ (T[j] > T[k])))
  )
);
solve minimize discard_num;
output ["\(discard_num)"];
