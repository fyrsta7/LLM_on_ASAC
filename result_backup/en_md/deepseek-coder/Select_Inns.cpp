#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, p;
    cin >> n >> k >> p;

    vector<vector<int>> inns(k);
    vector<vector<int>> charges(k);

    for (int i = 0; i < n; ++i) {
        int color, charge;
        cin >> color >> charge;
        inns[color].push_back(i);
        charges[color].push_back(charge);
    }

    int totalOptions = 0;

    for (int color = 0; color < k; ++color) {
        const vector<int>& innIndices = inns[color];
        const vector<int>& cafeCharges = charges[color];
        int size = innIndices.size();

        for (int i = 0; i < size; ++i) {
            for (int j = i + 1; j < size; ++j) {
                int minCharge = *min_element(cafeCharges.begin() + i, cafeCharges.begin() + j + 1);
                if (minCharge <= p) {
                    totalOptions++;
                }
            }
        }
    }

    cout << totalOptions << endl;

    return 0;
}
