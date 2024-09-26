int: n;
var int: total;
function int: give(int: day, int: cur) =
  if(day > cur) then give(day - cur, cur + 1) else cur endif;
constraint 1 <= n /\ n <= 100000;
constraint total == sum(i in 1..n) (give(i, 1));
solve satisfy;
output["\(total)"];
