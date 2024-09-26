#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int minPlays(vector<pair<int, int>>& cards) {
    unordered_map<int, int> count; // Count of cards by rank
    int jokers = 0; // Count of jokers
    for (const auto& card : cards) {
        if (card.first == 0) { // Joker
            jokers++;
        } else {
            count[card.first]++;
        }
    }

    int pairs = 0, singles = 0, straights = 0;
    
    // Process pairs and singles
    for (auto& entry : count) {
        int rankCount = entry.second;
        pairs += rankCount / 2; // Each pair makes one pair
        singles += rankCount % 2; // Remaining cards are singles
    }

    // Each straight requires 5 consecutive cards, use greedy approach
    vector<int> ranks;
    for (auto& entry : count) {
        ranks.push_back(entry.first);
    }
    sort(ranks.begin(), ranks.end());

    int straightCount = 0;
    for (int i = 0; i <= ranks.size() - 5; i++) {
        int length = 1;
        for (int j = i + 1; j < ranks.size(); j++) {
            if (ranks[j] == ranks[j - 1] + 1) {
                length++;
                if (length == 5) {
                    straightCount++;
                    // Restart searching after the end of the straight
                    i = j - 4;
                    break;
                }
            } else {
                length = 1;
            }
        }
    }

    // Combine the counts, adding jokers to make plays easier
    int totalPlays = 0;
    // Use jokers to make pairs or singles, then use straight if any available
    totalPlays += singles - min(singles, jokers); // Play singles using jokers
    totalPlays += pairs; // Add pairs
    totalPlays += straightCount; // Add straights

    int remainingJokers = jokers - min(jokers, singles);
    totalPlays += remainingJokers; // Any leftover jokers can be played as single

    return totalPlays;
}

int main() {
    int T, n;
    cin >> T >> n;
    while (T--) {
        vector<pair<int, int>> cards(n);
        for (int i = 0; i < n; i++) {
            cin >> cards[i].first >> cards[i].second;
        }
        cout << minPlays(cards) << endl;
    }
    return 0;
}