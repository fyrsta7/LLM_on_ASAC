#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct MagicItem {
    int value, index;
    MagicItem(int v, int i) : value(v), index(i) {}
};

bool compareByValue(const MagicItem &a, const MagicItem &b) {
    return a.value < b.value;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<MagicItem> items;
    vector<int> resultA(m, 0), resultB(m, 0), resultC(m, 0), resultD(m, 0);

    for (int i = 0; i < m; ++i) {
        int val;
        cin >> val;
        items.emplace_back(val, i);
    }

    sort(items.begin(), items.end(), compareByValue);

    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            for (int k = j + 1; k < m; ++k) {
                for (int l = k + 1; l < m; ++l) {
                    int Xa = items[i].value, Xb = items[j].value;
                    int Xc = items[k].value, Xd = items[l].value;

                    if (Xb - Xa == 2 * (Xd - Xc) && Xb - Xa < (Xc - Xb) / 3) {
                        resultA[items[i].index]++;
                        resultB[items[j].index]++;
                        resultC[items[k].index]++;
                        resultD[items[l].index]++;
                    }
                }
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        cout << resultA[i] << " " << resultB[i] << " " << resultC[i] << " " << resultD[i] << endl;
    }

    return 0;
}