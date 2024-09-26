#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, p;
    cin >> n >> p;
    vector<long long> nums(n), charValue(n), score(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    
    charValue[0] = nums[0];
    score[0] = charValue[0];

    // Calculate characteristic values and scores
    for (int i = 1; i < n; ++i) {
        charValue[i] = max(charValue[i - 1] + nums[i], nums[i]);
        score[i] = charValue[i];
        long long maxPrevScore = score[0];
        for (int j = 1; j < i; ++j) {
            maxPrevScore = max(maxPrevScore, score[j]);
        }
        score[i] = max(score[i], maxPrevScore + charValue[i]);
    }

    // Find the maximum score
    long long maxScore = score[0];
    for (int i = 1; i < n; ++i) {
        maxScore = max(maxScore, score[i]);
    }

    // Output the result
    cout << maxScore % p << endl;

    return 0;
}