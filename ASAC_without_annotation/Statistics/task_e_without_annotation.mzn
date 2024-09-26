int: l;
int: r;
function var int: count_two(var int: x) =
    if x = 0 then 0 elseif (x mod 10 = 2) then (count_two(x div 10) + 1) else count_two(x div 10) endif;
var int: answer;
constraint answer = sum([count_two(i) | i in l..r]);
solve satisfy;
output [show(answer)];
