int: n;
int: m;
array[1..n] of int: w;
array[1..n] of var 1..m: choice;
array[1..n] of var int: start;
constraint forall(i in 1..m)(start[i] = 0 /\ choice[i] = i);
constraint forall(i in m+1..n)(
let{
array[1..m] of var 1..i-1: latest;
constraint forall(j in 1..m)(forall(k in 1..i-1 where choice[k] = j)(latest[j] >= k)
/\ exists(k in 1..i-1 where choice[k] = j)(latest[j] = k));
} in forall(j in 1..m)
(start[i] = min([start[latest[l]] + w[latest[l]] | l in 1..m]) /\
start[latest[choice[i]]] + w[latest[choice[i]]] <= start[latest[j]] + w[latest[j]] )
);
solve satisfy;
output[show(max([start[i] + w[i] | i in 1..n]))];
