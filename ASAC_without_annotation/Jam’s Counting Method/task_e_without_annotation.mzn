int: s;
int: t;
int: w;
array[1..w] of string: str;
array[int] of string: alphabet = ["a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"];
function int: get_num(string: letter) =
  if letter == "a" then 1
  elseif letter == "b" then 2
  elseif letter == "c" then 3
  elseif letter == "d" then 4
  elseif letter == "e" then 5
  elseif letter == "f" then 6
  elseif letter == "g" then 7
  elseif letter == "h" then 8
  elseif letter == "i" then 9
  elseif letter == "j" then 10
  elseif letter == "k" then 11
  elseif letter == "l" then 12
  elseif letter == "m" then 13
  elseif letter == "n" then 14
  elseif letter == "o" then 15
  elseif letter == "p" then 16
  elseif letter == "q" then 17
  elseif letter == "r" then 18
  elseif letter == "s" then 19
  elseif letter == "t" then 20
  elseif letter == "u" then 21
  elseif letter == "v" then 22
  elseif letter == "w" then 23
  elseif letter == "x" then 24
  elseif letter == "y" then 25
  else 26 endif;
function var int: distance(array[1..w] of var int: x1, array[1..w] of var int: x2) =
  sum(i in 1..w)((x2[i] - x1[i]) * pow(t - s + 1, w - i));
int: set_len = t - s + 1;
predicate larger(array[1..w] of var s..t: l, array[1..w] of var s..t: r, var int: pointer) =
  if pointer = w + 1 then false
  else l[pointer] > r[pointer] \/ (l[pointer] = r[pointer] /\ larger(l, r, pointer + 1)) endif;
array[1..w] of int: str_int = [get_num(str[i]) | i in 1..w];
array[0..5,1..w] of var s..t: str_list;
constraint str_list[0,1..w] = str_int;
constraint forall(i in 1..5)(forall(j,k in 1..w where j!=k)(str_list[i,j]!=str_list[i,k]));
constraint not exists(i,j in 1..5 where i!=j)(forall(k in 1..w)(str_list[i,k]=str_list[j,k]));
constraint forall(i in 1..5)(forall(j in 1..w-1)(str_list[i,j]<str_list[i,j+1]));
constraint forall(i,j in 0..5 where i<j)(larger(str_list[j,1..w],str_list[i,1..w],1));
var int: d = distance(str_list[0,1..w],str_list[5,1..w]);
solve minimize d;
output[alphabet[fix(str_list[k,i])] ++ if i==w then "\n" else "" endif | k in 1..5, i in 1..w];
