#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    
    vector<vector<int>> conflict(M, vector<int>(3));
    for (int i = 0; i < M; ++i) {
        cin >> conflict[i][0] >> conflict[i][1] >> conflict[i][2];
    }
    
    int min_final_value = INT_MAX;
    
    for (int mask = 0; mask < (1 << N); ++mask) {
        vector<int> prison1, prison2;
        
        for (int i = 0; i < N; ++i) {
            if (mask & (1 << i)) {
                prison1.push_back(i + 1);
            } else {
                prison2.push_back(i + 1);
            }
        }
        
        int value1 = 0, value2 = 0;
        
        if (prison1.size() >= 2) {
            for (int i = 0; i < M; ++i) {
                if (find(prison1.begin(), prison1.end(), conflict[i][0]) != prison1.end() &&
                    find(prison1.begin(), prison1.end(), conflict[i][1]) != prison1.end()) {
                    value1 = max(value1, conflict[i][2]);
                }
            }
        }
        
        if (prison2.size() >= 2) {
            for (int i = 0; i < M; ++i) {
                if (find(prison2.begin(), prison2.end(), conflict[i][0]) != prison2.end() &&
                    find(prison2.begin(), prison2.end(), conflict[i][1]) != prison2.end()) {
                    value2 = max(value2, conflict[i][2]);
                }
            }
        }
        
        int final_value = max(value1, value2);
        min_final_value = min(min_final_value, final_value);
    }
    
    cout << min_final_value << endl;
    
    return 0;
}
