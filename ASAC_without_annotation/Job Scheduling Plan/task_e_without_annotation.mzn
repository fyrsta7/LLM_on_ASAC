int: m;
int: n;
array[1..m*n] of int: order;
array[1..n,1..m] of int: machine;
array[1..n,1..m] of int: time;
array[1..m*n] of var int: begin_time;
array[1..m*n] of var int: end_time;
array[1..m*n] of var int: process;
predicate no_overlap(var int: begin1, var int: end1, var int: begin2, var int: end2) =
  begin1 >= end2 \/ begin2 >= end1;
constraint forall(i in 1..m*n)(process[i] = count(j in 1..i)(order[j] = order[i]));
constraint forall(i in 1..m*n)(end_time[i] - begin_time[i] = time[order[i], process[i]]);
constraint forall(i in 1..m*n)(
  let{
    var int: max_t = if process[i] == 1 then 0
    else max([end_time[j] | j in 1..i-1 where order[j] == order[i]])
  } in
  if forall(j in 1..i-1 where machine[order[j], process[j]] == machine[order[i], process[i]])
    (no_overlap(begin_time[j], end_time[j], max_t, max_t + time[order[i], process[i]]))
  then begin_time[i] = max_t
  else
    begin_time[i] = min([end_time[j] | j in 1..i-1 where
      machine[order[j], process[j]] == machine[order[i], process[i]] /\
      end_time[j] >= max_t /\
      forall(k in 1..i-1 where machine[order[k], process[k]] == machine[order[i], process[i]])
        (no_overlap(end_time[j], end_time[j] + time[order[i], process[i]], begin_time[k], end_time[k]))
    ])
  endif
);
var int: ans;
constraint ans = max(i in 1..m*n)(end_time[i]);
solve satisfy;
output[show(ans)];
