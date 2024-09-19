#include <iostream>
#include <vector>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    int k;
    cin >> t >> k;
    const int MAX = 2000;
    vector<vector<int>> C(MAX+1, vector<int>(MAX+1, 0));
    C[0][0] = 1 % k;
    for(int i=1;i<=MAX;i++){
        C[i][0] = 1 % k;
        for(int j=1;j<=i;j++){
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % k;
        }
    }
    vector<vector<int>> sum_(MAX+1, vector<int>(MAX+1, 0));
    for(int i=0;i<=MAX;i++){
        sum_[i][0] = (C[i][0]==0)?1:0;
        for(int j=1;j<=i;j++){
            sum_[i][j] = sum_[i][j-1] + ((C[i][j]==0)?1:0);
        }
    }
    while(t--){
        int n, m;
        cin >> n >> m;
        if(n > MAX) n = MAX;
        if(m > MAX) m = MAX;
        long long total =0;
        for(int i=0;i<=n;i++){
            int p = (m < i) ? m : i;
            total += sum_[i][p];
        }
        cout << total << "\n";
    }
}