int: N;
int: M;
array[1..N,1..M] of int: height;
enum water = {store, trans, empty};
array[1..N,1..M] of var water: build;
predicate water_flow(var 1..N: x, var 1..M: y) =
  (x > 1 /\ height[x-1,y] > height[x,y] /\ build[x-1,y] != empty)
  \/ (x < N /\ height[x+1,y] > height[x,y] /\ build[x+1,y] != empty)
  \/ (y > 1 /\ height[x,y-1] > height[x,y] /\ build[x,y-1] != empty)
  \/ (y < M /\ height[x,y+1] > height[x,y] /\ build[x,y+1] != empty);
constraint forall(i in 1..N, j in 1..M)
  (if build[i,j] = store then i = 1
  elseif build[i,j] = trans then water_flow(i,j)
  else true endif);
var int: desert_water;
constraint desert_water = count(j in 1..M)(build[N,j] = trans \/ build[N,j] = store);
var int: store_num;
constraint store_num = count(j in 1..M)(build[1,j] = store);
solve maximize desert_water * M - store_num;
output[if fix(desert_water) == M then "1\n" else "0\n" endif];
output[if fix(desert_water) == M then "\(fix(store_num))" else "\(fix(M - desert_water))" endif];
