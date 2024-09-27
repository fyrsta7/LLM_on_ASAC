#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool valid(int order, const vector<pair<int, int>>& cards, const vector<int>& card_set) {
    int n = card_set.size();
    if (n == 2) {
        bool found01 = false, found02 = false;
        for (int i : card_set) {
            if (cards[i].first == 0 && cards[i].second == 1) found01 = true;
            if (cards[i].first == 0 && cards[i].second == 2) found02 = true;
        }
        if (found01 && found02) return true;
    }
    if (n == 4) {
        unordered_map<int, int> count;
        for (int i : card_set) count[cards[i].first]++;
        for (auto& p : count) if (p.second == 4) return true;
    }
    if (n == 1 || n == 2 || n == 3) {
        unordered_map<int, int> count;
        for (int i : card_set) count[cards[i].first]++;
        for (auto& p : count) if (p.second == n) return true;
    }
    if (n == 4) {
        unordered_map<int, int> count;
        for (int i : card_set) count[cards[i].first]++;
        for (auto& p : count) if (p.second == 3) return true;
    }
    if (n == 5) {
        unordered_map<int, int> count;
        for (int i : card_set) count[cards[i].first]++;
        bool found3 = false, found2 = false;
        for (auto& p : count) {
            if (p.second == 3) found3 = true;
            if (p.second == 2) found2 = true;
        }
        if (found3 && found2) return true;
    }
    if (n >= 5) {
        vector<int> ranks;
        for (int i : card_set) ranks.push_back(cards[i].first);
        sort(ranks.begin(), ranks.end());
        for (int j = 3; j <= 13; ++j) {
            bool straight = true;
            for (int k = 0; k < n; ++k) {
                if (ranks[k] != k + j - 1) {
                    straight = false;
                    break;
                }
            }
            if (straight) return true;
        }
    }
    if (n >= 6 && n % 2 == 0) {
        vector<int> ranks;
        for (int i : card_set) ranks.push_back(cards[i].first);
        sort(ranks.begin(), ranks.end());
        for (int j = 3; j <= 13; ++j) {
            bool pairs = true;
            for (int k = 0; k < n / 2; ++k) {
                if (count(ranks.begin(), ranks.end(), k + j - 1) != 2) {
                    pairs = false;
                    break;
                }
            }
            if (pairs) return true;
        }
    }
    if (n >= 6 && n % 3 == 0) {
        vector<int> ranks;
        for (int i : card_set) ranks.push_back(cards[i].first);
        sort(ranks.begin(), ranks.end());
        for (int j = 3; j <= 13; ++j) {
            bool triples = true;
            for (int k = 0; k < n / 3; ++k) {
                if (count(ranks.begin(), ranks.end(), k + j - 1) != 3) {
                    triples = false;
                    break;
                }
            }
            if (triples) return true;
        }
    }
    if (n == 6) {
        unordered_map<int, int> count;
        for (int i : card_set) count[cards[i].first]++;
        for (auto& p : count) if (p.second == 4) return true;
    }
    if (n == 8) {
        unordered_map<int, int> count;
        for (int i : card_set) count[cards[i].first]++;
        bool found4 = false, found2_1 = false, found2_2 = false;
        for (auto& p : count) {
            if (p.second == 4) found4 = true;
            if (p.second == 2) {
                if (!found2_1) found2_1 = true;
                else found2_2 = true;
            }
        }
        if (found4 && found2_1 && found2_2) return true;
    }
    return false;
}

int main() {
    int T, n;
    cin >> T >> n;
    vector<vector<pair<int, int>>> cards(T, vector<pair<int, int>>(n));
    for (int i = 0; i < T; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> cards[i][j].first >> cards[i][j].second;
        }
    }

    vector<int> ans(T);
    for (int i = 0; i < T; ++i) {
        vector<vector<int>> card_order(n);
        for (int j = 0; j < n; ++j) {
            card_order[j].push_back(j);
        }
        for (int j = 0; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                if (valid(i, cards[i], {j, k})) {
                    card_order[j].push_back(k);
                    card_order[k].push_back(j);
                }
            }
        }
        for (int j = 0; j < n; ++j) {
            if (card_order[j].size() > 1) {
                ans[i]++;
            }
        }
    }

    for (int i = 0; i < T; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}
