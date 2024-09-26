#include <iostream>
#include <string>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin>>N;
    string name;
    int average, class_eval, papers;
    char leader, west;
    long long total_sum=0;
    string max_name;
    long long max_amount=-1;
    for(int i=0;i<N;i++){
        cin>>name>>average>>class_eval>>leader>>west>>papers;
        long long sum=0;
        if(average>80 && papers>0) sum +=8000;
        if(average>85 && class_eval>80) sum +=4000;
        if(average>90) sum +=2000;
        if(west=='Y' && average>85) sum +=1000;
        if(leader=='Y' && class_eval>80) sum +=850;
        total_sum += sum;
        if(sum > max_amount){
            max_amount = sum;
            max_name = name;
        }
    }
    cout<<max_name<<"\n"<<max_amount<<"\n"<<total_sum;
}