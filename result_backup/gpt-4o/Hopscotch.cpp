#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Square {
    int x, points;
};

bool canAchieveKPoints(int n, int d, int k, const vector<Square>& squares, int g) {
    vector<long long> dp(n, LLONG_MIN);
    dp[0] = squares[0].points;

    deque<int> dq;
    dq.push_back(0);
    
    for (int i = 1; i < n; ++i) {
        while (!dq.empty() && squares[i].x - squares[dq.front()].x > d + g) {
            dq.pop_front();
        }
        while (!dq.empty() && squares[i].x - squares[dq.front()].x < d - g) {
            dq.pop_front();
        }
        if (!dq.empty()) {
            dp[i] = dp[dq.front()] + squares[i].points;
        }

        while (!dq.empty() && dp[dq.back()] < dp[i]) {
            dq.pop_back();
        } 
        dq.push_back(i);
    }
    
    for (int i = 0; i < n; ++i) {
        if (dp[i] >= k) {
            return true;
        }
    }
    return false;
}

int main() {
    int n, d, k;
    cin >> n >> d >> k;

    vector<Square> squares(n);
    for (int i = 0; i < n; ++i) {
        cin >> squares[i].x >> squares[i].points;
    }
    
    int left = 0, right = d + k;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (canAchieveKPoints(n, d, k, squares, mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    cout << result << endl;
    return 0;
}