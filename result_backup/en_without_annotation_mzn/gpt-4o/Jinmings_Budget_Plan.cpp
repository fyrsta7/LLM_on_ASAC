#include <iostream>
#include <vector>
using namespace std;

int N, m;

struct Item {
    int size;
    int value;
    int mandatory;
};

int main() {
    cin >> N >> m;
    vector<Item> items(m);

    for (int i = 0; i < m; ++i) {
        cin >> items[i].size >> items[i].value >> items[i].mandatory;
    }

    int bestValue = 0;
    int combinations = 1 << m;

    for (int i = 0; i < combinations; ++i) {
        vector<bool> choose(m, false);
        int totalSize = 0;
        int totalValue = 0;
        bool valid = true;

        for (int j = 0; j < m; ++j) {
            if (i & (1 << j)) {
                choose[j] = true;
                totalSize += items[j].size;
                totalValue += items[j].size * items[j].value;

                if (items[j].mandatory != 0) {
                    choose[items[j].mandatory - 1] = true;
                    totalSize += items[items[j].mandatory - 1].size;
                    totalValue += items[items[j].mandatory - 1].size * items[items[j].mandatory - 1].value;
                }
            }
        }

        if (totalSize <= N && valid) {
            bestValue = max(bestValue, totalValue);
        }
    }

    cout << bestValue << endl;
    return 0;
}