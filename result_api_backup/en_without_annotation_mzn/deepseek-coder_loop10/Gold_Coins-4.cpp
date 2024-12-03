#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> give(n + 1, 0);
    for (int day = 1; day <= n; ++day) {
        give[day] = (day + 1) / 2;
    }

    long long total = 0;
    for (int i = 1; i <= n; ++i) {
        total += give[i];
    }

    cout << total << endl;

    return 0;
}