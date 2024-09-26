int: L;
int: M;
array[1..M, {1, 2}] of int: spot;
array[0..L] of var bool: index;
var int: cnt;
cnt = sum([index[i] | i in 0..L]);
constraint forall(i in 0..L)((index[i] = 0)\/(forall(j in 1..M)((i < spot[j, 1]) \/ (i > spot[j, 2]))));
solve maximize cnt;
output[show(cnt)];
