array[1..7,1..2] of int: time;
array[1..7] of var bool: unhappy;
constraint forall(i in 1..7)(unhappy[i]=(time[i,1]+time[i,2]>8));
var int: longest=arg_max(i in 1..7)(time[i,1]+time[i,2]);
solve satisfy;
output[if fix(count(i in 1..7)(unhappy[i]==true))==0 then "0" else "\(longest)" endif];
