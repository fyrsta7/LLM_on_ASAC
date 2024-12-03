#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int time[7][2];
    for(int i=0;i<7;i++) {
        cin >> time[i][0] >> time[i][1];
    }
    int count_unhappy =0;
    int max_sum = INT_MIN;
    for(int i=0;i<7;i++){
        int s = time[i][0] + time[i][1];
        if(s >8) count_unhappy++;
        if(s > max_sum) max_sum = s;
    }
    if(count_unhappy ==0){
        cout << "0";
    }
    else{
        cout << max_sum;
    }
}