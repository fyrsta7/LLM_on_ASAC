#include <iostream>
using namespace std;

int main(){
    int budget[12];
    for(int i=0;i<12;i++) cin>>budget[i];
    long long S=0;
    long long total_deposit=0;
    for(int i=0;i<12;i++){
        S +=300;
        if(S >= budget[i]){
            S -= budget[i];
            if(S >=100){
                long long deposit = (S /100)*100;
                total_deposit += deposit;
                S -= deposit;
            }
        }
        else{
            cout<<"-"<<(i+1);
            return 0;
        }
    }
    long long money = (total_deposit *12)/10 + S;
    cout<<money;
}