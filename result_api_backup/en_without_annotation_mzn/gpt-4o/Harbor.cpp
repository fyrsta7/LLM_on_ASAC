```
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct Stop {
    int time;
    int passenger;
    unordered_set<int> country;
};

int main() {
    int n;
    cin >> n;

    vector<Stop> stops(n);
    unordered_set<int> allCountries;
    
    for (int i = 0; i < n; ++i) {
        cin >> stops[i].time >> stops[i].passenger;
        int numCountries;
        cin >> numCountries;
        for (int j = 0; j < numCountries; ++j) {
            int countryId;
            cin >> countryId;
            stops[i].country.insert(countryId);
            allCountries.insert(countryId);
        }
    }

    vector<unordered_set<int>> unionCountry(n);

    for (int i = 0; i < n; ++i) {
        unionCountry[i] = stops[i].country;
        for (int j = 0; j < i; ++j) {
            if (stops[i].time - stops[j].time < 86400) {
                unionCountry[i].insert(stops[j].country.begin(), stops[j].country.end());
            }
        }
    }

    int sum = 0;
    for (const auto &uc : unionCountry) {
        sum += uc.size();
    }

    cout << sum << endl;

    for (const auto& uc : unionCountry) {
        cout << uc.size() << " ";
    }

    return 0;
}
