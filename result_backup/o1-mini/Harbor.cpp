#include <iostream>
#include <vector>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<long long> t(n);
    vector<vector<int>> ships(n);
    // As x_i,j <=1e5
    vector<int> freq(100001, 0);
    int distinct =0;
    for(int i=0;i<n;i++){
        long long ti;
        int ki;
        cin >> ti >> ki;
        t[i] = ti;
        ships[i].reserve(ki);
        for(int j=0;j<ki;j++){
            int x;
            cin >> x;
            ships[i].push_back(x);
            if(freq[x]==0){
                distinct++;
            }
            freq[x]++;
        }
    }
    int front =0;
    for(int i=0;i<n;i++){
        while(front <=i && t[i] - t[front] >=86400){
            for(auto x: ships[front]){
                freq[x]--;
                if(freq[x]==0){
                    distinct--;
                }
            }
            front++;
        }
        cout << distinct << "\n";
    }
}