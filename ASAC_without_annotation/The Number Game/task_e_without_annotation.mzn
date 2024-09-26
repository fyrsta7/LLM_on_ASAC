string: numstr;
int: num_length = string_length(numstr);
var int: one_num;
constraint one_num = sum(i in 1..num_length where numstr[i] = "1")(1);
solve satisfy;
output ["\(one_num)"];
