int: n;
array[1..10] of var int: digits;
predicate reverse_num(var int: num, array[1..10] of var int: digits, var int: i) =
  if i > 10 then true
  else
    (digits[i] = num mod 10) /\ reverse_num(num div 10, digits, i + 1)
  endif;
constraint reverse_num(abs(n), digits, 1);
solve satisfy;
output[if n > 0 then "" elseif n == 0 then "0" else "-" endif];
output[if (fix(sum([digits[j] | j in 1..i])) != 0 /\ fix(sum([digits[j] | j in i..10])) != 0) then show(digits[i]) else "" endif | i in 1..10];
