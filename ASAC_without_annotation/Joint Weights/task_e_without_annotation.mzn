int: n;
array[1..n-1,1..2] of int: roads;
array[1..n] of int: W;
function var int: distance(var int: node1, var int: node2) =
let{
  array[0..n] of var 1..n: route;
  var 1..n-1: len;
  constraint route[0] = node1;
  constraint route[len] = node2;
  constraint forall(i in 0..len-1)(exists(j in 1..n-1)((route[i] = roads[j,1] /\ route[i+1] = roads[j,2]) \/ (route[i+1] = roads[j,1] /\ route[i] = roads[j,2])));
} in len;
array[1..n,1..n] of var int: matrix;
constraint forall(i,j in 1..n where i != j)(matrix[i,j] = distance(i,j));
var int: max_weight = max(i,j in 1..n where matrix[i,j] == 2)(W[i] * W[j]);
var int: sum_weight = sum(i,j in 1..n where matrix[i,j] == 2)(W[i] * W[j]) mod 10007;
solve satisfy;
output["\(max_weight) \(sum_weight)"];
