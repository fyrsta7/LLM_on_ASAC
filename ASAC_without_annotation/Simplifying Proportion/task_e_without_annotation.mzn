int: A;
int: B;
int: L;
predicate mutuality(var int: x, var int: y) =
let{
    var int: m = min(x, y);
} in forall(i in 2..m)(not(x mod i == 0 /\ y mod i == 0));
var 1..L: A_s;
var 1..L: B_s;
constraint A_s/B_s >= A/B;
constraint mutuality(A_s, B_s);
solve minimize A_s * B - A * B_s;
output["\(A_s) \(B_s)"];
