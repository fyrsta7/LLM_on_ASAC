int: n;
array [1..n] of int: data;
set of int: ans = { i | i, j, k in data where i = j + k /\ j != k };
solve satisfy;
output[show(card(ans))];
