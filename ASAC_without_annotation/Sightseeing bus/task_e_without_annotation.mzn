int: n;
int: m;
int: k;
array[1..n-1] of int: D;
array[1..m] of int: T;
array[1..m] of int: A;
array[1..m] of int: B;
array[1..n] of var int: arrive_time;
array[1..n] of var int: depart_time;
array[1..n-1] of var int: save_time;
constraint forall(i in 1..n)(arrive_time[i] >= 0);
constraint forall(i in 1..n)(depart_time[i] > 0);
constraint arrive_time[1] = 0;
constraint forall(i in 1..m)(depart_time[A[i]] >= T[i]);
constraint forall(i in 1..n-1)(arrive_time[i+1] - depart_time[i] > 0);
constraint forall(i in 1..n)(depart_time[i] - arrive_time[i] >= 0);
constraint forall(i in 1..n-1)(arrive_time[i+1] - depart_time[i] + save_time[i] >= D[i]);
constraint forall(i in 1..n-1)(save_time[i] >= 0);
constraint k >= sum(i in 1..n-1)(save_time[i]);
var int: travel_time;
constraint travel_time = sum(i in 1..m)(arrive_time[B[i]] - T[i]);
solve minimize(travel_time);
output[show(travel_time)];
