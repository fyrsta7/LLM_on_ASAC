#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

int main() {
    int N;
    cin >> N;
    long long m1, m2;
    cin >> m1 >> m2;
    
    long long M = pow(m1, m2);
    vector<long long> S(N);
    
    for (int i = 0; i < N; i++) {
        cin >> S[i];
    }
    
    long long min_time = numeric_limits<long long>::max();
    
    for (int i = 0; i < N; i++) {
        long long cells = 1, time = 0;
        
        while (cells < M) {
            cells *= S[i];
            time++;
        }
        
        if (cells == M) {
            min_time = min(min_time, time);
        }
    }
    
    if (min_time == numeric_limits<long long>::max()) {
        cout << -1 << endl;
    } else {
        cout << min_time << endl;
    }
    
    return 0;
}