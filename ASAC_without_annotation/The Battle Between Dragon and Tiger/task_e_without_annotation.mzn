int: n;
array[1..n] of int: num;
int: m;
int: p1;
int: s1;
int: s2;
var 1..n: p2;
var int: left;
var int: right;
constraint left = sum(i in 1..(m-1))(num[i] * (m - i)) +
                      if p1 < m then s1 * (m - p1) else 0 endif +
                      if p2 < m then s2 * (m - p2) else 0 endif;
constraint right = sum(i in (m+1)..n)(num[i] * (i - m)) +
                      if p1 > m then s1 * (p1 - m) else 0 endif +
                      if p2 > m then s2 * (p2 - m) else 0 endif;
solve minimize abs(left - right);
output ["p2=" ++ show(p2)];
