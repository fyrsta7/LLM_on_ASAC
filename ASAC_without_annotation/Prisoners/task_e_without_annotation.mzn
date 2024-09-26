int: N;
int: M;
array[1..M, 1..3] of int: conflict;
set of int: full_set = 1..N;
var set of full_set: prison1;
var set of full_set: prison2;
constraint prison1 union prison2 = full_set;
constraint card(prison1 intersect prison2) = 0;
var int: value1;
var int: value2;
constraint value1 = if card(prison1) < 2 then 0 else
max([conflict[i, 3] | i in 1..M where conflict[i, 1] in prison1 /\ conflict[i, 2] in prison1 ]) endif;
constraint value2 = if card(prison2) < 2 then 0 else
max([conflict[i, 3] | i in 1..M where conflict[i, 1] in prison2 /\ conflict[i, 2] in prison2 ]) endif;
var int: final_value = max(value1, value2);
solve minimize final_value;
output[show(final_value)];
