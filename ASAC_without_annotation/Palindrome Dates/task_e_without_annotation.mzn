int: s;
int: t;
var int: res;
predicate val_ymd(var int: y, var int: m, var int: d) =
  m >= 1 /\ m <= 12 /\ d >= 1 /\ (m in {1, 3, 5, 7, 8, 10, 12} -> d <= 31) /\ (m in {4, 6, 9, 11} -> d <= 30) /\
  (m = 2 -> d <= 29) /\ ((m = 2 /\ (y mod 4 != 0 \/ (y mod 400 != 0 /\ y mod 100 == 0))) -> d <= 28);
predicate val_pal(var int: w) =
  w mod 10 == w div 10000000 /\ w div 10 mod 10 == w div 1000000 mod 10 /\ w div 100 mod 10 = w div 100000 mod 10 /\ w div 1000 mod 10 == w div 10000 mod 10;
predicate val_date(var int: w) =
  val_ymd(w div 10000, w div 100 mod 100, w mod 100) /\ val_pal(w);
predicate val_num(var int: s, var int: t, var int: num) =
  if val_date(s) then
    (s = t /\ num = 1) \/ (s < t /\ val_num(s + 1, t, num - 1))
  else
    (s = t /\ num = 0) \/ (s < t /\ val_num(s + 1, t, num))
  endif;
constraint val_num(s, t, res);
solve satisfy;
output["res=" ++ show(res)];
