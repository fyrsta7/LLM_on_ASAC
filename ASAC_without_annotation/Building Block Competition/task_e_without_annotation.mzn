int: n;
array[1..n] of int: h;
int: max_action = n * max(h);
predicate build(array[1..n] of var int: before, array[1..n] of var int: after, var int: left, var int: right)
= forall(i in 1..left-1)(before[i] = after[i]) /\ forall(i in left..right)(before[i] + 1 = after[i]) /\
forall(i in right+1..n)(before[i] = after[i]);
var 0..max_action: actions;
array[0..max_action,1..2] of var 1..n: left_right;
array[0..max_action,1..n] of var int: state;
constraint forall(i in 1..n)(state[0,i] = 0);
constraint forall(i in 1..actions)(build(state[i-1,1..n],state[i,1..n],left_right[i,1],left_right[i,2]));
constraint forall(i in 1..n)(state[actions,i] = h[i]);
solve minimize actions;
output[show(actions)];
