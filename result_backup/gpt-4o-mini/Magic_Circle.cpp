#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<int> magicValues(m);
    for (int i = 0; i < m; i++) {
        cin >> magicValues[i];
    }
    
    vector<int> countA(m, 0), countB(m, 0), countC(m, 0), countD(m, 0);
    
    // Create a map to find indices of items by their magic values
    unordered_map<int, vector<int>> valueToIndices;
    for (int i = 0; i < m; i++) {
        valueToIndices[magicValues[i]].push_back(i);
    }
    
    for (int bIndex = 0; bIndex < m; bIndex++) {
        int Xb = magicValues[bIndex];
        
        for (int diff = 1; Xb - diff >= 0; diff++) {
            int Xa = Xb - diff;
            int Xd = Xb + diff;
            int Xc = Xb + diff * 2;
            
            if (Xc > n || Xd > n) continue;
            
            if (valueToIndices.find(Xa) != valueToIndices.end() && 
                valueToIndices.find(Xc) != valueToIndices.end() &&
                valueToIndices.find(Xd) != valueToIndices.end()) {
                
                for (int aIndex : valueToIndices[Xa]) {
                    countA[aIndex]++;
                }
                
                for (int dIndex : valueToIndices[Xd]) {
                    countD[dIndex]++;
                }
                
                for (int cIndex : valueToIndices[Xc]) {
                    countC[cIndex]++;
                }
                
                // For the current bIndex, count it as B
                countB[bIndex]++;
            }
        }
    }
    
    for (int i = 0; i < m; i++) {
        cout << countA[i] << " " << countB[i] << " " << countC[i] << " " << countD[i] << endl;
    }
    
    return 0;
}