int: n;
array[1..n] of int: time;
array[1..n] of int: passenger;
array[1..n] of set of int: country;
set of int: all_country = array_union(country);
array[1..n] of var set of all_country: union_country;
constraint forall(i in 1..n)
(
  forall(j in 1..i)
  (
    if time[i] - time[j] < 86400 then union_country[i] superset country[j] endif
  )
);
solve minimize sum(i in union_country)(card(i));
output[show(card(union_country[i])) ++ " " | i in 1..n];
