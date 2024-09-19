#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> transport(n), price(n), time(n);
    for (int i = 0; i < n; ++i) {
        cin >> transport[i] >> price[i] >> time[i];
    }

    long long totalCost = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> tickets;

    for (int i = 0; i < n; ++i) {
        if (transport[i] == 0) {
            totalCost += price[i];
            tickets.push({time[i], price[i]});
        } else {
            while (!tickets.empty() && tickets.top().first + 45 < time[i]) {
                tickets.pop();
            }
            if (!tickets.empty() && tickets.top().second >= price[i]) {
                tickets.pop();
            } else {
                totalCost += price[i];
            }
        }
    }

    cout << totalCost << endl;
    return 0;
}
