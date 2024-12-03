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
    vector<int> used(n, 0);

    for (int i = 0; i < n; ++i) {
        dp[i] = tickets[i].price;
        for (int j = 0; j < i; ++j) {
            if (tickets[j].type == 0 && tickets[i].time - tickets[j].time <= 45 && tickets[j].price >= tickets[i].price) {
                if (dp[i] > dp[j]) {
                    dp[i] = dp[j];
                    used[i] = j + 1;
                }
            }
        }
    }

    int total = 0;
    for (int i = 0; i < n; ++i) {
        if (used[i] == 0) {
            total += tickets[i].price;
        }
    }

    cout << total << endl;
    return 0;
}
