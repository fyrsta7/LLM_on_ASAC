int: n;
array[1..n] of int: h;
var 1..n: m;
array[1..n] of var int: g;
array[1..n] of var 1..n: chosen;
constraint forall(i in 1..m-1)(chosen[i] < chosen[i+1]);
constraint forall(i in 1..m)(g[i] = h[chosen[i]]);
constraint forall(i in 1..m where i mod 2 == 0)(if i-1 > 0 then g[i] > g[i-1] else true endif
/\ if i+1 <= m then g[i] > g[i+1] else true endif) \/
forall(i in 1..m where i mod 2 == 0)(if i-1 > 0 then g[i] < g[i-1] else true endif
/\ if i+1 <= m then g[i] < g[i+1] else true endif);
solve maximize m;
output[show(m)];
