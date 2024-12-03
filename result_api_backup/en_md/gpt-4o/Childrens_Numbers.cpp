#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, p;
    cin >> n >> p;
    
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    
    vector<long long> characteristic_value(n);
    vector<long long> scores(n);

    // Calculate the characteristic values
    long long current_sum = 0, max_sum = nums[0];
    characteristic_value[0] = max_sum;

    for (int i = 1; i < n; ++i) {
        current_sum = max((long long)nums[i], current_sum + nums[i]);
        max_sum = max(max_sum, current_sum);
        characteristic_value[i] = max_sum;
    }

    // Calculate the scores
    scores[0] = characteristic_value[0];
    for (int i = 1; i < n; ++i) {
        long long max_score = characteristic_value[i];
        for (int j = 0; j < i; ++j) {
            max_score = max(max_score, scores[j] + characteristic_value[i]);
        }
        scores[i] = max_score;
    }

    // Find the maximum score and calculate the required result
    long long max_score = *max_element(scores.begin(), scores.end());
    long long result = max_score % p;

    // Output the result
    cout << result << endl;

    return 0;
}