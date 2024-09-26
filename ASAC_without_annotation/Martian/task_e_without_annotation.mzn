include "alldifferent.mzn";
int: N;
int: M;
array[1..N] of 1..N: init_finger;
int: max_size = product([i | i in 1..N]);
array[1..max_size, 1..N] of var 1..N: fingers;
var int: ans;
predicate larger(array[1..N] of var 1..N: l, array[1..N] of var 1..N: r, var int: pointer) =
  if pointer = N+1 then false
  else l[pointer] > r[pointer] \/ (l[pointer] = r[pointer] /\ larger(l, r, pointer+1)) endif;
constraint forall(i in 1..max_size)(alldifferent(fingers[i, 1..N]));
constraint forall(i in 1..max_size-1)(larger(fingers[i+1, 1..N], fingers[i, 1..N], 1));
constraint let{
  var int: i;
  constraint forall(j in 1..N)(init_finger[j] = fingers[i, j]);
} in ans = i + M;
solve satisfy;
output[show(fingers[fix(ans), 1..N])];
