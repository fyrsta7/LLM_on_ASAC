#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

const int MOD = 10007;

struct Node {
    int ways0, ways1;
    Node() : ways0(0), ways1(0) {}
    Node(int w0, int w1) : ways0(w0), ways1(w1) {}
};

Node combine(const Node& left, const Node& right, char op) {
    Node res;
    if (op == '+') {
        res.ways0 = (left.ways0 * right.ways0) % MOD;
        res.ways1 = (left.ways1 * right.ways0 + left.ways1 * right.ways1 + left.ways0 * right.ways1) % MOD;
    } else if (op == '*') {
        res.ways0 = (left.ways0 * right.ways0 + left.ways0 * right.ways1 + left.ways1 * right.ways0) % MOD;
        res.ways1 = (left.ways1 * right.ways1) % MOD;
    }
    return res;
}

Node evaluate(const string& expr, int& idx) {
    stack<Node> operands;
    stack<char> operators;
    while (idx < expr.size() && expr[idx] != ')') {
        if (expr[idx] == '(') {
            idx++;
            operands.push(evaluate(expr, idx));
        } else if (expr[idx] == '+' || expr[idx] == '*') {
            operators.push(expr[idx]);
        } else {
            operands.push(Node(1, 1)); // _ can be 0 or 1
        }
        idx++;
        if (!operators.empty() && (operators.top() == '*' || operands.size() == 2)) {
            Node right = operands.top(); operands.pop();
            Node left = operands.top(); operands.pop();
            operands.push(combine(left, right, operators.top()));
            operators.pop();
        }
    }
    while (!operators.empty()) {
        Node right = operands.top(); operands.pop();
        Node left = operands.top(); operands.pop();
        operands.push(combine(left, right, operators.top()));
        operators.pop();
    }
    return operands.top();
}

int main() {
    int L;
    string expr;
    cin >> L >> expr;
    int idx = 0;
    Node result = evaluate(expr, idx);
    cout << result.ways0 << endl;
    return 0;
}
