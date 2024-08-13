#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main() {
    int n, k, p;
    cin >> n >> k >> p;
    
    vector<pair<int, int>> inns(n);
    for (int i = 0; i < n; ++i) {
        cin >> inns[i].first >> inns[i].second;
    }
    
    vector<vector<int>> color_inns(k);
    for (int i = 0; i < n; ++i) {
        color_inns[inns[i].first].push_back(i);
    }
    
    int count = 0;
    for (int i = 0; i < k; ++i) {
        vector<int>& inns_of_color = color_inns[i];
        int size = inns_of_color.size();
        for (int j = 0; j < size; ++j) {
            int charge = inns[inns_of_color[j]].second;
            if (charge <= p) {
                for (int l = j + 1; l < size; ++l) {
                    int max_charge = charge;
                    for (int m = inns_of_color[j]; m <= inns_of_color[l]; ++m) {
                        max_charge = max(max_charge, inns[m].second);
                    }
                    if (max_charge <= p) {
                        ++count;
                    }
                }
            }
        }
    }
    
    cout << count << endl;
    return 0;
}