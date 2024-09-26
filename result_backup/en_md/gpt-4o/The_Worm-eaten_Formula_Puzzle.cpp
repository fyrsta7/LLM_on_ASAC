#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

int n;
string first, second, result;
unordered_map<char, int> char_to_digit;
unordered_map<int, char> digit_to_char;

bool is_valid_assignment() {
    vector<int> carry(n + 1, 0);
    for (int i = n - 1; i >= 0; --i) {
        int digit1 = char_to_digit[first[i]];
        int digit2 = char_to_digit[second[i]];
        int digit_sum = digit1 + digit2 + carry[i + 1];
        carry[i] = digit_sum / n;
        if ((digit_sum % n) != char_to_digit[result[i]]) {
            return false;
        }
    }
    return carry[0] == 0;
}

bool assign_digits(vector<bool>& used_digits, int index) {
    if (index == n) {
        return is_valid_assignment();
    }
    for (int digit = 0; digit < n; ++digit) {
        if (!used_digits[digit]) {
            used_digits[digit] = true;
            char_to_digit[digit_to_char[index]] = digit;
            if (assign_digits(used_digits, index + 1)) {
                return true;
            }
            used_digits[digit] = false;
        }
    }
    return false;
}

int main() {
    cin >> n;
    cin >> first >> second >> result;

    vector<bool> used_digits(n, false);
    for (int i = 0; i < n; ++i) {
        digit_to_char[i] = 'A' + i;
    }

    assign_digits(used_digits, 0);

    vector<int> answer(n);
    for (int i = 0; i < n; ++i) {
        answer[digit_to_char[i] - 'A'] = char_to_digit['A' + i];
    }

    for (int i = 0; i < n; ++i) {
        cout << answer[i] << (i < n - 1 ? " " : "\n");
    }

    return 0;
}