int: n;
array[1..3,1..2] of int: pencil;
int: max_single = max(i in 1..3)(ceil(pencil[i,2] / pencil[i,1]));
var 0..max_single * n: cost;
constraint
  ((cost div pencil[1, 2]) * pencil[1, 1] >= n)
  \/
  ((cost div pencil[2, 2]) * pencil[2, 1] >= n)
  \/
  ((cost div pencil[3, 2]) * pencil[3, 1] >= n);
solve minimize cost;
output["cost=" ++ show(cost)];
