include "alldifferent.mzn";
int: n;
array[1..n, 1..3] of int: grades;
array[1..n] of var 1..n: rank;
predicate prec(array[1..n] of var 1..n: rank, int: i, int: j) =
grades[rank[i], 1] + grades[rank[i], 2] + grades[rank[i], 3] > grades[rank[j], 1] + grades[rank[j], 2] + grades[rank[j], 3]
\/ (grades[rank[i], 1] + grades[rank[i], 2] + grades[rank[i], 3] = grades[rank[j], 1] + grades[rank[j], 2] + grades[rank[j], 3] /\ grades[rank[i], 1] > grades[rank[j], 1])
\/ (grades[rank[i], 1] + grades[rank[i], 2] + grades[rank[i], 3] = grades[rank[j], 1] + grades[rank[j], 2] + grades[rank[j], 3] /\ grades[rank[i], 1] = grades[rank[j], 1] /\ rank[i] < rank[j]);
constraint alldifferent(rank);
constraint forall(i in 1..n-1)(rank[i] < rank[i+1]);
constraint forall(i, j in 1..n where i < j)(prec(rank, i, j));
solve satisfy;
output["\(rank[i]) \(grades[rank[i], 1] + grades[rank[i], 2] + grades[rank[i], 3])\n" | i in 1..5];
