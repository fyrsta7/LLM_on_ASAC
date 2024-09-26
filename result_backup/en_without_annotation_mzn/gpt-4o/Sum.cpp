#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> color(n), number(n);
    for(int i = 0; i < n; ++i) {
        cin >> color[i];
    }
    for(int i = 0; i < n; ++i) {
        cin >> number[i];
    }
    
    int total = 0, res = 0;

    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            for(int k = j + 1; k < n; ++k) {
                if(color[i] == color[k] && k - j == j - i) {
                    total += (i + k) * (number[i] + number[k]);
                }
            }
        }
    }
    
    for(res = 0; res <= 10006; ++res) {
        if((total - res) % 10007 == 0) break;
    }

    cout << res << endl;
    return 0;
}