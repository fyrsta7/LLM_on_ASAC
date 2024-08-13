#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int calculate_min_draws(vector<pair<int, int>>& cards) {
    unordered_map<int, int> rank_count;
    for (auto& card : cards) {
        rank_count[card.first]++;
    }

    vector<int> counts;
    for (auto& entry : rank_count) {
        counts.push_back(entry.second);
    }

    sort(counts.rbegin(), counts.rend());

    int remaining_cards = cards.size();
    int draw_count = 0;
    while (remaining_cards > 0) {
        auto it = counts.begin();
        while (it != counts.end() && *it > 0) {
            (*it)--;
            remaining_cards--;
            it++;
        }
        draw_count++;
    }

    return draw_count;
}

int main() {
    int T, n;
    cin >> T >> n;

    for (int i = 0; i < T; i++) {
        vector<pair<int, int>> cards(n);
        for (int j = 0; j < n; j++) {
            cin >> cards[j].first >> cards[j].second;
        }
        cout << calculate_min_draws(cards) << endl;
    }

    return 0;
}