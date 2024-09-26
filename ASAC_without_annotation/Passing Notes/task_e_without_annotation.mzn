int: m;
int: n;
array[1..m, 1..n] of int: students;
array[1..m+n, 1..2] of var int: first;
array[1..m+n, 1..2] of var int: second;
int: L = m + n - 1;
constraint forall(i in 1..L)(first[i,1] >= 1 /\ first[i,2] <= m);
constraint forall(i in 1..L)(second[i,1] >= 1 /\ second[i,2] <= n);
constraint (first[1,1] = 1 /\ first[1,2] = 1) /\ (first[m+n,1] = m /\ first[m+n,2] = n);
constraint (second[1,1] = m /\ second[1,2] = n) /\ (second[m+n,1] = 1 /\ second[m+n,2] = 1);
predicate neighbor(array[1..2] of var int: a, array[1..2] of var int: b) =
  (b[1] = a[1] /\ b[2] = a[2] + 1) \/ (b[2] = a[2] /\ b[1] = a[1] + 1);
constraint forall(i in 1..L-1)(neighbor(first[i,1..2], first[i+1,1..2]));
constraint forall(i in 1..L-1)(neighbor(second[i+1,1..2], second[i,1..2]));
constraint forall(i, j in 2..L-1)(not(first[i,1] = second[j,1] /\ first[i,2] = second[j,2]));
var int: value;
constraint value = sum([students[first[i,1], first[i,2]] | i in 1..L]) + sum([students[second[i,1], second[i,2]] | i in 1..L]);
solve maximize value;
output[show(value)];
