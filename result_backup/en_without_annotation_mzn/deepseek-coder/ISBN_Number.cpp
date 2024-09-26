#include <iostream>
#include <string>

using namespace std;

int convert_str(char s) {
    if (s == '1') return 1;
    if (s == '2') return 2;
    if (s == '3') return 3;
    if (s == '4') return 4;
    if (s == '5') return 5;
    if (s == '6') return 6;
    if (s == '7') return 7;
    if (s == '8') return 8;
    if (s == '9') return 9;
    if (s == '0') return 0;
    if (s == 'X') return 10;
    return -1;
}

int main() {
    string isbn;
    cin >> isbn;

    int answer = (convert_str(isbn[0]) * 1 + convert_str(isbn[2]) * 2 + convert_str(isbn[3]) * 3 +
                  convert_str(isbn[4]) * 4 + convert_str(isbn[6]) * 5 + convert_str(isbn[7]) * 6 +
                  convert_str(isbn[8]) * 7 + convert_str(isbn[9]) * 8 + convert_str(isbn[10]) * 9) % 11;

    bool right = (convert_str(isbn[12]) == answer);

    string isbn_part = isbn.substr(0, 12);
    string str_list[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "X"};
    string last_num = str_list[answer];

    string correct = right ? "Right" : isbn_part + last_num;

    cout << correct << endl;

    return 0;
}