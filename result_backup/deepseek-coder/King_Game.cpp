#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Minister {
    int left, right;
};

bool compare(Minister a, Minister b) {
    return a.left * a.right < b.left * b.right;
}

int main() {
    int n;
    cin >> n;
    vector<Minister> ministers(n);
    int kingLeft, kingRight;
    cin >> kingLeft >> kingRight;

    for (int i = 0; i < n; ++i) {
        cin >> ministers[i].left >> ministers[i].right;
    }

    sort(ministers.begin(), ministers.end(), compare);

    long long maxReward = 0;
    long long product = kingLeft;

    for (int i = 0; i < n; ++i) {
        long long reward = product / ministers[i].right;
        if (reward > maxReward) {
            maxReward = reward;
        }
        product *= ministers[i].left;
    }

    cout << maxReward << endl;

    return 0;
}
