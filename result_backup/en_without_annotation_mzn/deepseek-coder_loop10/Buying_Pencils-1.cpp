#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int n;
    int pencil[3][2];
    cin >> n;
    for (int i = 0; i < 3; ++i) {
        cin >> pencil[i][0] >> pencil[i][1];
    }

    int max_single = 0;
    for (int i = 0; i < 3; ++i) {
        max_single = max(max_single, (int)ceil((double)n / pencil[i][0]) * pencil[i][1]);
    }

    int cost = max_single * n;
    for (int i = 0; i < 3; ++i) {
        int num_packs = (int)ceil((double)n / pencil[i][0]);
        cost = min(cost, num_packs * pencil[i][1]);
    }

    cout << "cost=" << cost << endl;
    return 0;
}