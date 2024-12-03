#include <iostream>
#include <string>

using namespace std;

void expandString(int p1, int p2, int p3, const string &input) {
    string output;
    for (size_t i = 0; i < input.size(); i++) {
        if (i > 0 && input[i] == '-') {
            char left = input[i - 1];
            char right = input[i + 1];

            if (left < right) {
                if (p1 == 1 || p1 == 2) {
                    char start = left + 1;
                    char end = right;
                    for (char ch = start; ch < end; ch++) {
                        char fillChar = (p1 == 1) ? ch : char(ch - 32);
                        output.append(p2, fillChar);
                    }
                } else {
                    int count = right - left - 1;
                    output.append(count * p2, '*');
                }
                // Skip the next character since it's processed
                i++;
            } else if (left == right) {
                output += left;
                output += left; // Just keep both left and right
            } else {
                output += left;
                output += '-';
            }
        } else {
            output += input[i];
        }
    }
    // Handle reverse order if needed
    if (p3 == 2) {
        reverse(output.begin(), output.end());
    }
    cout << output;
}

int main() {
    int p1, p2, p3;
    string input;

    cin >> p1 >> p2 >> p3;
    cin >> input;

    expandString(p1, p2, p3, input);
    return 0;
}