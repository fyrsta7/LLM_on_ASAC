int: n;
int: m;
array[1..n, 1..m] of int: a;
int: max_num = pow(2, n + m + 1);
array[1..max_num, 1..n, 1..2] of var int: plans;
var 0..max_num: num;
constraint forall(i in 1..num, j in 1..n)(plans[i, j, 1] in 1..n /\ plans[i, j, 2] in 1..m);
array[1..max_num] of var 1..n: dish_num;
constraint forall(i, j in 1..num where i != j)(dish_num[i] != dish_num[j] \/ not(forall(k, l in 1..dish_num[i] where plans[i, k, 1] = plans[j, l, 1])(plans[i, k, 2] = plans[j, l, 2])));
constraint forall(i in 1..num)(forall(j, k in 1..dish_num[i] where j != k)(plans[i, j, 1] != plans[i, k, 1]));
constraint forall(i in 1..num)(forall(j in 1..dish_num[i])(a[plans[i, j, 1], plans[i, j, 2]] > 0));
constraint forall(i in 1..num)(forall(j in 1..m)(sum(k in 1..dish_num[i] where plans[i, k, 2] = j)(1) <= dish_num[i] div 2));
array[1..max_num] of var int: methods;
constraint forall(i in 1..num)(methods[i] = product(j in 1..dish_num[i])(a[plans[i, j, 1], plans[i, j, 2]]));
var int: s;
constraint s = sum(i in 1..num)(methods[i]) mod 998244353;
solve::int_search(array1d(plans), input_order, indomain, complete)
maximize num;
output [show(s)];
