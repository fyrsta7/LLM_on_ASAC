include "alldifferent.mzn";
int: n;
int: s;
array[1..n-1, 1..3] of int: edge;
function array[0..n-1] of var 0..n-1: find_route(var int: a, var int: b) =
let {
    array[0..n-1] of var 0..n-1: tmp;
    var 0..n-1: len;
    array[1..n] of var 1..n: route;
    constraint all_different(tmp[1..n-1]);
    constraint route[1] = a;
    constraint route[len+1] = b;
    constraint forall(i in 1..len)((edge[tmp[i], 1] = route[i] /\ edge[tmp[i], 2] = route[i+1]) \/ (edge[tmp[i], 1] = route[i+1] /\ edge[tmp[i], 2] = route[i]));
    constraint tmp[0] = len;
} in tmp;
function var int: get_distance(array[0..n-1] of var 0..n-1: roads) =
if roads[0] == 0 then 0 else sum(i in 1..roads[0])(edge[roads[i], 3]) endif;
function var int: get_point_distance(var int: p, array[0..n-1] of var 0..n-1: roads) =
let {
    var 0..n-1: len;
    constraint len = roads[0];
    array[1..n, 1..2] of var int: p_distance;
    constraint forall(i in 1..len, j in 1..2)(p_distance[i, j] = get_distance(find_route(edge[roads[i], j], p)));
    var int: tmp;
    constraint tmp = min(i in 1..len, j in 1..2)(p_distance[i, j]);
} in tmp;
function var int: find_diameter() =
max(i, j in 1..n where i != j)(get_distance(find_route(i, j)));
var int: diameter;
constraint diameter = find_diameter();
predicate if_diameter(array[0..n-1] of var 0..n-1: roads) =
get_distance(roads) = diameter;
function var int: ECC(array[0..n-1] of var 0..n-1: roads) =
let {
    array[1..n] of var int: ecc_distance;
    constraint forall(i in 1..n)(ecc_distance[i] = get_point_distance(i, roads))
} in max(ecc_distance);
var 1..n: begin;
var 1..n: end;
array[0..n-1] of var 0..n-1: dia_roads = find_route(begin, end);
constraint if_diameter(dia_roads);
var int: length = dia_roads[0];
var 1..n-1: core_begin;
var 1..n-1: core_end;
constraint core_begin <= core_end /\ core_end <= length;
array[0..n-1] of var 0..n-1: core;
constraint core[0] = core_end - core_begin;
constraint forall(i in 1..core_end-core_begin)(core[i] = dia_roads[i+core_begin-1]);
constraint get_distance(core) <= s;
var int: ans = ECC(core);
solve minimize ans;
output [show(ans)];
