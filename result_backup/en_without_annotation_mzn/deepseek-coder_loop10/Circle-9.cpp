#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    
    int len = 1;
    for (int i = 0; i < k; ++i) {
        len *= 10;
    }
    
    vector<int> suffix(len + 1);
    suffix[1] = n % len;
    
    for (int i = 2; i <= len; ++i) {
        suffix[i] = (suffix[i - 1] * n) % len;
    }
    
    vector<int> seen(len, -1);
    int cycle_start = -1;
    
    for (int i = 1; i <= len; ++i) {
        if (seen[suffix[i]] != -1) {
            cycle_start = seen[suffix[i]];
            break;
        }
        seen[suffix[i]] = i;
    }
    
    if (cycle_start == -1) {
        cout << "-1" << endl;
    } else {
        cout << cycle_start - 1 << endl;
    }
    
    return 0;
}