int: n;
int: x;
function var int: appear_times(var int: num, var int: a) =
if num < 10 then (num == a)
else appear_times(num div 10, a) + ((num mod 10) == a)
endif;
var int: ans;
constraint ans = sum(i in 1..n)(appear_times(i, x));
solve satisfy;
output[show(ans)];
