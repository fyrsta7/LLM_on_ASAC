#include <iostream>
using namespace std;

int main(){
    int apples[10];
    for(int i=0;i<10;i++) cin>>apples[i];
    int h_max;
    cin>>h_max;
    int limit = h_max + 30;
    int count=0;
    for(int i=0;i<10;i++) if(apples[i] <= limit) count++;
    cout<<count;
    return 0;
}