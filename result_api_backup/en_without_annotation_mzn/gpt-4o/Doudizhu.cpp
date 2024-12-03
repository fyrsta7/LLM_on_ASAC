#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Card {
    int rank;
    int suit;
};

int T, n;
vector<vector<Card>> cards;

bool is_valid(int order, set<int>& card_set) {
    int size = card_set.size();
    vector<int> counts(14, 0);

    for (auto i : card_set) {
        counts[cards[order][i].rank]++;
    }

    if (size == 2) {
        if ((counts[1] == 1 && counts[2] == 1) ||
            (counts[1] == 2 || counts[2] == 2 || counts[3] == 2 || counts[4] == 2 || counts[5] == 2 || counts[6] == 2 ||
             counts[7] == 2 || counts[8] == 2 || counts[9] == 2 || counts[10] == 2 || counts[11] == 2 || counts[12] == 2 || counts[13] == 2)) {
            return true;
        }
    }

    if (size == 1 ||
        (size == 3 && counts[1] == 3 || counts[2] == 3 || counts[3] == 3 || counts[4] == 3 || counts[5] == 3 || counts[6] == 3 ||
         counts[7] == 3 || counts[8] == 3 || counts[9] == 3 || counts[10] == 3 || counts[11] == 3 || counts[12] == 3 || counts[13] == 3)) {
        return true;
    }

    if (size == 4) {
        for (int j = 1; j <= 13; j++) {
            if (counts[j] == 4) {
                return true;
            }
        }
    }

    if (size == 5) {
        for (int j = 1; j <= 13; j++) {
            for (int l = 1; l <= 13; l++) {
                if (j != l && counts[j] == 3 && counts[l] == 2) {
                    return true;
                }
            }
        }
    }

    if (size >= 5 && size <= 13) {
        for (int j = 3; j <= 13 - size + 1; j++) {
            bool valid = true;
            for (int k = 0; k < size; k++) {
                if (counts[j + k] != 1) {
                    valid = false;
                    break;
                }
            }
            if (valid) return true;
        }
    }

    if (size >= 6 && size <= 12 && size % 2 == 0) {
        for (int j = 3; j <= 13 - size / 2 + 1; j++) {
            bool valid = true;
            for (int k = 0; k < size / 2; k++) {
                if (counts[j + k] != 2) {
                    valid = false;
                    break;
                }
            }
            if (valid) return true;
        }
    }

    if (size >= 6 && size <= 18 && size % 3 == 0) {
        for (int j = 3; j <= 13 - size / 3 + 1; j++) {
            bool valid = true;
            for (int k = 0; k < size / 3; k++) {
                if (counts[j + k] != 3) {
                    valid = false;
                    break;
                }
            }
            if (valid) return true;
        }
    }

    if (size == 6) {
        for (int j = 1; j <= 13; j++) {
            if (counts[j] == 4) {
                return true;
            }
        }
    }

    if (size == 8) {
        for (int j = 1; j <= 13; j++) {
            for (int l = 1; l <= 13; l++) {
                for (int p = 1; p <= 13; p++) {
                    if (j != l && j != p && l != p &&
                        counts[j] == 4 && counts[l] == 2 && counts[p] == 2) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

int main() {
    cin >> T >> n;
    cards.resize(T, vector<Card>(n));

    for (int t = 0; t < T; ++ t) {
        for (int i = 0; i < n; ++i) {
            cin >> cards[t][i].rank >> cards[t][i].suit;
        }
    }

    vector<int> ans(T);

    for (int t = 0; t < T; ++t) {
        int valid_count = 0;

        for (int i = 0; i < (1 << n); ++i) {
            set<int> card_set;
            for (int j = 0; j < n; ++j)
                if (i & (1 << j)) card_set.insert(j);

            if (is_valid(t, card_set))
                valid_count++;
        }

        ans[t] = valid_count;
    }

    for (int t = 0; t < T; ++t) {
        cout << ans[t] << endl;
    }

    return 0;
}