#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int value;
    int profit;
    double ratio;
};

bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> V(m), P(m);
    vector<Item> items(m);
    
    for (int i = 0; i < m; i++) {
        cin >> V[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> P[i];
    }
    
    for (int i = 0; i < m; i++) {
        items[i] = {V[i], P[i], (double)P[i] / V[i]};
    }
    
    sort(items.begin(), items.end(), compare);
    
    int currentWeight = 0;
    int maxProfit = 0;
    
    for (int i = 0; i < m; i++) {
        if (currentWeight + items[i].value <= n) {
            currentWeight += items[i].value;
            maxProfit += items[i].value * items[i].profit;
        }
    }
    
    cout << maxProfit << endl;
    
    return 0;
}