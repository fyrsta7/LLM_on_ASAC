#include <iostream>
#include <string>
using namespace std;

int convert_str(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c == 'X') return 10;
    return -1;
}

int main() {
    string isbn;
    cin >> isbn;
    
    int sum = 0;
    sum += convert_str(isbn[0]) * 1;
    sum += convert_str(isbn[2]) * 2;
    sum += convert_str(isbn[3]) * 3;
    sum += convert_str(isbn[4]) * 4;
    sum += convert_str(isbn[6]) * 5;
    sum += convert_str(isbn[7]) * 6;
    sum += convert_str(isbn[8]) * 7;
    sum += convert_str(isbn[9]) * 8;
    sum += convert_str(isbn[10]) * 9;
    
    int answer = sum % 11;
    bool right = (convert_str(isbn[12]) == answer);
    
    string isbn_part = isbn.substr(0, 12);
    string last_num = (answer == 10) ? "X" : to_string(answer);
    
    string correct = right ? "Right" : isbn_part + last_num;
    
    cout << correct << endl;
    
    return 0;
}