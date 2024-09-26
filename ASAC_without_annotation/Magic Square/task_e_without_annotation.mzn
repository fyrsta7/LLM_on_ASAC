include "all_different.mzn";
int: N;
array[1..N, 1..N] of var 1..N*N: square;
constraint alldifferent(square);
constraint square[1, N div 2 + 1] = 1;
constraint forall(i in 2..N*N)(
  let{
    var 1..N: x;
    var 1..N: y;
    constraint square[x, y] = i-1;
  } in
  (
    (x=1 /\ y!=N /\ square[N, y+1]=i) \/
    (x!=1 /\ y=N /\ square[x-1, 1]=i) \/
    (x=1 /\ y=N /\ square[x+1, y]=i) \/
    (x!=1 /\ y!=N /\ (square[x-1, y+1]=i \/ (square[x-1, y+1]<i /\ square[x+1, y]=i) ))
  )
);
solve satisfy;
output["\(square[i, j])" ++ if j==N then "\n" else " " endif | i in 1..N, j in 1..N];
