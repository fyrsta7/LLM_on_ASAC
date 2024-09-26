int: d;
int: n;
array[1..n, 1..2] of int: public_loc;
array[1..n] of int: public_num;
int: max_plans = 100;
predicate cover_spot(array[1..2] of var int: loc, array[1..2] of var int: center) =
    max(i in 1..2)(abs(loc[i] - center[i])) <= d;
array[1..max_plans, 1..2] of var 0..128: ans;
var 1..max_plans: plans;
constraint forall(i, j in 1..plans where i != j)(not(ans[i, 1] == ans[j, 1] /\ ans[i, 2] == ans[j, 2]));
var int: num;
constraint num > 0;
constraint forall(t in 1..plans)(num = sum(i in 1..n where cover_spot(public_loc[i, 1..2], ans[t, 1..2]))(public_num[i]));
var int: score;
constraint score = max_plans * num + plans;
solve maximize score;
output["\(plans) \(num)"];
