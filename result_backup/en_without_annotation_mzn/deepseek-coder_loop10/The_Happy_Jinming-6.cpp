#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int value;
    int price;
    double ratio;
};

bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Item> items(m);
    
    for (int i = 0; i < m; ++i) {
        cin >> items[i].value;
    }
    
    for (int i = 0; i < m; ++i) {
        cin >> items[i].price;
        items[i].ratio = static_cast<double>(items[i].price) / items[i].value;
    }
    
    sort(items.begin(), items.end(), compare);
    
    int obj = 0;
    for (int i = 0; i < m && n > 0; ++i) {
        int buy_amount = min(n, items[i].value);
        obj += buy_amount * items[i].price;
        n -= buy_amount;
    }
    
    cout << obj << endl;
    
    return 0;
}