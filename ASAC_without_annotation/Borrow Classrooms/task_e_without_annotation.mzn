int: n;
int: m;
array[1..n] of int: r;
array[1..m] of int: d;
array[1..m] of int: s;
array[1..m] of int: t;
array[0..m,1..n] of var int: state;
constraint state[0,1..n] = r;
var 0..m: num;
constraint forall(i in 1..num)(forall(j in s[i]..t[i])(state[i,j] = state[i-1,j] - d[i]));
constraint forall(i in 1..num)(forall(j in 1..n where not(j >= s[i] /\ j <= t[i]))(state[i,j] = state[i-1,j]));
constraint forall(i in 1..num, j in 1..n)(state[i,j] >= 0);
solve maximize num;
output[if fix(num) == m then "0"
else "-1\n\(fix(num+1))" endif
];
