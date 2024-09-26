#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Tourist {
    int arrivalTime;
    int from;
    int to;
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;
  
    vector<int> D(n - 1);
    for(int i = 0; i < n - 1; i++) {
        cin >> D[i];
    }
    
    vector<Tourist> tourists(m);
    for(int i = 0; i < m; i++) {
        cin >> tourists[i].arrivalTime >> tourists[i].from >> tourists[i].to;
    }

    // Collect waiting times for each scenic spot
    vector<vector<int>> waitTimes(n + 1);
    for(auto& tourist : tourists) {
        waitTimes[tourist.from].push_back(tourist.arrivalTime);
    }

    vector<int> finishTimes(n, 0);
    int totalTravelTime = 0;
   
    for(int i = 0; i < n - 1; i++) {
        int currentTime = finishTimes[i];
        // Wait for tourists at scenic spot i+1
        if(!waitTimes[i + 1].empty()) {
            sort(waitTimes[i + 1].begin(), waitTimes[i + 1].end());
            for(int arrival : waitTimes[i + 1]) {
                if(arrival > currentTime) {
                    currentTime = arrival;
                }
            }
        }
        
        finishTimes[i + 1] = currentTime + D[i];
        
        // Use k accelerators
        if (k > 0) {
            int originalD = D[i];
            int reducedD = max(0, originalD - k);
            k -= (originalD - reducedD);
            D[i] = reducedD;
        }
        
        finishTimes[i + 1] += D[i];
    }
    
    for(int i = 0; i < m; i++) {
        totalTravelTime += finishTimes[tourists[i].to - 1] - tourists[i].arrivalTime;
    }
  
    cout << totalTravelTime << endl;
    return 0;
}