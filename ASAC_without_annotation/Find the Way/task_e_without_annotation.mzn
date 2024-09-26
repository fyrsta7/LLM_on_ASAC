include "all_different.mzn";
int: n;
int: m;
array[1..m,1..2] of int: road;
int: s;
int: t;
array[1..n,1..n] of var bool: available;
constraint forall(i in 1..n)(available[i,i] = true);
constraint forall(i in 1..m)(available[road[i,1], road[i,2]] = true);
constraint forall(i,j in 1..n where i != j)(if available[i,j] then exists(p in 1..m)(road[p,1] = i /\ available[road[p,2], j]) endif);
constraint forall(i in 1..n, j in 1..n, k in 1..n)(if available[i,j] /\ available[j,k] then available[i,k] = true endif);
var bool: cond1 = available[s,t];
array[1..m] of var 1..m: route;
var 1..m: len;
constraint if cond1 then road[route[1],1] = s /\ road[route[len],2] = t else true endif;
constraint forall(i in 1..len-1)(road[route[i],2] = road[route[i+1],1]);
var bool: cond2;
constraint cond2 = forall(i in 1..len)
(forall(j in 1..m where road[j,1] = road[route[i],1] \/ road[j,1] = road[route[i],2])
(available[road[j,2], t] \/ available[t, road[j,2]]));
var int: score = if cond2/\cond1 then len-m else len endif;
solve minimize score;
output[if fix(cond1)/\ fix(cond2) then "\(len)" else "-1" endif];
