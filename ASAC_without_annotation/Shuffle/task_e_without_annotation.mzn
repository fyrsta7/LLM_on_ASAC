int: n;
int: m;
array[1..n] of int: T;
int: upper_bound = max(T) + m;
int: max_times = min(max(T) div m + 1, n);
var 1..max_times: times;
array[1..max_times] of var 0..upper_bound: departure;
var int: object;
constraint forall(i in 1..times-1)(departure[i+1] - departure[i] >= m);
constraint object = sum(i in 1..n)(min(j in 1..times where departure[j] >= T[i])(departure[j] - T[i]));
solve::int_search(array1d(departure), input_order, indomain, complete)
minimize object;
output[show(object)];
