array[1..10] of int: apple;
int: h;
var int: num;
constraint num = count([apple[i] <= h + 30 | i in 1..10]);
solve satisfy;
output [show(num)];
