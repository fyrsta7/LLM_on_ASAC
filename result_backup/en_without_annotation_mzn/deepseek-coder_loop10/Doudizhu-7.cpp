#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool valid(int order, const vector<vector<int>>& cards, const vector<int>& card_set) {
    int n = card_set.size();
    if (n == 2) {
        bool found01 = false, found02 = false;
        for (int i : card_set) {
            if (cards[order][i][0] == 0 && cards[order][i][1] == 1) found01 = true;
            if (cards[order][i][0] == 0 && cards[order][i][1] == 2) found02 = true;
        }
        if (found01 && found02) return true;
    }
    if (n == 4) {
        unordered_map<int, int> count;
        for (int i : card_set) count[cards[order][i][0]]++;
        for (auto& p : count) if (p.second == 4) return true;
    }
    if (n == 1 || n == 2 || n == 3) {
        unordered_map<int, int> count;
        for (int i : card_set) count[cards[order][i][0]]++;
        for (auto& p : count) if (p.second == n) return true;
    }
    if (n == 4) {
        unordered_map<int, int> count;
        for (int i : card_set) count[cards[order][i][0]]++;
        for (auto& p : count) if (p.second == 3) return true;
    }
    if (n == 5) {
        unordered_map<int, int> count;
        for (int i : card_set) count[cards[order][i][0]]++;
        bool found3 = false, found2 = false;
        for (auto& p : count) {
            if (p.second == 3) found3 = true;
            if (p.second == 2) found2 = true;
        }
        if (found3 && found2) return true;
    }
    if (n >= 5) {
        vector<int> ranks;
        for (int i : card_set) ranks.push_back(cards[order][i][0]);
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
        for (int i : card_set) ranks.push_back(cards[order][i][0]);
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
        for (int i : card_set) ranks.push_back(cards[order][i][0]);
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
        for (int i : card_set) count[cards[order][i][0]]++;
        for (auto& p : count) if (p.second == 4) return true;
    }
    if (n == 8) {
        unordered_map<int, int> count;
        for (int i : card_set) count[cards[order][i][0]]++;
        bool found4 = false, found2 = false;
        int four_rank = -1, two_rank1 = -1, two_rank2 = -1;
        for (auto& p : count) {
            if (p.second == 4) {
                found4 = true;
                four_rank = p.first;
            }
            if (p.second == 2) {
                if (two_rank1 == -1) two_rank1 = p.first;
                else two_rank2 = p.first;
            }
        }
        if (found4 && two_rank1 != -1 && two_rank2 != -1 && four_rank != two_rank1 && four_rank != two_rank2 && two_rank1 != two_rank2) return true;
    }
    return false;
}

int main() {
    int T, n;
    cin >> T >> n;
    vector<vector<vector<int>>> cards(T, vector<vector<int>>(n, vector<int>(2)));
    for (int i = 0; i < T; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> cards[i][j][0] >> cards[i][j][1];
        }
    }

    vector<int> ans(T);
    for (int i = 0; i < T; ++i) {
        vector<vector<int>> subsets;
        for (int mask = 0; mask < (1 << n); ++mask) {
            vector<int> subset;
            for (int j = 0; j < n; ++j) {
                if (mask & (1 << j)) subset.push_back(j);
            }
            subsets.push_back(subset);
        }

        int valid_count = 0;
        for (const auto& subset : subsets) {
            if (valid(i, cards, subset)) valid_count++;
        }
        ans[i] = valid_count;
    }

    for (int i = 0; i < T; ++i) {
        cout << ans[i] << endl;
    }

    return 0;
}
