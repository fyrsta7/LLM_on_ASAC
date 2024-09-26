#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <numeric>

using namespace std;

struct Minister {
    int number1;
    int number2;
};

int n, a, b;
vector<Minister> minister;
vector<int> order;
vector<int> number1;
vector<int> number2;
vector<int> money;

int calculateAnswer() {
    int maxMoney = INT_MIN;
    vector<int> prod(n + 1, 1);
    prod[0] = a;

    for (int i = 1; i <= n; ++i) {
        prod[i] = prod[i - 1] * number1[order[i - 1]] / number2[order[i - 1]];
        money[i - 1] = prod[i];
        maxMoney = max(maxMoney, money[i - 1]);
    }

    return maxMoney;
}

int main() {
    cin >> n >> a >> b;
    minister.resize(n);
    money.resize(n);
    order.resize(n);
    number1.resize(n);
    number2.resize(n);

    for (int i = 0; i < n; ++i) {
        cin >> minister[i].number1 >> minister[i].number2;
        number1[i] = minister[i].number1;
        number2[i] = minister[i].number2;
        order[i] = i;
    }

    int answer = INT_MAX;
    
    do {
        answer = min(answer, calculateAnswer());
    } while (next_permutation(order.begin(), order.end()));

    cout << answer << endl;
    return 0;
}