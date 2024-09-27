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
    for (int i = 0; i < m; ++i) {
        if (n >= items[i].value) {
            obj += items[i].value * items[i].price;
            n -= items[i].value;
        } else {
            obj += n * items[i].price;
            break;
        }
    }
    
    cout << obj << endl;
    return 0;
}