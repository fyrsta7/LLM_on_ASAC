#include <iostream>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n, p;
    cin >> n >> p;
    ll a;
    cin >> a;
    ll char_current = a;
    ll score_current = char_current;
    ll max_score = score_current;
    ll current_max = score_current + char_current;
    for(ll i=2;i<=n;i++){
        cin >> a;
        char_current = a > (char_current + a) ? a : (char_current + a);
        ll score_i = current_max;
        if(score_i > max_score) max_score = score_i;
        current_max = (current_max > (score_i + char_current)) ? current_max : (score_i + char_current);
    }
    if(max_score >=0){
        cout << (max_score % p);
    }
    else{
        cout << -( (-max_score) % p);
    }
}