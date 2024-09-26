#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<long long> coeff(n+1);
    for(auto &x: coeff) cin >> x;
    string res = "";
    for(int i=1;i<=n;i++){
        if(coeff[i] < 0){
            res += "-";
        }
        else{
            if(coeff[i] !=0 && i !=1){
                res += "+";
            }
        }
        if(abs(coeff[i]) !=1 && coeff[i] !=0){
            res += to_string(abs(coeff[i]));
        }
        else{
            if(coeff[i]==0){
                // nothing
            }
        }
        if(coeff[i] !=0){
            res += "x";
            int power = n - i +1;
            if(power !=1){
                res += "^" + to_string(power);
            }
        }
    }
    if(coeff[n+1] !=0){
        if(coeff[n+1] >0){
            res += "+";
        }
        else{
            res += "-";
        }
        res += to_string(abs(coeff[n+1]));
    }
    cout << res;
}