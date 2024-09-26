int: T;
int: K;
array[1..T] of int: n;
array[1..T] of int: m;
function var int: factorial(var int: x) =
  if x == 0 then 1 else
    product([i | i in 1..x]) endif;
array[1..T] of var int: ans;
constraint forall(t in 1..T)(
  ans[t] = count(i in 1..n[t], j in 1..m[t] where j <= i)
  (factorial(i) div ((factorial(j) * factorial(i - j))) mod K = 0)
);
solve satisfy;
output[show(ans)];
