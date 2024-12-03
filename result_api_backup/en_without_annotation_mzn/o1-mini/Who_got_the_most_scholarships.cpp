#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<string> name(n);
    vector<int> score(n), review(n), paper(n);
    vector<string> if_leader(n), if_west(n);
    for(int i=0;i<n;i++) cin>>name[i]>>score[i]>>review[i]>>if_leader[i]>>if_west[i]>>paper[i];
    vector<long long> scholarship(n,0);
    long long total=0;
    long long max_sch=0;
    int idx=-1;
    for(int i=0;i<n;i++){
        long long s=0;
        if(score[i]>80 && paper[i]>=1) s +=8000;
        if(score[i]>85 && review[i]>80) s +=4000;
        if(score[i]>90) s +=2000;
        if(score[i]>85 && if_west[i]=="Y") s +=1000;
        if(review[i]>80 && if_leader[i]=="Y") s +=850;
        scholarship[i]=s;
        total +=s;
        if(s >= max_sch){
            max_sch =s;
            idx=i;
        }
    }
    cout<<name[idx]<<"\n"<<max_sch<<"\n"<<total;
}