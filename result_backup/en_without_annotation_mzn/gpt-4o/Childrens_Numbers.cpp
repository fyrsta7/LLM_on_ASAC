#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

int main() {
    int n, p;
    cin >> n >> p;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> character(n, INT_MIN);
    vector<int> score(n, INT_MIN);
    
    for (int i = 0; i < n; ++i) {
        int maxSum = INT_MIN;
        for (int j = 0; j <= i; ++j) {
            int currentSum = 0;
            for (int k = j; k <= i; ++k) {
                currentSum += a[k];
            }
            maxSum = max(maxSum, currentSum);
        }
        character[i] = maxSum;
    }

    score[0] = character[0];
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            score[i] = max(score[i], character[j] + score[j]);
        }
    }

    int ans = *max_element(score.begin(), score.end()) % p;

    cout << ans << endl;

    return 0;
}