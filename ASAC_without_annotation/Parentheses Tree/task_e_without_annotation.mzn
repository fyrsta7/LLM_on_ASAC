int: n;
array[1..n] of string: bracket;
array[1..n-1] of int: father;
array[1..n] of int: b_num = [if bracket[i] == "(" then 0 else 1 endif | i in 1..n];
predicate valid(array[int] of var 0..1: x) =
  count(i in index_set(x))(x[i] == 1) = count(i in index_set(x))(x[i] == 0)
  /\ forall(i in index_set(x) where x[i] == 0)
  (exists(j in index_set(x) where j > i /\ x[j] == 1)(sum(k in i+1..j-1 where x[k] = 0)(1) = sum(k in i+1..j-1 where x[k] = 1)(1)));
array[1..n,1..n] of var 1..n: route;
array[1..n] of var 1..n: length;
constraint forall(i in 1..n)(route[i,1] = 1 /\ route[i,length[i]] = i);
constraint forall(i in 1..n)(forall(j in 1..length[i]-1)(father[route[i,j+1]-1] = route[i,j]));
array[1..n] of var int: num;
constraint forall(i in 1..n)(num[i] = sum(a,b in 1..length[i] where a <= b /\ valid([b_num[route[i,j]] | j in a..b]))(1));
function var int: bitwise_xor(var int: a, var int: b) =
  if a == 0 then b elseif b == 0 then a
  else (((a mod 2) + (b mod 2))) mod 2 + 2 * bitwise_xor(a div 2, b div 2) endif;
array[1..n] of var int: ans;
constraint ans[1] = num[1] * 1;
constraint forall(i in 2..n)(ans[i] = bitwise_xor(ans[i-1], num[i] * i));
solve satisfy;
output[show(ans[n])];
