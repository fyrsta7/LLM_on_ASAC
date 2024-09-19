#include <iostream>
#include <map>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    map<int, int> cnt;
    int x;
    for(int i = 0; i < n; i++) {
        cin >> x;
        cnt[x]++;
    }
    for(auto it = cnt.begin(); it != cnt.end(); ++it){
        cout << it->first << " " << it->second << "\n";
    }
}