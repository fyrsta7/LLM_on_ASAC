#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> coeffs(n+1);
    for(int &c: coeffs) cin >> c;
    string res = "";
    bool first = true;
    for(int i=0;i<=n;i++){
        int degree = n-i;
        int c = coeffs[i];
        if(c == 0) continue;
        if(first){
            if(c < 0){
                res += "-";
            }
        }
        else{
            if(c > 0){
                res += "+";
            }
            else{
                res += "-";
            }
        }
        int abs_c = abs(c);
        if(degree >0){
            if(abs_c !=1){
                res += to_string(abs_c);
            }
        }
        if(degree >1){
            res += "x^" + to_string(degree);
        }
        else if(degree ==1){
            res += "x";
        }
        else{
            if(degree ==0){
                res += to_string(abs_c);
            }
        }
        first = false;
    }
    cout << res;
}