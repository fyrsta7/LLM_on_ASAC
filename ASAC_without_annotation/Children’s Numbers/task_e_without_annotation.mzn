int: n;
int: p;
array [1 .. n] of int: a;
array [1 .. n] of var int: character;
array [1 .. n] of var int: score;
var int: ans;
constraint forall(i in 1..n)(
  character[i] = max(j, k in 1..i where j <= k)(sum(l in j..k)(a[l]))
);
constraint score[1] = character[1];
constraint forall(i in 2 .. n)(
  score[i] = max(j in 1..i-1)(character[j] + score[j])
);
constraint ans = (max(i in 1 .. n)(score[i])) mod p;
solve satisfy;
output[show(ans)];
