#include <bits/stdc++.h>
using namespace std;

int main(){
    int s, t;
    cin >> s >> t;
    vector<int> pal_dates;
    for(int y=0; y<=9999; y++){
        string y_str = to_string(y);
        while(y_str.size() <4) y_str = "0" + y_str;
        string mmdd_str = y_str;
        reverse(mmdd_str.begin(), mmdd_str.end());
        if(mmdd_str.size() !=4) continue;
        int mm = stoi(mmdd_str.substr(0,2));
        int dd = stoi(mmdd_str.substr(2,2));
        if(mm <1 || mm >12) continue;
        int max_d=31;
        if(mm ==4 || mm==6 || mm==9 || mm==11){
            max_d=30;
        }
        else if(mm ==2){
            bool leap = (y%4 ==0 && (y%100 !=0 || y%400 ==0));
            max_d = leap ? 29 : 28;
        }
        if(dd >=1 && dd <= max_d){
            int w = y * 10000 + mm *100 + dd;
            pal_dates.push_back(w);
        }
    }
    // pal_dates is sorted
    int res = upper_bound(pal_dates.begin(), pal_dates.end(), t) - lower_bound(pal_dates.begin(), pal_dates.end(), s);
    cout << "res=" << res << "\n";
}