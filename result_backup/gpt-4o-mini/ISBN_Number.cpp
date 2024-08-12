#include <iostream>
#include <string>

int main() {
    std::string isbn;
    std::cin >> isbn;

    int sum = 0;
    for (int i = 0, j = 1; i < 9; ++i, ++j) {
        if (isbn[i] != '-') {
            sum += (isbn[i] - '0') * j;
        }
    }

    int identifier = sum % 11;
    char correctIdentifier = (identifier == 10) ? 'X' : (identifier + '0');

    if (correctIdentifier == isbn[isbn.size() - 1]) {
        std::cout << "Right" << std::endl;
    } else {
        isbn[isbn.size() - 1] = correctIdentifier;
        std::cout << isbn << std::endl;
    }

    return 0;
}