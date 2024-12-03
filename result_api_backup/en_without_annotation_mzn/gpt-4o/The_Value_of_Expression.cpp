#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <cmath>

using namespace std;

struct Plan {
    vector<int> number;
    bool operator==(const Plan &other) const {
        return number == other.number;
    }
};

namespace std {
    template <>
    struct hash<Plan> {
        size_t operator()(const Plan &p) const {
            size_t h = 0;
            for (int n : p.number) {
                h = h * 31 + hash<int>()(n);
            }
            return h;
        }
    };
}

bool isOperator(const string &s) {
    return s == "+" || s == "*";
}

bool evaluateExpression(const vector<int> &number, const vector<int> &expr_int, const vector<int> &symbol_loc, const vector<int> &priority) {
    vector<vector<int>> state(symbol_loc.size() + 1, vector<int>(number.size() + 1, 0));
    for (int i = 0; i < number.size(); ++i) {
        state[0][i + 1] = number[i];
    }
    
    for (int j = 0; j < symbol_loc.size(); ++j) {
        int idx = symbol_loc[j] - 1;
        for (int t = 0; t < symbol_loc.size(); ++t) {
            if (priority[t] == j + 1) {
                if (expr_int[idx] == 1) {
                    state[j + 1][idx + 1] = state[j][idx + 1] + state[j][idx + 2] > 0 ? 1 : 0;
                    state[j + 1][idx + 2] = state[j][idx + 1] + state[j][idx + 2] > 0 ? 1 : 0;
                } else {
                    state[j + 1][idx + 1] = state[j][idx + 1] * state[j][idx + 2];
                    state[j + 1][idx + 2] = state[j][idx + 1] * state[j][idx + 2];
                }
                for (int l = 0; l < number.size(); ++l) {
                    if (l != idx && l != idx + 1) {
                        state[j + 1][l + 1] = state[j][l + 1];
                    }
                }
            }
        }
    }

    int sum = accumulate(state[symbol_loc.size()].begin(), state[symbol_loc.size()].end(), 0);
    return sum == 0;
}

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
        else expr_int[i] = 4;
    }

    vector<int> symbol_loc;
    for (int i = 0; i < n; ++i) {
        if (expr_int[i] == 1 || expr_int[i] == 2) {
            symbol_loc.push_back(i + 1);
        }
    }

    int symbol_count = symbol_loc.size();
    int num_count = symbol_count + 1;
    int max_plans = pow(2, num_count);

    unordered_set<Plan> plans;
    for (int i = 0; i < max_plans; ++i) {
        vector<int> number(num_count);
        for (int j = 0; j < num_count; ++j) {
            number[j] = (i >> j) & 1;
        }
        Plan p = {number};
        plans.insert(p);
    }

    vector<int> priority(symbol_count);
    iota(priority.begin(), priority.end(), 1);

    int max_plan_num = 0;
    do {
        for (auto &plan : plans) {
            if (evaluateExpression(plan.number, expr_int, symbol_loc, priority)) {
                max_plan_num++;
            }
        }
    } while (next_permutation(priority.begin(), priority.end()));
    
    int result = max_plan_num % 10007;
    cout << result << endl;

    return 0;
}