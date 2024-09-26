#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int p1, p2, p3, m;
    cin >> p1 >> p2 >> p3 >> m;
    string s;
    cin >> s;
    // Define lower and upper alphabets
    string lower_alphabet = "abcdefghijklmnopqrstuvwxyz0123456789";
    string upper_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    // Function to get index in alphabet (1-based)
    auto index_of = [&](const string& alphabet, char c) -> int {
        return alphabet.find(c) + 1;
    };
    string result = "";
    for(int p=0; p<m; p++){
        if(p ==0 || p ==m-1){
            result += s[p];
        }
        else if(s[p-1] == '-' || s[p+1] == '-'){
            result += s[p];
        }
        else{
            if(s[p] == '-'){
                // Check conditions
                char before = s[p-1];
                char after = s[p+1];
                int idx_before = index_of(lower_alphabet, before);
                int idx_after = index_of(lower_alphabet, after);
                if(idx_before >0 && idx_after >0 && idx_before < idx_after){
                    bool both_lower = (islower(before) && islower(after));
                    bool both_upper = (isupper(before) && isupper(after));
                    bool both_digit = (isdigit(before) && isdigit(after));
                    if( (both_lower || both_upper || both_digit)){
                        // Generate range
                        vector<char> range_chars;
                        for(int t=idx_before; t<idx_after-1; t++){
                            range_chars.push_back(lower_alphabet[t]);
                        }
                        if(p3 ==2){
                            reverse(range_chars.begin(), range_chars.end());
                        }
                        // Concatenate with p2 repeats and based on p1
                        string expansion_str = "";
                        for(char c: range_chars){
                            for(int l=0; l<p2; l++){
                                if(p1 ==1){
                                    expansion_str += lower_alphabet[c >= 'a' && c <= 'z' ? lower_alphabet.find(c) : lower_alphabet.find('0') + (c - '0')];
                                }
                                else if(p1 ==2){
                                    if(isalpha(c)){
                                        expansion_str += toupper(c);
                                    }
                                    else{
                                        expansion_str += c;
                                    }
                                }
                                else{
                                    expansion_str += '*';
                                }
                            }
                        }
                        result += expansion_str;
                    }
                    else{
                        result += s[p];
                    }
                }
                else{
                    result += s[p];
                }
            }
            else{
                result += s[p];
            }
        }
    }
    cout << result;
}