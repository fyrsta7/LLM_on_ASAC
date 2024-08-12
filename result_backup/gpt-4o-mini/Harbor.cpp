#include <iostream>
#include <vector>
#include <unordered_set>
#include <deque>

using namespace std;

struct Ship {
    int time;
    int passengers;
    vector<int> nationalities;
};

int main() {
    int n;
    cin >> n;
    
    vector<Ship> ships(n);
    for (int i = 0; i < n; i++) {
        cin >> ships[i].time >> ships[i].passengers;
        ships[i].nationalities.resize(ships[i].passengers);
        for (int j = 0; j < ships[i].passengers; j++) {
            cin >> ships[i].nationalities[j];
        }
    }
    
    unordered_set<int> uniqueCountries;
    deque<int> activeShips; // Holds indices of ships within the last 24 hours
    vector<int> results(n);
    
    for (int i = 0; i < n; i++) {
        // Remove ships older than 24 hours
        while (!activeShips.empty() && ships[activeShips.front()].time <= ships[i].time - 86400) {
            activeShips.pop_front();
        }

        // Add the current ship to the list of active ships
        activeShips.push_back(i);

        // Clear set and count unique nationalities
        uniqueCountries.clear();
        for (int index : activeShips) {
            for (int nationality : ships[index].nationalities) {
                uniqueCountries.insert(nationality);
            }
        }

        // Store result for the current ship
        results[i] = uniqueCountries.size();
    }
    
    for (int res : results) {
        cout << res << endl;
    }

    return 0;
}