int: n;
int: m;
array[1..n] of int: p;
array[1..n-1,1..2] of int: road;
array[1..m,1..4] of int: request;
array[1..m,1..n] of var 0..1: troop;
array[1..m] of var int: score;
constraint forall(i in 1..m)(
  if request[i,2] == 0 /\ request[i,4] == 0 /\ exists(j in 1..n-1)(
    (road[j,1] == request[i,1] /\ road[j,2] == request[i,3]) \/
    (road[j,2] == request[i,1] /\ road[j,1] == request[i,3])
  ) then
    score[i] = -1
  else
    score[i] >= 0
  endif
);
constraint forall(i in 1..m)(
  if score[i] != -1 then
    troop[i, request[i,1]] = request[i,2] /\ troop[i, request[i,3]] = request[i,4]
  endif
);
constraint forall(i in 1..m)(
  forall(j in 1..n-1)(
    not (troop[i, road[j,1]] == 0 /\ troop[i, road[j,2]] == 0)
  )
);
constraint forall(i in 1..m where score[i] != -1)(
  score[i] = sum(j in 1..n)(troop[i,j] * p[j])
);
solve minimize sum(score);
output[show(score)];
