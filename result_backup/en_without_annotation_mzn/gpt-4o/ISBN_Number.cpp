#include <iostream>
#include <string>

int convert_char(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c == 'X') return 10;
    return -1;
}

int main() {
    std::string isbn;
    std::cin >> isbn;

    int answer = (convert_char(isbn[0]) * 1 + convert_char(isbn[2]) * 2 + convert_char(isbn[3]) * 3 + convert_char(isbn[4]) * 4 +
                  convert_char(isbn[6]) * 5 + convert_char(isbn[7]) * 6 + convert_char(isbn[8]) * 7 + convert_char(isbn[9]) * 8 + convert_char(isbn[10]) * 9) % 11;

    char correct_last_char = (answer == 10) ? 'X' : answer + '0';

    if (isbn[12] == correct_last_char) {
        std::cout << "Right" << std::endl;
    } else {
        isbn[12] = correct_last_char;
        std::cout << isbn << std::endl;
    }

    return 0;
}