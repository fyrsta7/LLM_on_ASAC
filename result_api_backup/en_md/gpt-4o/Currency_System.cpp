#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int findGCD(int x, int y) {
    while (y != 0) {
        int temp = y;
        y = x % y;
        x = temp;
    }
    return x;
}

int findMinDenominations(vector<int>& a) {
    sort(a.begin(), a.end());
    vector<bool> canRepresent(30001, false);
    canRepresent[0] = true;
    
    for (int i = 0; i < a.size(); ++i) {
        for (int j = a[i]; j < canRepresent.size(); ++j) {
            if (canRepresent[j - a[i]]) {
                canRepresent[j] = true;
            }
        }
    }
    
    for (int i = 1; i < canRepresent.size(); ++i) {
        if (!canRepresent[i]) {
            return 1;
        }
    }
    
    int gcdOverall = a[0];
    for (int i = 1; i < a.size(); ++i) {
        gcdOverall = gcd(gcdOverall, a[i]);
    }
    if (gcdOverall != 1) {
        return a.size();
    }
    
    vector<int> basis;
    for (int den : a) {
        bool independent = true;
        for (int b : basis) {
            int g = findGCD(den, b);
            if (g != 1) {
                independent = false;
                break;
            }
        }
        if (independent) {
            basis.push_back(den);
        }
    }
    return basis.size();
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        cout << findMinDenominations(a) << endl;
    }
    return 0;
}