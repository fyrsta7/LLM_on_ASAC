int: N;
array[1..N] of int: H;
int: X0;
int: M;
array[1..M] of int: S;
array[1..M] of int: X;
function var int: d(var int: i, var int: j) =
    abs(H[i] - H[j]);
predicate near(var int: d1, var int: d2, var int: H1, var int: H2) =
    d1 < d2 \/ (d1 == d2 /\ H1 < H2);
function var int: plan_B(var int: current_city) =
let{
    var 1..N: nearest;
    constraint if current_city < N then nearest > current_city else nearest = N+1 endif;
    constraint forall(i in current_city+1..N where i != nearest)(near(d(current_city, nearest), d(current_city, i), H[nearest], H[i]));
} in nearest;
function var int: plan_A(var int: current_city) =
let{
    var 1..N: second_near;
    var 1..N: nearest;
    constraint if current_city < N-1 then second_near > current_city /\ nearest > current_city /\ second_near != nearest else second_near = N+1 /\ nearest = N endif;
    constraint forall(i in current_city+1..N where i != nearest)(near(d(current_city, nearest), d(current_city, i), H[nearest], H[i]));
    constraint forall(i in current_city+1..N where (i != nearest /\ i != second_near))(near(d(current_city, second_near), d(current_city, i), H[second_near], H[i]));
} in second_near;
function array[1..2] of var int: travel(var int: start_city, var int: limit) =
let{
    array[0..N] of var 1..N+1: route;
    var 0..N-1: days;
    constraint route[0] = start_city;
    constraint forall(i in 1..days)(route[i] < N+1);
    constraint forall(i in 1..days)(if i mod 2 == 1 then route[i] = plan_A(route[i-1]) else route[i] = plan_B(route[i-1]) endif);
    constraint sum(i in 1..days)(d(route[i], route[i-1])) <= limit;
    array[1..2] of var int: total_distance;
    constraint total_distance[1] = sum(i in 1..days where i mod 2 == 1)(d(route[i], route[i-1]));
    constraint total_distance[2] = sum(i in 1..days where i mod 2 == 0)(d(route[i], route[i-1]));
} in total_distance;
array[1..M, 1..2] of var int: ans;
constraint forall(i in 1..M)(ans[i, 1..2] = travel(S[i], X[i]));
solve maximize sum(i in 1..M, j in 1..2)(ans[i, j]);
output["\(ans[i, 1]) , \(ans[i, 2])\n" | i in 1..N];
