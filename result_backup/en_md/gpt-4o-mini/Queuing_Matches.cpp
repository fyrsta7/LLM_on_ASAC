#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

const int MOD = 100000003;

int main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < n; ++i)
        cin >> b[i];

    unordered_map<int, int> countA, countB;

    for (int i = 0; i < n; ++i) {
        countA[a[i]]++;
        countB[b[i]]++;
    }

    vector<int> freqA, freqB;
    for (const auto& p : countA) {
        if (countB.count(p.first)) {
            freqA.push_back(p.second);
            freqB.push_back(countB[p.first]);
        } else {
            freqA.push_back(p.second);
            freqB.push_back(0);
        }
    }
    for (const auto& p : countB) {
        if (!countA.count(p.first)) {
            freqA.push_back(0);
            freqB.push_back(p.second);
        }
    }

    int swaps = 0;

    for (size_t i = 0; i < freqA.size(); ++i) {
        swaps += abs(freqA[i] - freqB[i]);
    }

    swaps /= 2;

    cout << swaps % MOD << endl;

    return 0;
}