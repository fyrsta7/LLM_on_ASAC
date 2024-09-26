int: n;
int: m;
int: k;
int: x;
function var int: move(var int: x) =
    (x + m) mod n;
int: rounds = pow(10, k);
array[0..rounds] of var int: state;
constraint state[0] = x;
constraint forall(i in 1..rounds)(state[i] = move(state[i-1]));
solve satisfy;
output [show(state[rounds])];
