#include <iostream>
#include <string>
using namespace std;

int convert_str(char s) {
    switch (s) {
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case '0': return 0;
        case 'X': return 10;
        default: return -1;
    }
}

int main() {
    string isbn;
    cin >> isbn;
    
    int answer = (convert_str(isbn[0]) * 1 + convert_str(isbn[2]) * 2 + convert_str(isbn[3]) * 3 + convert_str(isbn[4]) * 4 +
                  convert_str(isbn[6]) * 5 + convert_str(isbn[7]) * 6 + convert_str(isbn[8]) * 7 + convert_str(isbn[9]) * 8 + convert_str(isbn[10]) * 9) % 11;
    
    bool right = (convert_str(isbn[12]) == answer);
    
    string isbn_part = isbn.substr(0, 12);
    string str_list = "0123456789X";
    string last_num = string(1, str_list[answer]);
    
    string correct = right ? "Right" : isbn_part + last_num;
    
    cout << correct << endl;
    
    return 0;
}