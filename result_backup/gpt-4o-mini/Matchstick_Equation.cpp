#include <iostream>
#include <vector>

using namespace std;

const int matchsticks[10] = { 6, 2, 5, 5, 4, 5, 6, 3, 7, 6 }; // Matchsticks needed for digits 0-9
const int plus_sign = 2; // Matchsticks for '+'
const int equals_sign = 2; // Matchsticks for '='

void generate_numbers(vector<int>& numbers, int current, int remaining_sticks, int max_digit) {
    if (remaining_sticks < 0) return;
    if (current > 0) numbers.push_back(current);
    for (int digit = 0; digit <= max_digit; ++digit) {
        if (current == 0 && digit == 0) continue; // Skip leading zero
        generate_numbers(numbers, current * 10 + digit, remaining_sticks - matchsticks[digit], max_digit);
    }
}

int count_equations(int n) {
    int total_sticks_for_signs = plus_sign + equals_sign;
    int usable_sticks = n - total_sticks_for_signs;
    if (usable_sticks < 0) return 0;

    vector<int> numbers;
    generate_numbers(numbers, 0, usable_sticks, 9);

    int equation_count = 0;

    for (size_t i = 0; i < numbers.size(); ++i) {
        for (size_t j = 0; j < numbers.size(); ++j) {
            if (numbers[i] + numbers[j] < 0) continue; // Avoid negative sums
            int sum = numbers[i] + numbers[j];
            for (int k = 0; k < numbers.size(); ++k) {
                if (numbers[k] == sum) {
                    equation_count++; // Count A+B=C
                }
            }
        }
    }

    return equation_count;
}

int main() {
    int n;
    cin >> n;
    cout << count_equations(n) << endl;
    return 0;
}