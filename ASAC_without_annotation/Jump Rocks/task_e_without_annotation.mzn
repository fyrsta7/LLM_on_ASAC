int: L;
int: N;
int: M;
array[1..N] of int: D;
array[1..N] of var bool: moved;
var int: predist = min(i in 1..N-1 where moved[i] == false, j in i+1..N where moved[j] == false)(abs(D[i] - D[j]));
var int: predist2 = min(i in 1..N where moved[i] == false)(min(D[i], L - D[i]));
var int: mindist = min(predist, predist2);
constraint sum(moved) <= M;
solve maximize mindist;
output["mindist=\(mindist)"]
