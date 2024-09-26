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
    
    int total_value = 0;
    int total_price = 0;
    
    for (int i = 0; i < m; ++i) {
        if (total_value + items[i].value <= n) {
            total_value += items[i].value;
            total_price += items[i].price;
        }
    }
    
    cout << total_price << endl;
    
    return 0;
}
