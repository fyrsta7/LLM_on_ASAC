#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> random(n);
    for(auto &x: random) cin >> x;
    set<int> s(random.begin(), random.end());
    int num = s.size();
    cout << num << "\n";
    for(auto x: s){
        cout << x << " ";
    }
}