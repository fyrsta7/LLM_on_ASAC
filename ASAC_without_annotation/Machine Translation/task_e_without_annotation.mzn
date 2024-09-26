int: M;
int: N;
array[1..N] of int: words;
enum op = {hit, seek};
array[0..N, 1..M] of var int: memory;
array[1..N] of var op: action;
constraint forall(i in 1..M)(memory[0, i] = -1);
constraint forall(i in 1..N)(if count(j in 1..M)(words[i] = memory[i-1, j]) > 0 then action[i] = hit /\
                            memory[i, 1..M] = memory[i-1, 1..M]
                            else action[i] = seek /\
                            forall(k in 1..M-1)(memory[i, k] = memory[i-1, k+1]) /\
                            memory[i, M] = words[i] endif);
solve satisfy;
output["\(count(i in 1..N)(fix(action)[i] = seek))"];
