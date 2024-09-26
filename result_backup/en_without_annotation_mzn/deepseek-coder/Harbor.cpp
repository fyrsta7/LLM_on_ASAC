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

    for (int i = 0; i < n; ++i) {
        set<int> current_countries = country[i];
        for (int j = 0; j < i; ++j) {
            if (time[i] - time[j] < 86400) {
                current_countries.insert(country[j].begin(), country[j].end());
            }
        }
        union_country[i] = current_countries;
    }

    for (int i = 0; i < n; ++i) {
        cout << union_country[i].size() << " ";
    }
    cout << endl;

    return 0;
}
