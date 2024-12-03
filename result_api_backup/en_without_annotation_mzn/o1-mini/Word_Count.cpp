#include <bits/stdc++.h>
using namespace std;

int main(){
    string find_str, text_str;
    cin >> find_str;
    cin >> text_str;

    // Convert to lowercase
    auto to_lower_case = [](string s) -> string{
        string res = s;
        for(auto &c: res) c = tolower(c);
        return res;
    };

    string fs = to_lower_case(find_str);
    string ts = to_lower_case(text_str);
    int find_len = fs.length();
    int text_len = ts.length();

    int num = 0;
    int first_pos = -1;

    size_t pos = ts.find(fs);
    while(pos != string::npos){
        // Check whole word
        bool is_start_ok = (pos ==0) || (ts[pos-1] == ' ');
        bool is_end_ok = (pos + find_len >= text_len) || (ts[pos + find_len] == ' ');
        if(is_start_ok && is_end_ok){
            num++;
            if(first_pos == -1){
                first_pos = pos;
            }
        }
        pos = ts.find(fs, pos +1);
    }

    if(num >0){
        cout << num << first_pos;
    }
    else{
        cout << "-1-1";
    }
}