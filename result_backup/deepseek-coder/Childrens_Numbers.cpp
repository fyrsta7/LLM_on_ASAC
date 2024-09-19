#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, p;
    cin >> n >> p;
    vector<long long> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    vector<long long> prefix_sum(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefix_sum[i + 1] = prefix_sum[i] + nums[i];
    }

    vector<long long> max_sum(n + 1, 0);
    long long current_max = nums[0];
    for (int i = 1; i <= n; ++i) {
        current_max = max(current_max, prefix_sum[i]);
        max_sum[i] = current_max;
    }

    vector<long long> scores(n);
    scores[0] = max_sum[1];
    long long max_score = scores[0];
    for (int i = 1; i < n; ++i) {
        scores[i] = max_score + max_sum[i + 1];
        max_score = max(max_score, scores[i]);
    }

    long long result = *max_element(scores.begin(), scores.end());
    result = (result % p + p) % p;
    cout << result << endl;

    return 0;
}
