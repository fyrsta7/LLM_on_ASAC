#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int M, N;
    cin >> M >> N;
    vector<int> words(N);
    for(auto &x: words) cin >> x;
    deque<int> cache;
    unordered_set<int> s;
    for(int i=0;i<M;i++) cache.push_back(-1);
    int seeks=0;
    for(int i=0;i<N;i++){
        int word = words[i];
        if(word == -1){
            // assuming words can be -1, treat as normal
        }
        if(s.find(word)!=s.end()){
            // hit, do nothing
        }
        else{
            // seek
            seeks++;
            int removed = cache.front();
            cache.pop_front();
            if(removed != -1){
                s.erase(removed);
            }
            cache.push_back(word);
            s.insert(word);
        }
    }
    cout << seeks;
}