#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> S(N), A(N);
    for (int i = 0; i < N; ++i) cin >> S[i];
    for (int i = 0; i < N; ++i) cin >> A[i];

    vector<pair<int, int>> households(N);
    for (int i = 0; i < N; ++i) {
        households[i] = {S[i], A[i]};
    }

    sort(households.begin(), households.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    });

    vector<long long> fatigue(N);
    long long max_distance = 0;
    long long total_fatigue = 0;

    for (int i = 0; i < N; ++i) {
        total_fatigue += households[i].second;
        max_distance = max(max_distance, (long long)households[i].first);
        fatigue[i] = total_fatigue + 2 * max_distance;
    }

    for (int i = 0; i < N; ++i) {
        cout << fatigue[i] << '\n';
    }

    return 0;
}
