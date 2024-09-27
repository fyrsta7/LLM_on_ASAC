#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    
    int len = pow(10, k);
    vector<int> suffix(len + 1);
    unordered_set<int> seen;
    
    int current = 1;
    for (int i = 1; i <= len; ++i) {
        current = (current * n) % len;
        suffix[i] = current;
        if (i == 1) {
            seen.insert(current);
        } else if (current == suffix[1]) {
            cout << i - 1 << endl;
            return 0;
        }
    }
    
    cout << -1 << endl;
    return 0;
}