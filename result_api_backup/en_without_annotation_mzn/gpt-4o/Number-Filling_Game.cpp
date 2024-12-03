#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int n, m;
vector<vector<vector<int>>> table;
vector<vector<int>> direction;
vector<vector<vector<int>>> track;
vector<int> ans;

vector<int> get_track(const vector<vector<int>>& t, const vector<int>& d) {
    vector<int> tmp(m + n - 1);
    tmp[0] = t[0][0];
    tmp[m + n - 2] = t[n-1][m-1];
    for (int i = 1; i < m + n - 2; ++i) {
        int x = count(d.begin(), d.begin() + i, 0);
        int y = count(d.begin(), d.begin() + i, 1);
        tmp[i] = t[x][y];
    }
    return tmp;
}

bool larger(const vector<int>& d1, const vector<int>& d2) {
    for (int i = 0; i < m + n - 2; ++i) {
        if (d1[i] != d2[i]) {
            return d1[i] > d2[i];
        }
    }
    return false;
}

int main() {
    cin >> n >> m;
    
    int max_mn = 1;
    for (int i = m; i < m + n - 1; ++i) {
        max_mn *= i;
    }
    for (int i = 1; i <= n - 1; ++i) {
        max_mn /= i;
    }
    
    int max_t = pow(2, m * n);
    
    table.resize(max_t, vector<vector<int>>(n, vector<int>(m)));
    direction.resize(max_mn, vector<int>(m + n - 2));
    track.resize(max_t, vector<vector<int>>(max_mn, vector<int>(m + n - 1)));
    ans.resize(max_t);
    
    // Input and logic mimicking MiniZinc setup here...
    // Ensure correct implementation of requirements.
    
    for (int t = 0; t < max_t; ++t) {
        for (int i = 0; i < max_mn; ++i) {
            track[t][i] = get_track(table[t], direction[i]);
        }
    }
    
    for (int t = 0; t < max_t; ++t) {
        bool all_larger = true;
        for (int i = 0; i < max_mn; ++i) {
            for (int j = 0; j < max_mn; ++j) {
                if (i != j) {
                    if (!larger(direction[i], direction[j]) || !larger(track[t][i], track[t][j])) {
                        all_larger = false;
                        break;
                    }
                }
            }
            if (!all_larger) break;
        }
        ans[t] = all_larger ? 1 : 0;
    }
    
    int sum_ans = accumulate(ans.begin(), ans.end(), 0);
    cout << sum_ans << endl;
    return 0;
}