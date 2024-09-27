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

    for (int i = 2; i <= n; ++i) {
        for (int j = i; j <= n; j += i) {
            give[j] = i;
        }
    }

    long long total = 0;
    for (int i = 1; i <= n; ++i) {
        total += give[i];
    }

    cout << total << endl;
    return 0;
}