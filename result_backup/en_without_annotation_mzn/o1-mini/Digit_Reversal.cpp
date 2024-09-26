#include <bits/stdc++.h>
using namespace std;

int main(){
    long long n;
    cin >> n;
    long long abs_n = abs(n);
    int digits[10] = {0};
    for(int i=0;i<10;i++){
        digits[i] = abs_n %10;
        abs_n /=10;
    }
    string output = "";
    if(n < 0){
        output += "-";
    }
    bool started = false;
    for(int i=9;i>=0;i--){
        if(!started){
            if(digits[i] !=0){
                started = true;
                output += to_string(digits[i]);
            }
        }
        else{
            output += to_string(digits[i]);
        }
    }
    if(!started){
        output = "0";
    }
    cout << output;
}