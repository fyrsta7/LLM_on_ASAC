#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    
    vector<int> index(n);
    for (int i = 0; i < n; ++i) {
        cin >> index[i];
    }
    
    vector<int> reader_token(q);
    vector<int> reader_bit(q);
    for (int i = 0; i < q; ++i) {
        cin >> reader_token[i] >> reader_bit[i];
    }
    
    vector<int> object(q, n + 1);
    
    for (int i = 0; i < q; ++i) {
        for (int k = 0; k < n; ++k) {
            if ((index[k] % (1 << reader_bit[i])) == reader_token[i]) {
                if (object[i] == n + 1 || index[k] < index[object[i]]) {
                    object[i] = k;
                }
            }
        }
    }
    
    for (int i = 0; i < q; ++i) {
        if (object[i] < n) {
            cout << index[object[i]] << endl;
        } else {
            cout << -1 << endl;
        }
    }
    
    return 0;
}