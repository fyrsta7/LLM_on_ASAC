#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> carpets(n, vector<int>(4));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 4; ++j) {
            cin >> carpets[i][j];
        }
    }
    int x, y;
    cin >> x >> y;
    
    int ans = -1;
    
    for (int i = 0; i < n; ++i) {
        int x1 = carpets[i][0];
        int y1 = carpets[i][1];
        int x2 = x1 + carpets[i][2];
        int y2 = y1 + carpets[i][3];
        
        if (x >= x1 && y >= y1 && x <= x2 && y <= y2) {
            ans = i + 1;  // Convert 0-based index to 1-based index
        }
    }
    
    cout << ans << endl;
    
    return 0;
}