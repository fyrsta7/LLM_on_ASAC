#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k, p;
    cin >> n >> k >> p;
    struct Hotel {
        int type;
        int value;
    };
    vector<Hotel> hotels(n);
    for(int i=0;i<n;i++) cin >> hotels[i].type >> hotels[i].value;
    sort(hotels.begin(), hotels.end(), [&](const Hotel &a, const Hotel &b) -> bool{
        if(a.type != b.type) return a.type < b.type;
        return false;
    });
    ll total_valid =0;
    int i=0;
    while(i<n){
        int current_type = hotels[i].type;
        vector<int> group;
        while(i<n && hotels[i].type == current_type){
            group.push_back(hotels[i].value);
            i++;
        }
        int m = group.size();
        ll total_pairs = (ll)m*(m-1)/2;
        ll invalid =0;
        int cnt=0;
        for(auto val: group){
            if(val > p){
                cnt++;
            }
            else{
                if(cnt >=2){
                    invalid += ((ll)cnt*(cnt-1))/2;
                }
                cnt=0;
            }
        }
        if(cnt >=2){
            invalid += ((ll)cnt*(cnt-1))/2;
        }
        total_valid += (total_pairs - invalid);
    }
    cout << total_valid;
}