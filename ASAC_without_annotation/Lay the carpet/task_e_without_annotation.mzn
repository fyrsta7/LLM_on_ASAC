int: n;
array[1..n, 1..4] of int: carpets;
array[1..2] of int: loc;
predicate inside(var int: x, var int: y, array[1..4] of var int: carpet) =
  x >= carpet[1] /\ y >= carpet[2] /\ x <= carpet[1] + carpet[3] /\ y <= carpet[2] + carpet[4];
var set of 1..n: carpet_set;
set of int: full_set = 1..n;
constraint forall(i in 1..n)
  (if inside(loc[1], loc[2], carpets[i, 1..4]) then i in carpet_set else i in full_set diff carpet_set endif);
var int: ans;
constraint if card(carpet_set) = 0 then ans = -1 else ans = max(carpet_set) endif;
solve satisfy;
output[show(ans)];
