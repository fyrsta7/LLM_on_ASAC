int: n;
var 2..n-1: m;
constraint n mod m = 0;
solve maximize m;
output[show(m)];
