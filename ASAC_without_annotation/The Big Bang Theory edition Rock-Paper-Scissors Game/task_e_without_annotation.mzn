int: N;
int: NA;
int: NB;
array[1..NA] of int: loopA;
array[1..NB] of int: loopB;
enum match = {win, lose, draw};
array[1..5, 1..5] of var match: table = [|draw, lose, win, win, lose|
                                          win, draw, lose, win, lose|
                                          lose, win, draw, lose, win|
                                          lose, lose, win, draw, win|
                                          win, win, lose, lose, draw|];
array[0..N-1] of var int: A;
array[0..N-1] of var int: B;
var int: scoreA;
var int: scoreB;
constraint forall(i in 0..N-1)(A[i] = loopA[(i mod NA) + 1] /\ B[i] = loopB[(i mod NB) + 1]);
constraint scoreA = sum(i in 0..N-1)(if table[A[i] + 1, B[i] + 1] == win then 1 else 0 endif);
constraint scoreB = sum(i in 0..N-1)(if table[B[i] + 1, A[i] + 1] == win then 1 else 0 endif);
solve satisfy;
output["\(scoreA) \(scoreB)"];
