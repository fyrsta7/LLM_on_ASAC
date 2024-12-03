#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, p;
    cin >> n >> p;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> character(n);
    vector<int> score(n);

    // Calculate character array
    for (int i = 0; i < n; ++i) {
        int max_sum = a[i];
        int current_sum = a[i];
        for (int j = i - 1; j >= 0; --j) {
            current_sum += a[j];
            max_sum = max(max_sum, current_sum);
        }
        character[i] = max_sum;
    }

    // Calculate score array
    score[0] = character[0];
    for (int i = 1; i < n; ++i) {
        score[i] = character[i];
        for (int j = 0; j < i; ++j) {
            score[i] = max(score[i], character[i] + score[j]);
        }
    }

    // Find the maximum score and compute the answer
    int max_score = *max_element(score.begin(), score.end());
    int ans = max_score % p;

    cout << ans << endl;

    return 0;
}