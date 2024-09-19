#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> P(n);
    for(auto &x:P) cin >> x;
    stack<int> S1, S2;
    int input_ptr =0;
    int next_needed =1;
    string ops="";
    while(next_needed <=n){
        if(!S1.empty() && S1.top() == next_needed){
            ops += "b ";
            S1.pop();
            next_needed++;
        }
        else if(!S2.empty() && S2.top() == next_needed){
            ops += "d ";
            S2.pop();
            next_needed++;
        }
        else if(input_ptr <n){
            // Decide to push to S1 or S2
            // To get lex order, prefer 'a'
            // Push to S1
            S1.push(P[input_ptr]);
            ops += "a ";
            input_ptr++;
        }
        else{
            // Cannot perform any operation
            break;
        }
    }
    // After input is exhausted, try to pop remaining
    while(next_needed <=n){
        if(!S1.empty() && S1.top() == next_needed){
            ops += "b ";
            S1.pop();
            next_needed++;
        }
        else if(!S2.empty() && S2.top() == next_needed){
            ops += "d ";
            S2.pop();
            next_needed++;
        }
        else{
            break;
        }
    }
    if(next_needed >n){
        // Remove trailing space
        if(ops.back() == ' ') ops.pop_back();
        cout << ops;
    }
    else{
        cout << "0";
    }
}