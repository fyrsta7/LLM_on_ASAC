int: k;
int: N;
int: l = ceil(log(2, N));
array[1..l] of var int: idx;
var int: ans;
predicate int2bin(array[1..l] of var int: idx, var int: N, var int: pointer) =
if N = 0 then true else
idx[pointer] = N mod 2 /\ int2bin(idx, N div 2, pointer + 1)
endif;
constraint int2bin(idx, N, 1);
constraint ans = sum([pow(k, i - 1) | i in 1..l where idx[i] = 1]);
solve satisfy;
output[show(ans)];
