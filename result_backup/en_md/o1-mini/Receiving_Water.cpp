#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> w(n);
    for(int &x : w) cin >> x;
    priority_queue<int, vector<int>, std::greater<int>> pq;
    int max_time = 0;
    for(int i=0;i<m && i<n;i++){
        pq.push(w[i]);
        if(w[i] > max_time) max_time = w[i];
    }
    for(int i=m;i<n;i++){
        int t = pq.top();
        pq.pop();
        int finish = t + w[i];
        pq.push(finish);
        if(finish > max_time) max_time = finish;
    }
    cout << max_time;
}