array[1..12] of int: budget;
array[0..12] of var int: left;
var int: total;
constraint left[0] = 0;
constraint forall(i in 1..12)(left[i] = (300 + left[i-1] - budget[i]) mod 100);
constraint total = sum([((300 + left[i-1] - budget[i]) div 100) * 100 | i in 1..12]) * 1.2;
solve satisfy;
output[
if min(fix(left)) < 0 then "-\(min([i | i in 0..12 where fix(left[i]) < 0]))"
else "\(left[12] + total)"
endif
];
