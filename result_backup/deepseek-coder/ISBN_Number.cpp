#include <iostream>
#include <string>
using namespace std;

int main() {
    string isbn;
    cin >> isbn;
    
    int sum = 0;
    int factor = 1;
    for (int i = 0; i < 11; ++i) {
        if (isbn[i] != '-') {
            sum += (isbn[i] - '0') * factor;
            ++factor;
        }
    }
    
    int remainder = sum % 11;
    char checkDigit = (remainder == 10) ? 'X' : (remainder + '0');
    
    if (isbn.back() == checkDigit) {
        cout << "Right" << endl;
    } else {
        isbn.back() = checkDigit;
        cout << isbn << endl;
    }
    
    return 0;
}
