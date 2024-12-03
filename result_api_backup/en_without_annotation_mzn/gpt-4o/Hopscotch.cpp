#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    int n, d, k;
    cin >> n >> d >> k;
    vector<int> X(n), S(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> X[i];
    }

    for (int i = 0; i < n; ++i) {
        cin >> S[i];
    }

    int left = 0, right = 1000000000, g = 1000000000;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        bool possible = false;
        
        for (int i = 0; i < n; ++i) {
            set<int> A;
            int sumS = 0;

            for (int j = i; j < n; ++j) {
                bool valid = true;

                if (j > i && !A.empty()) {
                    auto it = prev(A.end());
                    if (!(X[j] - X[*it] >= d - mid && X[j] - X[*it] <= d + mid)) {
                        valid = false;
                    }
                }

                if (valid) {
                    A.insert(j);
                    sumS += S[j];

                    if (sumS >= k) {
                        possible = true;
                        break;
                    }

                    if (possible) {
                        break;
                    }
                }
            }

            if (possible) {
                break;
            }
        }

        if (possible) {
            g = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    cout << g << endl;
    return 0;
}
