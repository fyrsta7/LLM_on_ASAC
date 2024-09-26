int: n;
array[1..n] of int: number;
set of int: num_set = array2set(number);
int: m = card(num_set);
array[1..m, 1..2] of var int: count_num;
constraint forall(i in 1..m)(count_num[i, 1] in num_set);
constraint forall(i in 1..m)(count_num[i, 2] = count(number, count_num[i, 1]));
constraint forall(i in 1..m-1)(count_num[i, 1] < count_num[i+1, 1]);
solve satisfy;
output[
  "\(count_num[i, 1]) \(count_num[i, 2])\n" | i in 1..m];
