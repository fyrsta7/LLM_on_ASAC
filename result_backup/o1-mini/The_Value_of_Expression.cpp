#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef long long ll;
const int MOD = 10007;

struct Counts {
    int c0;
    int c1;
};

int precedence(char op){
    if(op == '*') return 2;
    if(op == '+') return 1;
    return 0;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int L;
    cin >> L;
    string s;
    cin >> s;
    vector<char> op_stack;
    vector<Counts> operand_stack;
    for(char ch : s){
        if(ch == '+' || ch == '*'){
            while(!op_stack.empty() && op_stack.back() != '(' && precedence(op_stack.back()) >= precedence(ch)){
                char oper = op_stack.back();
                op_stack.pop_back();
                Counts right, left;
                if(!operand_stack.empty()){
                    right = operand_stack.back();
                    operand_stack.pop_back();
                }
                else{
                    right.c0 = 1;
                    right.c1 = 1;
                }
                if(!operand_stack.empty()){
                    left = operand_stack.back();
                    operand_stack.pop_back();
                }
                else{
                    left.c0 = 1;
                    left.c1 = 1;
                }
                Counts res;
                if(oper == '*'){
                    res.c0 = (int)(((ll)left.c0 * right.c0) % MOD + ((ll)left.c0 * right.c1) % MOD + ((ll)left.c1 * right.c0) % MOD) % MOD;
                    res.c1 = ((ll)left.c1 * right.c1) % MOD;
                }
                else { // oper == '+'
                    res.c0 = ((ll)left.c0 * right.c0) % MOD;
                    res.c1 = (((ll)left.c0 * right.c1) % MOD + ((ll)left.c1 * right.c0) % MOD + ((ll)left.c1 * right.c1) % MOD) % MOD;
                }
                operand_stack.push_back(res);
            }
            op_stack.push_back(ch);
        }
        else if(ch == '('){
            op_stack.push_back(ch);
        }
        else if(ch == ')'){
            while(!op_stack.empty() && op_stack.back() != '('){
                char oper = op_stack.back();
                op_stack.pop_back();
                Counts right, left;
                if(!operand_stack.empty()){
                    right = operand_stack.back();
                    operand_stack.pop_back();
                }
                else{
                    right.c0 =1;
                    right.c1 =1;
                }
                if(!operand_stack.empty()){
                    left = operand_stack.back();
                    operand_stack.pop_back();
                }
                else{
                    left.c0 =1;
                    left.c1 =1;
                }
                Counts res;
                if(oper == '*'){
                    res.c0 = (int)(((ll)left.c0 * right.c0) % MOD + ((ll)left.c0 * right.c1) % MOD + ((ll)left.c1 * right.c0) % MOD) % MOD;
                    res.c1 = ((ll)left.c1 * right.c1) % MOD;
                }
                else { // oper == '+'
                    res.c0 = ((ll)left.c0 * right.c0) % MOD;
                    res.c1 = (((ll)left.c0 * right.c1) % MOD + ((ll)left.c1 * right.c0) % MOD + ((ll)left.c1 * right.c1) % MOD) % MOD;
                }
                operand_stack.push_back(res);
            }
            if(!op_stack.empty() && op_stack.back() == '('){
                op_stack.pop_back();
            }
        }
    }
    while(!op_stack.empty()){
        char oper = op_stack.back();
        op_stack.pop_back();
        Counts right, left;
        if(!operand_stack.empty()){
            right = operand_stack.back();
            operand_stack.pop_back();
        }
        else{
            right.c0 =1;
            right.c1 =1;
        }
        if(!operand_stack.empty()){
            left = operand_stack.back();
            operand_stack.pop_back();
        }
        else{
            left.c0 =1;
            left.c1 =1;
        }
        Counts res;
        if(oper == '*'){
            res.c0 = (int)(((ll)left.c0 * right.c0) % MOD + ((ll)left.c0 * right.c1) % MOD + ((ll)left.c1 * right.c0) % MOD) % MOD;
            res.c1 = ((ll)left.c1 * right.c1) % MOD;
        }
        else { // oper == '+'
            res.c0 = ((ll)left.c0 * right.c0) % MOD;
            res.c1 = (((ll)left.c0 * right.c1) % MOD + ((ll)left.c1 * right.c0) % MOD + ((ll)left.c1 * right.c1) % MOD) % MOD;
        }
        operand_stack.push_back(res);
    }
    Counts final_counts;
    if(!operand_stack.empty()){
        final_counts = operand_stack.back();
    }
    else{
        final_counts.c0 =1;
        final_counts.c1 =1;
    }
    cout << final_counts.c0 % MOD;
}
