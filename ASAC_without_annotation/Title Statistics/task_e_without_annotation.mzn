string: title;
int: title_length = string_length(title);
var int: answer;
constraint answer = sum(i in 1..title_length where title[i] != " ")(1);
solve satisfy;
output [show(answer)];
