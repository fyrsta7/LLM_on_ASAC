#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Minister {
    int left, right;
};

int main() {
    int n;
    cin >> n;

    int king_left, king_right;
    cin >> king_left >> king_right;

    vector<Minister> ministers(n);
    for (int i = 0; i < n; ++i) {
        cin >> ministers[i].left >> ministers[i].right;
    }

    // Sort ministers by (left hand value / right hand value) to minimize the maximum reward
    sort(ministers.begin(), ministers.end(), [](const Minister& a, const Minister& b) {
        return static_cast<long long>(a.left) * b.right < static_cast<long long>(b.left) * a.right;
    });

    int max_reward = 0;
    long long product = king_left;

    for (int i = 0; i < n; ++i) {
        max_reward = max(max_reward, static_cast<int>(product / ministers[i].right));
        product *= ministers[i].left;
    }

    cout << max_reward << endl;

    return 0;
}