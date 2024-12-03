#include <iostream>
using namespace std;

int main(){
    int apple[10];
    for(int i=0;i<10;i++) cin>>apple[i];
    int h;
    cin>>h;
    int num=0;
    int limit = h + 30;
    for(int i=0;i<10;i++) if(apple[i]<=limit) num++;
    cout<<num;
    return 0;
}