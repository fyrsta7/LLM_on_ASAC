int: N;
array[1..pow(2,N)] of 0..1: number;
int: node_num = pow(2,N+1)-1;
array[1..node_num] of var int: tree;
predicate build_tree(int: left, int: right, var int: idx) =
    if left == right then
        (if number[left] == 1 then tree[idx] = 0
        else tree[idx] = 1 endif)
    else
        ((if count(i in left..right)(number[i] == 0) == 0 then tree[idx] = 0
        elseif count(i in left..right)(number[i] == 1) == 0 then tree[idx] = 1
        else tree[idx] = 2 endif)
        /\ build_tree(left, (left+right-1) div 2, idx+1)
        /\ build_tree((left+right-1) div 2 + 1, right, idx+right-left+1)) endif;
array[1..node_num] of var int: last;
predicate last_order(int: left, int: right, int: last_left, int: last_right) =
    if left == right then last[last_left] = tree[left]
    else
        (last[last_right] = tree[left]
        /\ last_order(left+1, (right+left) div 2, last_left, (last_left+last_right) div 2-1)
        /\ last_order((right+left) div 2 + 1, right, (last_left+last_right) div 2, last_right-1)) endif;
constraint build_tree(1, pow(2,N), 1);
constraint last_order(1, node_num, 1, node_num);
solve satisfy;
output[if fix(last[i]) == 0 then "I" elseif fix(last[i]) == 1 then "B" else "F" endif | i in 1..node_num];
