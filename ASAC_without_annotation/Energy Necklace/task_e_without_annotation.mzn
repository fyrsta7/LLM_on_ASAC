int: N;
array[1..N] of int: beads;
function var int: precede(var int: j, var int: len) =
    if j > 1 then j - 1 else len endif;
function var int: follow(var int: j, var int: len) =
    if j < len then j + 1 else 1 endif;
array[1..N,1..N] of var int: steps;
array[1..N] of var 1..N: choose;
constraint forall(i in 2..N)(choose[i] <= N - i + 1);
constraint steps[1,1..N] = beads;
constraint forall(i in 1..N-1)(forall(j in 1..choose[i]-1)(steps[i+1,j] = steps[i,j]));
constraint forall(i in 1..N-1)(forall(j in choose[i]+1..N-i+1)(steps[i+1,j-1] = steps[i,j]));
var int: ans;
constraint ans = sum([steps[i,choose[i]] * steps[i,precede(choose[i],N-i+1)] * steps[i,follow(choose[i],N-i+1)] | i in 1..N-1]);
solve maximize ans;
output[show(ans)];
