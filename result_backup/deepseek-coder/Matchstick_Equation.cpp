#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int matchsticks[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int countMatches(int num) {
    if (num == 0) return matchsticks[0];
    int count = 0;
    while (num > 0) {
        count += matchsticks[num % 10];
        num /= 10;
    }
    return count;
}

int main() {
    int n;
    cin >> n;
    n -= 4; // Subtract the matches used by '+' and '='

    vector<int> validNumbers;
    for (int i = 0; i <= 1000; ++i) {
        if (countMatches(i) <= n) {
            validNumbers.push_back(i);
        }
    }

    int count = 0;
    for (int a : validNumbers) {
        for (int b : validNumbers) {
            int c = a + b;
            if (countMatches(a) + countMatches(b) + countMatches(c) == n) {
                count++;
            }
        }
    }

    cout << count << endl;
    return 0;
}
