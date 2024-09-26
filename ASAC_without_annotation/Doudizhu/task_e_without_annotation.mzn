int: T;
int: n;
array[1..T,1..n,1..2] of int: cards;
predicate valid(var int: order, var set of 1..n: card_set) =
(card(card_set) = 2
/\ exists(i in card_set)(cards[order,i,1] == 0 /\ cards[order,i,2] == 1)
/\ exists(i in card_set)(cards[order,i,1] == 0 /\ cards[order,i,2] == 2)) \/
(card(card_set) = 4
/\ exists(j in 1..13)(forall(i in card_set)(cards[order,i,1] = j))
) \/
(card(card_set) = 1) \/
(card(card_set) = 2
/\ exists(j in 1..13)(forall(i in card_set)(cards[order,i,1] = j))) \/
(card(card_set) = 3
/\ exists(j in 1..13)(forall(i in card_set)(cards[order,i,1] = j))) \/
(card(card_set) = 4
/\ exists(j in 1..13)(sum(k in card_set where cards[order,k,1] = j)(1) = 3)) \/
(card(card_set) = 5
/\ exists(j in 1..13, l in 1..13 where j != l)
(sum(k in card_set where cards[order,k,1] = j)(1) = 3 /\ sum(k in card_set where cards[order,k,1] = l)(1) = 2)) \/
(card(card_set) >= 5
/\ exists(j in 3..13)
(forall(k in 1..card(card_set))(sum(c in card_set where cards[order,c,1] = k + j - 1)(1) = 1))) \/
(card(card_set) >= 6 /\ card(card_set) mod 2 = 0
/\ exists(j in 3..13)
(forall(k in 1..card(card_set) div 2)(sum(c in card_set where cards[order,c,1] = k + j - 1)(1) = 2))) \/
(card(card_set) >= 6 /\ card(card_set) mod 3 = 0
/\ exists(j in 3..13)
(forall(k in 1..card(card_set) div 3)(sum(c in card_set where cards[order,c,1] = k + j - 1)(1) = 3))) \/
(card(card_set) = 6
/\ exists(j in 1..13)
(sum(k in card_set where cards[order,k,1] = j)(1) = 4)) \/
(card(card_set) = 8
/\ exists(j in 1..13, l in 1..13, p in 1..13 where not(j == l \/ j == p \/ p == l))
(sum(k in card_set where cards[order,k,1] = j)(1) = 4 /\ sum(k in card_set where cards[order,k,1] = l)(1) = 2
/\ sum(k in card_set where cards[order,k,1] = p)(1) = 2)) \/
(card(card_set) = 0);
array[1..T,1..n] of var set of 1..n: card_order;
constraint forall(i in 1..T)(array_union(card_order[i,1..n]) = 1..n);
constraint forall(i in 1..T)(forall(j in 1..n,k in 1..n where j != k)(card_order[i,j] intersect card_order[i,k] = {}));
constraint forall(i in 1..T,j in 1..n)(valid(i,card_order[i,j]));
array[1..T] of var 1..n: ans;
constraint forall(i in 1..T)(ans[i] = count(j in 1..n)(card(card_order[i,j]) > 0));
solve satisfy;
output[show(ans)];
