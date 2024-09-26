int: n;
int: m;
int: S;
array[1..n,1..2] of int: ores;
array[1..m,1..2] of int: intervals;
var int: Y;
var int: W;
constraint Y=sum(i in 1..m)
(sum(j in 1..n where ores[j,1]>=W /\ j>=intervals[i,1] /\ j<=intervals[i,2])(1)*sum(j in 1..n where ores[j,1]>=W /\ j>=intervals[i,1] /\ j<=intervals[i,2])(ores[j,2]));
solve minimize (abs(S-Y));
output[show(abs(S-Y))];
