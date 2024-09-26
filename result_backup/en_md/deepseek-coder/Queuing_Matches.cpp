#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

const int MOD = 1000000007;

int main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    unordered_map<int, int> pos;
    for (int i = 0; i < n; ++i) {
        pos[b[i]] = i;
    }

    vector<int> seq(n);
    for (int i = 0; i < n; ++i) {
        seq[i] = pos[a[i]];
    }

    vector<int> temp = seq;
    sort(temp.begin(), temp.end());

    int swaps = 0;
    for (int i = 0; i < n; ++i) {
        if (seq[i] != temp[i]) {
            int j = i + 1;
            while (j < n && seq[j] != temp[i]) ++j;
            swap(seq[i], seq[j]);
            ++swaps;
        }
    }

    cout << swaps % MOD << endl;
    return 0;
}
