#include<bits/stdc++.h>
using namespace std;

struct State {
    vector<int> row1;
    vector<int> row2;
    vector<int> row3;
    int steps;
};

int main(){
    int n;
    cin>>n;
    const int infty=1000;
    const int max_steps=100;
    // Initial state
    State initial;
    initial.steps=0;
    initial.row1.resize(2*n);
    for(int i=0;i<n;i++){
        initial.row1[2*i]=i+1;
        initial.row1[2*i+1]=i+1;
    }
    initial.row2.assign(2*n, infty);
    initial.row3.assign(2*n, infty);
    // Goal state
    vector<int> goal_row1(2*n, infty);
    vector<int> goal_row2(2*n, infty);
    vector<int> goal_row3(2*n);
    for(int i=0;i<n;i++){
        goal_row3[2*i]=i+1;
        goal_row3[2*i+1]=i+1;
    }
    // BFS
    queue<State> q;
    q.push(initial);
    // Use a hash set
    auto hash_state = [&](const State& s) -> string{
        string key="";
        for(auto num:s.row1) key += to_string(num)+",";
        key += "|";
        for(auto num:s.row2) key += to_string(num)+",";
        key += "|";
        for(auto num:s.row3) key += to_string(num)+",";
        return key;
    };
    unordered_set<string> visited;
    visited.insert(hash_state(initial));
    while(!q.empty()){
        State current = q.front(); q.pop();
        // Check goal
        if(current.row1 == goal_row1 && current.row2 == goal_row2 && current.row3 == goal_row3){
            cout<<current.steps;
            return 0;
        }
        if(current.steps >= max_steps) continue;
        // Possible actions: move from one row to another
        vector<pair<int, int>> actions = { {1,2},{1,3},{2,1},{2,3},{3,1},{3,2} };
        for(auto &[from, to] : actions){
            // Check if 'from' row has a movable item
            vector<int> src, dst, other1;
            if(from ==1){ src = current.row1; }
            else if(from ==2){ src = current.row2; }
            else { src = current.row3; }
            if(src[0]==infty) continue;
            // Perform move
            State next = current;
            // Move from 'from' to 'to'
            // Remove first from 'from'
            if(from ==1){ next.row1.erase(next.row1.begin()); next.row1.push_back(infty); }
            else if(from ==2){ next.row2.erase(next.row2.begin()); next.row2.push_back(infty); }
            else { next.row3.erase(next.row3.begin()); next.row3.push_back(infty); }
            // Insert into 'to'
            if(to ==1){ 
                next.row1.insert(next.row1.begin(), src[0]); 
                next.row1.pop_back(); 
            }
            else if(to ==2){ 
                next.row2.insert(next.row2.begin(), src[0]); 
                next.row2.pop_back(); 
            }
            else { 
                next.row3.insert(next.row3.begin(), src[0]); 
                next.row3.pop_back(); 
            }
            next.steps +=1;
            // Check visited
            string key = hash_state(next);
            if(!visited.count(key)){
                visited.insert(key);
                q.push(next);
            }
        }
    }
    // If not found
    cout<<-1;
}