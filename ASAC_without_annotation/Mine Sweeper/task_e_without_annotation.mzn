int: n;
int: m;
array[int, int] of int: a;
array[1..n, 1..m] of var int: b;
function int: getval(int: x, int: y) = if (x < 1 \/ x > n \/ y < 1 \/ y > m) then 0 else a[x, y] endif;
constraint forall(i in 1..n) (forall(j in 1..m) (0 <= a[i, j] /\ a[i, j] <= 1));
constraint forall(i in 1..n) (forall(j in 1..m) (if (a[i, j] == 1) then (b[i, j] == -1) else (b[i, j] = getval(i - 1, j - 1) + getval(i - 1, j) + getval(i - 1, j + 1) + getval(i, j - 1) + getval(i, j + 1) + getval(i + 1, j - 1) + getval(i + 1, j) + getval(i + 1, j + 1)) endif));
solve satisfy;
output [(if fix(b[i, j]) != -1 then show(b[i, j]) else "*" endif) ++ (if j == m then "\n" else "" endif)| i in 1..n, j in 1..m];
