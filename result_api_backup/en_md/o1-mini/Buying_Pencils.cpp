#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int n;
    cin>>n;
    int a, b;
    int min_cost = INT32_MAX;
    for(int i=0;i<3;i++){
        cin>>a>>b;
        int k = (n + a -1)/a;
        long long cost = (long long)k * b;
        if(cost < min_cost){
            min_cost = cost;
        }
    }
    cout<<min_cost;
}