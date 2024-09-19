#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k, p;
    cin >> n >> k >> p;
    vector<pair<int, int>> inns(n);
    vector<int> color_total(k, 0);
    for(int i=0;i<n;i++){
        cin >> inns[i].first >> inns[i].second;
        color_total[inns[i].first]++;
    }
    ll total_pairs =0;
    for(int c=0;c<k;c++){
        if(color_total[c] >=2){
            total_pairs += (ll)color_total[c] * (color_total[c]-1) /2;
        }
    }
    ll invalid_pairs=0;
    vector<int> color_seg(k, 0);
    for(int i=0;i<n;i++){
        if(inns[i].second > p){
            color_seg[inns[i].first]++;
        }
        else{
            for(int c=0;c<k;c++){
                if(color_seg[c] >=2){
                    invalid_pairs += ((ll)color_seg[c] * (color_seg[c]-1))/2;
                }
                color_seg[c]=0;
            }
        }
    }
    // After loop, check any remaining segment
    for(int c=0;c<k;c++){
        if(color_seg[c] >=2){
            invalid_pairs += ((ll)color_seg[c] * (color_seg[c]-1))/2;
        }
    }
    ll answer = total_pairs - invalid_pairs;
    cout << answer;
}