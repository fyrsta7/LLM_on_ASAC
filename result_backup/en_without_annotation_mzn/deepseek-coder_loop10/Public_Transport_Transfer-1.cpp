#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Ticket {
    int type;
    int price;
    int time;
};

int main() {
    int n;
    cin >> n;
    vector<Ticket> tickets(n);
    for (int i = 0; i < n; ++i) {
        cin >> tickets[i].type >> tickets[i].price >> tickets[i].time;
    }

    vector<int> dp(n, 0);
    vector<bool> used(n, false);

    for (int i = 0; i < n; ++i) {
        dp[i] = tickets[i].price;
        for (int j = 0; j < i; ++j) {
            if (tickets[j].type == 0 && tickets[i].time - tickets[j].time <= 45 && tickets[j].price >= tickets[i].price) {
                dp[i] = min(dp[i], dp[j]);
            }
        }
    }

    int total = 0;
    for (int i = 0; i < n; ++i) {
        if (tickets[i].type == 0) {
            total += tickets[i].price;
        } else {
            total += dp[i];
        }
    }

    cout << total << endl;
    return 0;
}
