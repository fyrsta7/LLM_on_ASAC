#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int sticks[] = {6,2,5,5,4,5,6,3,7,6};

int use_sticks(int num) {
    int count = 0;
    while (num > 0) {
        count += sticks[num % 10];
        num /= 10;
    }
    return count;
}

int main() {
    int n;
    cin >> n;

    int maxEquations = 0;
    vector<tuple<int, int, int>> solutions;

    for (int a = 0; a <= 100; a++) {
        for (int b = 0; b <= 100; b++) {
            int c = a + b;
            if (c > 100) continue;

            if (use_sticks(a) + use_sticks(b) + use_sticks(c) + 4 == n) {
                solutions.push_back({a, b, c});
                maxEquations = max(maxEquations, (int)solutions.size());
            }
        }
    }

    sort(solutions.begin(), solutions.end());
    solutions.erase(unique(solutions.begin(), solutions.end()), solutions.end());

    cout << solutions.size() << endl;
    return 0;
}