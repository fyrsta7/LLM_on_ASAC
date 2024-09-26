int: M;
int: S;
int: T;
enum action = {run, flash, rest};
var 1..T: min_time;
var int: max_dis;
array[1..T] of var action: action_list;
array[0..T] of var int: current_mana;
array[0..T] of var int: current_dis;
constraint current_dis[0] = 0;
constraint current_mana[0] = M;
constraint forall(i in 1..T)(current_mana[i] >= 0);
constraint forall(i in 1..T)(
    if action_list[i] = run then current_mana[i] = current_mana[i-1]
    elseif action_list[i] = flash then current_mana[i] = current_mana[i-1] - 10
    else current_mana[i] = current_mana[i-1] + 4
    endif
);
constraint forall(i in 1..T)(
    if action_list[i] = run then current_dis[i] = current_dis[i-1] + 17
    elseif action_list[i] = flash then current_dis[i] = current_dis[i-1] + 60
    else current_dis[i] = current_dis[i-1]
    endif
);
constraint max_dis = current_dis[T];
var int: score;
constraint if max_dis >= S then current_dis[min_time] >= S /\ current_dis[min_time-1] < S else min_time = T endif;
constraint score = if max_dis >= S then 300000 - min_time else max_dis endif;
solve::int_search(array1d(action_list), input_order, indomain, complete)
maximize score;
output[if fix(max_dis) >= S then "Yes\n\(min_time)" else "No\n\(max_dis)" endif];
