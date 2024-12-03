#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> arrivalTimes;
    vector<vector<int>> nationalities;
    
    arrivalTimes.reserve(n);
    nationalities.reserve(n);

    for (int i = 0; i < n; ++i) {
        int ti, ki;
        cin >> ti >> ki;
        
        arrivalTimes.push_back(ti);
        vector<int> tempNationalities(ki);
        
        for (int j = 0; j < ki; ++j) {
            cin >> tempNationalities[j];
        }
        
        nationalities.push_back(tempNationalities);
    }
    
    int windowStart = 0;
    unordered_set<int> currentNationalities;
    vector<int> passengerCount(100001, 0);
    
    for (int i = 0; i < n; ++i) {
        int currentTime = arrivalTimes[i];
        
        while (arrivalTimes[windowStart] <= currentTime - 86400) {
            for (int nationality : nationalities[windowStart]) {
                if (--passengerCount[nationality] == 0) {
                    currentNationalities.erase(nationality);
                }
            }
            ++windowStart;
        }
        
        for (int nationality : nationalities[i]) {
            if (++passengerCount[nationality] == 1) {
                currentNationalities.insert(nationality);
            }
        }
        
        cout << currentNationalities.size() << endl;
    }
    
    return 0;
}