#include <iostream>
#include <vector>

using namespace std;

struct Carpet {
    int x1, y1, x2, y2; // boundaries of the carpet
};

int main() {
    int n;
    cin >> n;
    vector<Carpet> carpets(n);

    for (int i = 0; i < n; ++i) {
        int a, b, g, k;
        cin >> a >> b >> g >> k;
        carpets[i] = {a, b, a + g, b + k}; // Store the corners of the carpet
    }

    int x, y;
    cin >> x >> y;

    // Check carpets from top to bottom
    for (int i = n - 1; i >= 0; --i) {
        if (x >= carpets[i].x1 && x <= carpets[i].x2 && y >= carpets[i].y1 && y <= carpets[i].y2) {
            cout << (i + 1) << endl; // Output the carpet number (1-indexed)
            return 0;
        }
    }

    cout << -1 << endl; // Point not covered by any carpet
    return 0;
}