int: n;
array[1..n+1] of int: coefficient;
output[if(coefficient[i] < 0) then "-" else (if(coefficient[i] == 0 \/ i == 1) then "" else "+" endif) endif
 ++ if(abs(coefficient[i]) == 1 \/ coefficient[i] == 0 ) then "" else show(abs(coefficient[i])) endif
 ++ if(coefficient[i] == 0) then "" else ("x" ++ if(n-i+1 == 1) then "" else "^" ++ show(n-i+1) endif) endif
|i in 1..n];
solve satisfy;
output[if(coefficient[n+1] == 0) then "" else (if(coefficient[n+1] > 0) then "+" else "-" endif) ++ show(abs(coefficient[n+1])) endif];
