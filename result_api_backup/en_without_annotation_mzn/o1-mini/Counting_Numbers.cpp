#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    vector<int> numbers(n);
    for(auto &x:numbers) cin>>x;
    sort(numbers.begin(), numbers.end());
    vector<pair<int, int>> count_num;
    if(n>0){
        int current = numbers[0];
        int cnt =1;
        for(int i=1;i<n;i++){
            if(numbers[i]==current) cnt++;
            else{
                count_num.emplace_back(current, cnt);
                current = numbers[i];
                cnt=1;
            }
        }
        count_num.emplace_back(current, cnt);
    }
    for(auto &[num, cnt]: count_num){
        cout<<num<<" "<<cnt<<"\n";
    }
}