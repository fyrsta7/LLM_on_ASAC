include "all_different.mzn";
int: n;
int: m;
array[1..n-1, 1..3] of int: road;
array[1..m, 1..2] of int: plans;
var 1..m: hole;
function var int: travel(var int: start, var int: end) =
let {
    array[1..n-1] of var 1..n-1: route;
    constraint alldifferent(route);
    var 1..n-1: len;
    constraint (road[route[1], 1] = start \/ road[route[1], 2] = start) /\ (road[route[len], 1] = end \/ road[route[len], 2] = end);
    constraint forall(i in 1..len-1) (road[route[i], 2] = road[route[i+1], 1] \/ road[route[i], 1] = road[route[i+1], 1] \/ road[route[i], 1] = road[route[i+1], 2] \/ road[route[i], 2] = road[route[i+1], 2]);
} in sum(i in 1..len)(if route[i] = hole then 0 else road[route[i], 3] endif);
array[1..m] of var int: time;
constraint forall(i in 1..m)(time[i] = travel(plans[i, 1], plans[i, 2]));
var int: max_time = max(time);
solve minimize max_time;
output[show(max_time)];
