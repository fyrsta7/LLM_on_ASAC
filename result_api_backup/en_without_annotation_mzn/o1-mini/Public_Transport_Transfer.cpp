#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> ty(n+1), price(n+1), time_(n+1);
    for(int i=1;i<=n;i++) cin >> ty[i];
    for(int i=1;i<=n;i++) cin >> price[i];
    for(int i=1;i<=n;i++) cin >> time_[i];
    vector<bool> used_prev(n+1, false);
    vector<bool> used_current(n+1, false);
    long long total =0;
    for(int i=1;i<=n;i++){
        int take;
        if(ty[i]==0){
            take =i;
        }
        else{
            take =i;
            for(int j=1;j<=i;j++){
                if(j==i || (ty[j]==0 && (time_[i] - time_[j] <=45) && price[j]>=price[i] && used_prev[j])){
                    take =j;
                    break;
                }
            }
        }
        // Update used_current
        for(int j=1;j<=i;j++){
            if(ty[i]==0){
                if(j==i){
                    used_current[j]=true;
                }
                else{
                    if(i>1)
                        used_current[j]=used_prev[j];
                    else
                        used_current[j]=false;
                }
            }
            else{
                if(j==i || j==take){
                    used_current[j]=false;
                }
                else{
                    if(i>1)
                        used_current[j]=used_prev[j];
                    else
                        used_current[j]=false;
                }
            }
        }
        // Update total
        if(ty[i]==0 || take ==i){
            total +=price[i];
        }
        // Prepare for next iteration
        used_prev = used_current;
    }
    cout << total;
}