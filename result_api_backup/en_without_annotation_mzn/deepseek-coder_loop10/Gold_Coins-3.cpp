#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> give(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        give[i] = i;
    }

    long long total = 0;
    int cur = 1;
    for (int i = 1; i <= n; ++i) {
        total += give[i];
        if (i == cur) {
            cur = i + 1;
        }
    }

    cout << total << endl;
    return 0;
}