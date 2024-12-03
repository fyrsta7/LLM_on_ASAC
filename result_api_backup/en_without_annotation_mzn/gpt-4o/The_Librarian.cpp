#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    
    vector<int> index(n);
    vector<int> reader_token(q);
    vector<int> reader_bit(q);
    
    for (int i = 0; i < n; ++i) cin >> index[i];
    for (int i = 0; i < q; ++i) cin >> reader_token[i];
    for (int i = 0; i < q; ++i) cin >> reader_bit[i];
    
    vector<int> object(q, n + 1); // default to n+1 (unmatched)

    for (int i = 0; i < q; ++i) {
        int best = n + 1; // default to n+1 (unmatched)
        for (int j = 0; j < n; ++j) {
            if (index[j] % (int)pow(10, reader_bit[i]) == reader_token[i]) {
                if (best == n + 1 || index[j] < index[best]) {
                    best = j;
                }
            }
        }
        object[i] = best;
    }

    for (int i = 0; i < q; ++i) {
        if (object[i] < n) 
            cout << index[object[i]] << endl;
        else 
            cout << -1 << endl;
    }

    return 0;
}