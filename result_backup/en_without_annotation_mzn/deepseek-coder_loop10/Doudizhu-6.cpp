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
        for (int j = 3; j <= 13; ++j) {
            bool valid_seq = true;
            for (int k = 0; k < n; ++k) {
                bool found = false;
                for (int i : card_set) {
                    if (cards[order][i][0] == k + j - 1) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    valid_seq = false;
                    break;
                }
            }
            if (valid_seq) return true;
        }
    }
    if (n >= 6 && n % 2 == 0) {
        for (int j = 3; j <= 13; ++j) {
            bool valid_seq = true;
            for (int k = 0; k < n / 2; ++k) {
                int count = 0;
                for (int i : card_set) {
                    if (cards[order][i][0] == k + j - 1) count++;
                }
                if (count != 2) {
                    valid_seq = false;
                    break;
                }
            }
            if (valid_seq) return true;
        }
    }
    if (n >= 6 && n % 3 == 0) {
        for (int j = 3; j <= 13; ++j) {
            bool valid_seq = true;
            for (int k = 0; k < n / 3; ++k) {
                int count = 0;
                for (int i : card_set) {
                    if (cards[order][i][0] == k + j - 1) count++;
                }
                if (count != 3) {
                    valid_seq = false;
                    break;
                }
            }
            if (valid_seq) return true;
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
    vector<vector<vector<int>>> cards(T, vector<vector<int>>(n, vector<int>(2)));
    for (int i = 0; i < T; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> cards[i][j][0] >> cards[i][j][1];
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
                if (valid(i, cards, {j, k})) {
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
        cout << ans[i] << endl;
    }

    return 0;
}