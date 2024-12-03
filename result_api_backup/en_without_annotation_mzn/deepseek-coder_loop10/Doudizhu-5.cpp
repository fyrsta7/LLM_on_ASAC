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
        int j = cards[card_set[0]].first;
        for (int i : card_set) {
            if (cards[i].first != j) return false;
        }
        return true;
    }
    if (n == 1 || n == 2 || n == 3) {
        int j = cards[card_set[0]].first;
        for (int i : card_set) {
            if (cards[i].first != j) return false;
        }
        return true;
    }
    if (n == 4) {
        unordered_map<int, int> count;
        for (int i : card_set) {
            count[cards[i].first]++;
        }
        for (auto& p : count) {
            if (p.second == 3) return true;
        }
    }
    if (n == 5) {
        unordered_map<int, int> count;
        for (int i : card_set) {
            count[cards[i].first]++;
        }
        bool found3 = false, found2 = false;
        for (auto& p : count) {
            if (p.second == 3) found3 = true;
            if (p.second == 2) found2 = true;
        }
        return found3 && found2;
    }
    if (n >= 5) {
        for (int j = 3; j <= 13; ++j) {
            bool valid_seq = true;
            for (int k = 0; k < n; ++k) {
                bool found = false;
                for (int i : card_set) {
                    if (cards[i].first == k + j - 1) {
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
                    if (cards[i].first == k + j - 1) {
                        count++;
                    }
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
                    if (cards[i].first == k + j - 1) {
                        count++;
                    }
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
        for (int i : card_set) {
            count[cards[i].first]++;
        }
        for (auto& p : count) {
            if (p.second == 4) return true;
        }
    }
    if (n == 8) {
        unordered_map<int, int> count;
        for (int i : card_set) {
            count[cards[i].first]++;
        }
        int j = -1, l = -1, p = -1;
        for (auto& pair : count) {
            if (pair.second == 4) j = pair.first;
            if (pair.second == 2) {
                if (l == -1) l = pair.first;
                else p = pair.first;
            }
        }
        return j != -1 && l != -1 && p != -1 && j != l && j != p && l != p;
    }
    return n == 0;
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
            if (valid(i, cards[i], card_order[j])) {
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
