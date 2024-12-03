#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Inn {
    int color;
    int charge;
};

int main() {
    int n, k, p;
    cin >> n >> k >> p;

    vector<Inn> inns(n);
    for (int i = 0; i < n; ++i) {
        cin >> inns[i].color >> inns[i].charge;
    }

    unordered_map<int, vector<int>> colorMap;
    for (int i = 0; i < n; ++i) {
        colorMap[inns[i].color].push_back(inns[i].charge);
    }

    int optionCount = 0;
    for (const auto &entry : colorMap) {
        vector<int> charges = entry.second;
        sort(charges.begin(), charges.end());

        int size = charges.size();
        for (int i = 0; i < size; ++i) {
            for (int j = i + 1; j < size; ++j) {
                if (charges[j] <= p) {
                    optionCount++;
                } else {
                    break;
                }
            }
        }
    }

    cout << optionCount << endl;
    return 0;
}