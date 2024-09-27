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
        for (int j = 0; j < passenger[i]; ++j) {
            int c;
            cin >> c;
            country[i].insert(c);
        }
    }

    vector<set<int>> union_country(n);
    set<int> current_countries;

    for (int i = 0; i < n; ++i) {
        current_countries.insert(country[i].begin(), country[i].end());
        union_country[i] = current_countries;

        for (int j = i - 1; j >= 0 && time[i] - time[j] < 86400; --j) {
            for (int c : country[j]) {
                current_countries.insert(c);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << union_country[i].size() << " ";
    }
    cout << endl;

    return 0;
}
