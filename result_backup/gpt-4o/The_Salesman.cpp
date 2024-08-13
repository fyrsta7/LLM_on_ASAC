#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N;
    cin >> N;
    
    vector<int> S(N), A(N), result(N);
    
    for (int i = 0; i < N; ++i) {
        cin >> S[i];
    }
    
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    
    vector<pair<int, int>> households(N);
    for (int i = 0; i < N; ++i) {
        households[i] = {S[i], A[i]};
    }
    
    sort(households.begin(), households.end(), [](pair<int, int> &a, pair<int, int> &b) {
        return a.second > b.second; // Sort by fatigue value in descending order
    });
    
    int maxDistance = households[0].first;
    int totalSellingFatigue = 0;
    
    for (int i = 0; i < N; ++i) {
        maxDistance = max(maxDistance, households[i].first);
        totalSellingFatigue += households[i].second;
        
        result[i] = 2 * maxDistance + totalSellingFatigue;
    }
    
    for (int i = 0; i < N; ++i) {
        cout << result[i] << endl;
    }

    return 0;
}
