#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<int> S(N), A(N);
    for (int i = 0; i < N; ++i) {
        cin >> S[i];
    }
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    // To accumulate results
    vector<long long> results(N);
    
    // We will calculate the fatigue incrementally
    long long totalWalkDistance = 0;
    long long totalFatigue = 0;
    
    for (int i = 0; i < N; ++i) {
        totalWalkDistance += S[N - 1]; // walking distance to the farthest household
        totalFatigue += A[i]; // selling fatigue
        
        // Each time we sell to the i-th house, add the round trip distance
        results[i] = totalWalkDistance * 2 + totalFatigue;
    }
    
    for (int i = 0; i < N; ++i) {
        cout << results[i] << endl;
    }

    return 0;
}