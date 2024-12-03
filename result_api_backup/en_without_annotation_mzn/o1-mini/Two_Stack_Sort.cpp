#include<bits/stdc++.h>
using namespace std;

struct State {
    int input_idx;
    int output_idx;
    vector<int> stack1;
    vector<int> stack2;
    string actions;
};

int main(){
    int n;
    cin>>n;
    vector<int> numbers(n);
    for(auto &x:numbers) cin>>x;
    queue<State> q;
    unordered_set<string> visited;
    State start = {0,0, vector<int>(), vector<int>(), ""};
    q.push(start);
    auto hash_state = [&](const State &s) -> string{
        string res = to_string(s.input_idx)+"|"+to_string(s.output_idx)+"|";
        for(auto x:s.stack1) res += to_string(x)+" ";
        res += "|";
        for(auto x:s.stack2) res += to_string(x)+" ";
        return res;
    };
    while(!q.empty()){
        State current = q.front(); q.pop();
        if(current.output_idx == n){
            cout<<current.actions;
            return 0;
        }
        string h = hash_state(current);
        if(visited.find(h)!=visited.end()) continue;
        visited.insert(h);
        // Push to stack1
        if(current.input_idx < n){
            State next = current;
            next.stack1.push_back(numbers[current.input_idx]);
            next.input_idx +=1;
            next.actions += "a";
            q.push(next);
        }
        // Push to stack2
        if(current.input_idx < n){
            State next = current;
            next.stack2.push_back(numbers[current.input_idx]);
            next.input_idx +=1;
            next.actions += "c";
            q.push(next);
        }
        // Pop from stack1
        if(!current.stack1.empty() && current.stack1.back() == current.output_idx+1){
            State next = current;
            int val = next.stack1.back(); next.stack1.pop_back();
            next.output_idx +=1;
            next.actions += "b";
            q.push(next);
        }
        // Pop from stack2
        if(!current.stack2.empty() && current.stack2.back() == current.output_idx+1){
            State next = current;
            int val = next.stack2.back(); next.stack2.pop_back();
            next.output_idx +=1;
            next.actions += "d";
            q.push(next);
        }
    }
    return 0;
}