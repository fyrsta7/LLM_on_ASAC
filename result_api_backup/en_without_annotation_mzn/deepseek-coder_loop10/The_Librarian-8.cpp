#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> index(n);
    vector<int> reader_token(q);
    vector<int> reader_bit(q);
    vector<int> object(q);

    for (int i = 0; i < n; ++i) {
        cin >> index[i];
    }

    for (int i = 0; i < q; ++i) {
        cin >> reader_token[i] >> reader_bit[i];
    }

    for (int i = 0; i < q; ++i) {
        int best_fit = n + 1;
        for (int k = 0; k < n; ++k) {
            if ((index[k] % (1 << reader_bit[i])) == reader_token[i]) {
                if (best_fit == n + 1 || index[k] < index[best_fit - 1]) {
                    best_fit = k + 1;
                }
            }
        }
        object[i] = best_fit;
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