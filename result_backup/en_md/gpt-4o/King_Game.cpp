#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Minister {
    int left;
    int right;
    double cost;
};

bool compare(Minister& a, Minister& b) {
    return a.cost > b.cost;
}

int main() {
    int n;
    cin >> n;

    int kingLeft, kingRight;
    cin >> kingLeft >> kingRight;

    vector<Minister> ministers(n);
    for (int i = 0; i < n; ++i) {
        cin >> ministers[i].left >> ministers[i].right;
        ministers[i].cost = double(ministers[i].left) / ministers[i].right;
    }

    sort(ministers.begin(), ministers.end(), compare);

    long long product = kingLeft;
    int maxReward = 0;
    
    for (int i = 0; i < n; ++i) {
        int reward = product / ministers[i].right;
        maxReward = max(maxReward, reward);
        product *= ministers[i].left;
    }

    cout << maxReward << endl;
    return 0;
}