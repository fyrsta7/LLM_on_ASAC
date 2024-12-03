#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }

    int m = 1;
    for (int i = 1; i < n; ++i) {
        if ((i % 2 == 0 && ((i - 1 > 0 && h[i] > h[i - 1]) || (i + 1 < n && h[i] > h[i + 1])))
         || (i % 2 == 0 && ((i - 1 > 0 && h[i] < h[i - 1]) || (i + 1 < n && h[i] < h[i + 1])))) {
            m++;
        }
    }

    cout << m << endl;
    return 0;
}