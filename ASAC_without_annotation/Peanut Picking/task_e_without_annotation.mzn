int: M;
int: N;
int: K;
array[1..M, 1..N] of int: peanuts;
set of int: peanut_set = array_union([array2set(peanuts[i, 1..N]) | i in 1..M]) diff {0};
var set of peanut_set: pick_set;
enum action = {up, down, left, right, pick, wait};
array[1..K] of var action: action_list;
array[0..K, 1..2] of var int: position;
var int: num;
predicate move(var action: act, var int: before_x, var int: before_y, var int: after_x, var int: after_y) =
    if act = up then before_x = after_x + 1 /\ before_y = after_y
    elseif act = down then before_x = after_x - 1 /\ before_y = after_y
    elseif act = left then before_x = after_x /\ before_y = after_y + 1
    elseif act = right then before_x = after_x /\ before_y = after_y - 1
    else before_x = after_x /\ before_y = after_y
    endif;
constraint forall(i in 1..K-1)((position[i, 1] >= 1 /\ position[i, 1] <= M) /\ (position[i, 2] >= 1 /\ position[i, 2] <= N));
constraint action_list[1] = down /\ action_list[K] = up;
constraint position[0, 1] = 0 /\ position[K, 1] = 0;
constraint forall(i in 1..K)(move(action_list[i], position[i-1, 1], position[i-1, 2], position[i, 1], position[i, 2]));
constraint forall(i in 1..K)(if peanuts[position[i, 1], position[i, 2]] = 0 then action_list[i] != pick endif);
constraint forall(i, j in 1..K where i < j /\ action_list[i] = pick /\ action_list[j] = pick)(peanuts[position[i, 1], position[i, 2]] > peanuts[position[j, 1], position[j, 2]]);
constraint forall(i in 1..K where action_list[i] = pick)(peanuts[position[i, 1], position[i, 2]] in pick_set);
constraint if peanut_set != pick_set then min(pick_set) >= max(peanut_set diff pick_set) endif;
constraint num = sum([peanuts[position[i, 1], position[i, 2]] | i in 1..K where action_list[i] = pick]);
solve maximize num;
output [show(num)];
