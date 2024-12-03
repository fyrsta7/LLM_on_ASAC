#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> pencil(3, vector<int>(2));
    for(int i = 0; i < 3; ++i) {
        cin >> pencil[i][0] >> pencil[i][1];
    }

    int min_cost = INT_MAX;
    for(int i = 0; i < 3; ++i) {
        int num_pencils = (n + pencil[i][0] - 1) / pencil[i][0];
        int cost = num_pencils * pencil[i][1];
        min_cost = min(min_cost, cost);
    }

    cout << "cost=" << min_cost << endl;
    return 0;
}