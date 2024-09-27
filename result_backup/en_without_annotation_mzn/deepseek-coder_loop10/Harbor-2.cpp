#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> time(n);
    vector<int> passenger(n);
    vector<set<int>> country(n);

    for (int i = 0; i < n; ++i) {
        cin >> time[i] >> passenger[i];
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int c;
            cin >> c;
            country[i].insert(c);
        }
    }

    vector<set<int>> union_country(n);
    set<int> all_countries;

    for (int i = 0; i < n; ++i) {
        union_country[i] = country[i];
        all_countries.insert(country[i].begin(), country[i].end());
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (time[i] - time[j] < 86400) {
                union_country[i].insert(union_country[j].begin(), union_country[j].end());
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << union_country[i].size() << " ";
    }

    return 0;
}