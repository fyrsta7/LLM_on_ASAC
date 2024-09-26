#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> X(n+1), Y(n+1);
    for(int i=1;i<=n;i++) cin >> X[i];
    for(int i=1;i<=n;i++) cin >> Y[i];
    struct Tube{
        int t;
        int l;
        int r;
    };
    vector<Tube> tubes(k);
    for(int i=0;i<k;i++) cin >> tubes[i].t >> tubes[i].l >> tubes[i].r;
    sort(tubes.begin(), tubes.end(), [&](const Tube &a, const Tube &b) -> bool{
        return a.t < b.t;
    });
    // bird[0] =1
    ll sum_tap=0;
    int pass_tube=0;
    ll bird_prev =1;
    int tube_ptr=0;
    for(int i=1;i<=n;i++){
        bool is_tube = false;
        int l=0, r=0;
        if(tube_ptr <k && tubes[tube_ptr].t ==i){
            is_tube=true;
            l = tubes[tube_ptr].l;
            r = tubes[tube_ptr].r;
        }
        ll tap=0;
        ll bird=0;
        if(is_tube){
            // Try tap=0
            ll bird_try = min((ll)(bird_prev - Y[i]), (ll)m);
            if(bird_try > l && bird_try < r && bird_try >=1){
                tap=0;
                bird=bird_try;
                pass_tube++;
            }
            else{
                // Need to find tap >=1 such that min(bird_prev + X[i]*tap, m) > l and < r
                if(X[i]==0){
                    // Can't increase, so can't pass
                    // Set tap=0
                    bird = min((ll)(bird_prev - Y[i]), (ll)m);
                    if(bird >=1){
                        tap=0;
                    }
                    else{
                        // Impossible to set tap to make bird >=1
                        // Choose tap=0
                        tap=0;
                        bird = 1;
                    }
                }
                else{
                    // Find smallest tap >=1 such that bird_prev + X[i]*tap > l and < r
                    ll min_tap = max((ll)1, (ll)ceil((double)(l+1 - bird_prev)/X[i]));
                    ll max_tap = (r-1 - bird_prev)/X[i];
                    if(bird_prev + (ll)X[i]*min_tap > l && bird_prev + (ll)X[i]*min_tap < r){
                        tap = min_tap;
                        bird = min(bird_prev + (ll)X[i]*tap, (ll)m);
                        pass_tube++;
                    }
                    else{
                        // Check if any tap makes bird <=m and >l and <r
                        bool found=false;
                        for(ll t = min_tap; t <= max_tap && t<= (ll)m; t++){
                            ll temp = min(bird_prev + X[i]*t, (ll)m);
                            if(temp > l && temp < r){
                                tap = t;
                                bird = temp;
                                pass_tube++;
                                found=true;
                                break;
                            }
                        }
                        if(!found){
                            // Can't pass this tube, set tap=0
                            tap=0;
                            bird = min((ll)(bird_prev - Y[i]), (ll)m);
                            if(bird <1) bird=1;
                        }
                    }
                }
            }
            sum_tap += tap;
            bird_prev = bird;
            tube_ptr++;
        }
        else{
            // Not a tube step
            // Set tap=0
            ll bird_try = min((ll)(bird_prev - Y[i]), (ll)m);
            if(bird_try >=1){
                tap=0;
                bird = bird_try;
            }
            else{
                if(X[i]==0){
                    // Cannot increase, set bird to 1
                    tap=0;
                    bird =1;
                }
                else{
                    // Need to set tap to make bird >=1
                    ll required = 1 - (bird_prev - Y[i]);
                    ll t = ceil((double)required / X[i]);
                    if(t <1) t=1;
                    bird = min(bird_prev + X[i]*t, (ll)m);
                    tap = t;
                    sum_tap += tap;
                }
            }
            bird_prev = bird;
        }
    }
    if(pass_tube ==k){
        cout << "1\n" << sum_tap;
    }
    else{
        cout << "0\n" << pass_tube;
    }
}