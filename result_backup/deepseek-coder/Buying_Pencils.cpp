#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    int minCost = INT_MAX;
    for (int i = 0; i < 3; ++i) {
        int numPencils, price;
        cin >> numPencils >> price;
        int packages = (n + numPencils - 1) / numPencils;
        int totalCost = packages * price;
        minCost = min(minCost, totalCost);
    }
    cout << minCost << endl;
    return 0;
}
