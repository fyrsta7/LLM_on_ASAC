int: n;
int: m;
array[1..n, 1..m] of int: number;
enum choice = {head, tail};
array[1..n, 1..m] of var choice: take_number;
function var int: cal_score(array[1..m] of var int: row, array[1..m] of var choice: actions) =
  sum(i in 1..m)(pow(2,i) * (if actions[i] == head then row[count(j in 1..i)(actions[j] == head)] else row[m + 1 - count(j in 1..i)(actions[j] == tail)] endif));
var int: total_score;
constraint total_score = sum(i in 1..n)(cal_score(number[i, 1..m], take_number[i, 1..m]));
solve maximize total_score;
output[show(total_score)];
