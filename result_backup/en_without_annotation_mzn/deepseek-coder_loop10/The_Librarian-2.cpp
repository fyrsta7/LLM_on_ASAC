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
        int token = reader_token[i];
        int bit = reader_bit[i];
        int pow10 = 1;
        for (int b = 0; b < bit; ++b) {
            pow10 *= 10;
        }
        
        for (int j = 0; j < n; ++j) {
            if ((index[j] % pow10) == token) {
                if (object[i] == n + 1 || index[j] < index[object[i] - 1]) {
                    object[i] = j + 1;
                }
            }
        }
    }
    
    for (int i = 0; i < q; ++i) {
        if (object[i] == n + 1) {
            cout << -1 << endl;
        } else {
            cout << index[object[i] - 1] << endl;
        }
    }
    
    return 0;
}