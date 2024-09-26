int: n;
array[1..n] of string: name;
array[1..n] of int: score;
array[1..n] of int: review;
array[1..n] of string: if_leader;
array[1..n] of string: if_west;
array[1..n] of int: paper;
array[1..n] of var int: scholarship;
function var int: fellow(int: score, int: paper) =
    if score > 80 /\ paper >= 1 then 8000 else 0 endif;
function var int: mayfourth(int: score, int: review) =
    if score > 85 /\ review > 80 then 4000 else 0 endif;
function var int: grade(int: score) =
    if score > 90 then 2000 else 0 endif;
function var int: west(int: score, string: if_west) =
    if score > 85 /\ if_west = "Y" then 1000 else 0 endif;
function var int: contribution(int: review, string: if_leader) =
    if review > 80 /\ if_leader = "Y" then 850 else 0 endif;
constraint forall(i in 1..n)(scholarship[i] =
    fellow(score[i], paper[i]) + mayfourth(score[i], review[i]) + grade(score[i]) + west(score[i], if_west[i]) + contribution(review[i], if_leader[i]));
solve satisfy;
output[
    "\(name[arg_max(fix(scholarship))])\n" ++
    "\(max(fix(scholarship)))\n" ++
    "\(sum(scholarship))"
];
