#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> expr_str(n);
    for (int i = 0; i < n; ++i) {
        cin >> expr_str[i];
    }

    vector<int> expr_int(n);
    for (int i = 0; i < n; ++i) {
        if (expr_str[i] == "+") expr_int[i] = 1;
        else if (expr_str[i] == "*") expr_int[i] = 2;
        else if (expr_str[i] == "(") expr_int[i] = 3;
        else if (expr_str[i] == ")") expr_int[i] = 4;
    }

    int symbol_count = count_if(expr_int.begin(), expr_int.end(), [](int x) { return x == 1 || x == 2; });
    int num_count = symbol_count + 1;
    int max_plans = 1 << num_count;

    vector<vector<int>> number(max_plans, vector<int>(num_count));
    for (int i = 0; i < max_plans; ++i) {
        for (int j = 0; j < num_count; ++j) {
            number[i][j] = (i >> j) & 1;
        }
    }

    int plan_num = 0;
    for (int i = 0; i < max_plans; ++i) {
        bool unique = true;
        for (int j = 0; j < i; ++j) {
            if (number[i] == number[j]) {
                unique = false;
                break;
            }
        }
        if (unique) {
            ++plan_num;
        }
    }

    vector<int> symbol_loc(symbol_count);
    int idx = 0;
    for (int i = 0; i < n; ++i) {
        if (expr_int[i] == 1 || expr_int[i] == 2) {
            symbol_loc[idx++] = i;
        }
    }

    vector<int> priority(symbol_count);
    for (int i = 0; i < symbol_count; ++i) {
        priority[i] = i + 1;
    }

    vector<vector<vector<int>>> state(max_plans, vector<vector<int>>(symbol_count + 1, vector<int>(num_count)));
    for (int i = 0; i < max_plans; ++i) {
        for (int j = 0; j < num_count; ++j) {
            state[i][0][j] = number[i][j];
        }
    }

    for (int i = 0; i < max_plans; ++i) {
        for (int j = 0; j < symbol_count; ++j) {
            for (int t = 0; t < symbol_count; ++t) {
                if (priority[t] == j + 1) {
                    int t_idx = symbol_loc[t];
                    if (expr_int[t_idx] == 1) {
                        state[i][j + 1][t_idx] = (state[i][j][t_idx] || state[i][j][t_idx + 1]);
                        state[i][j + 1][t_idx + 1] = (state[i][j][t_idx] || state[i][j][t_idx + 1]);
                    } else {
                        state[i][j + 1][t_idx] = (state[i][j][t_idx] && state[i][j][t_idx + 1]);
                        state[i][j + 1][t_idx + 1] = (state[i][j][t_idx] && state[i][j][t_idx + 1]);
                    }
                    for (int l = 0; l < num_count; ++l) {
                        if (l != t_idx && l != t_idx + 1) {
                            state[i][j + 1][l] = state[i][j][l];
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < max_plans; ++i) {
        int sum = 0;
        for (int t = 0; t < num_count; ++t) {
            sum += state[i][symbol_count][t];
        }
        if (sum == 0) {
            ++plan_num;
        }
    }

    cout << plan_num % 10007 << endl;
    return 0;
}