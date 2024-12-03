#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

int main(){
    long long budget[13];
    for(int i=1;i<=12;i++) cin>>budget[i];
    long long left[13];
    left[0]=0;
    int first_neg=-1;
    for(int i=1;i<=12;i++){
        long long temp = 300 + left[i-1] - budget[i];
        left[i] = temp % 100;
        if(left[i]<0 && first_neg==-1){
            first_neg =i;
        }
    }
    if(first_neg !=-1){
        cout<<"-"<<first_neg;
    }
    else{
        double total=0.0;
        for(int i=1;i<=12;i++) {
            total += ((300 + left[i-1] - budget[i])/100) *100;
        }
        total *=1.2;
        double result = left[12] + total;
        cout<<fixed<<setprecision(1)<<result;
    }
}