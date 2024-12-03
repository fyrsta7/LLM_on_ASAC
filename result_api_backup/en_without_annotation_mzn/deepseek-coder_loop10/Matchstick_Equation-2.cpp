#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int sticks[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
const int L = 150;

int use_sticks(int num) {
    int count = 0;
    while (num > 0) {
        count += sticks[num % 10];
        num /= 10;
    }
    return count;
}

bool is_valid(int a, int b, int c, int n) {
    return use_sticks(a) + use_sticks(b) + use_sticks(c) + 4 == n;
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> equations;
    int ans = 0;

    for (int a = 0; a <= 100; ++a) {
        for (int b = 0; b <= 100; ++b) {
            int c = a + b;
            if (c > 100) continue;
            if (is_valid(a, b, c, n)) {
                equations.push_back({a, b, c});
                ans++;
            }
        }
    }

    sort(equations.begin(), equations.end());
    equations.erase(unique(equations.begin(), equations.end()), equations.end());

    cout << equations.size() << endl;

    return 0;
}
