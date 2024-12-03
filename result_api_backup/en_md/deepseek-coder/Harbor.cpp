#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<int, vector<int>>> ships(n);
    for (int i = 0; i < n; ++i) {
        int ti, ki;
        cin >> ti >> ki;
        ships[i].first = ti;
        ships[i].second.resize(ki);
        for (int j = 0; j < ki; ++j) {
            cin >> ships[i].second[j];
        }
    }

    unordered_set<int> countries;
    queue<pair<int, int>> q;
    for (int i = 0; i < n; ++i) {
        int ti = ships[i].first;
        for (int country : ships[i].second) {
            q.push({ti, country});
            countries.insert(country);
        }

        while (!q.empty() && q.front().first <= ti - 86400) {
            countries.erase(q.front().second);
            q.pop();
        }

        cout << countries.size() << '\n';
    }

    return 0;
}
