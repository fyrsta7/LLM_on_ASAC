int: a;
int: b;
var int: x;
constraint x > 0;
constraint (a * x) mod b = 1;
solve minimize x;
output[show(x)];
