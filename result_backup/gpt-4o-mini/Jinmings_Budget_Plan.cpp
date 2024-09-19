#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    int price, importance, mainItem;
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<Item> items(m + 1);  // to store items indexed from 1
    vector<int> mainItems; // to store main items with their accessories

    for (int i = 1; i <= m; ++i) {
        cin >> items[i].price >> items[i].importance >> items[i].mainItem;
        if (items[i].mainItem == 0) {
            mainItems.push_back(i); // store index of main items
        }
    }

    vector<int> dp(n + 1, 0); // dp array for knapsack problem

    // Process each main item
    for (int mainIndex : mainItems) {
        int mainPrice = items[mainIndex].price;
        int mainImportance = items[mainIndex].importance;

        // Initial knapsack for including the main item itself
        for (int j = n; j >= mainPrice; --j) {
            dp[j] = max(dp[j], dp[j - mainPrice] + mainPrice * mainImportance);
        }

        // Now check accessories
        for (int i = 1; i <= m; ++i) {
            if (items[i].mainItem == mainIndex) {
                int accessoryPrice = items[i].price;
                int accessoryImportance = items[i].importance;

                // Check if we can include the accessory
                for (int j = n; j >= mainPrice + accessoryPrice; --j) {
                    dp[j] = max(dp[j], dp[j - accessoryPrice] + accessoryPrice * accessoryImportance + mainPrice * mainImportance);
                }
            }
        }
    }

    cout << *max_element(dp.begin(), dp.end()) << endl; // Print maximum value
    return 0;
}