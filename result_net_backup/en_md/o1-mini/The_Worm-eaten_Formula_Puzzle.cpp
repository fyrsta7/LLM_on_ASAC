#include <iostream>
#include <string>
#include <vector>

using namespace std;

int n;
string s1, s2, s_sum;
int letter_to_digit[26];
bool digit_used_flag[26];
bool found = false;
int solution[26];

bool backtrack(int index, int carry) {
    if (found) return false;
    if (index < 0) {
        if (carry == 0) {
            for(int i = 0; i < n; ++i) {
                solution[i] = letter_to_digit[i];
            }
            found = true;
        }
        return false;
    }
    char a = s1[index];
    char b = s2[index];
    char c = s_sum[index];
    int a_idx = a - 'A';
    int b_idx = b - 'A';
    int c_idx = c - 'A';
    int a_digit = letter_to_digit[a_idx];
    int b_digit = letter_to_digit[b_idx];
    int c_digit = letter_to_digit[c_idx];
    if(a_digit != -1 && b_digit != -1 && c_digit != -1){
        int total = a_digit + b_digit + carry;
        if(total % n != c_digit) return false;
        int new_carry = total / n;
        return backtrack(index-1, new_carry);
    }
    if(a_digit != -1 && b_digit != -1){
        int total = a_digit + b_digit + carry;
        int expected_c = total % n;
        int new_carry = total / n;
        if(c_digit == -1){
            if(digit_used_flag[expected_c]) return false;
            letter_to_digit[c_idx] = expected_c;
            digit_used_flag[expected_c] = true;
            if(backtrack(index-1, new_carry)) return true;
            letter_to_digit[c_idx] = -1;
            digit_used_flag[expected_c] = false;
        }
        else{
            if(c_digit != expected_c) return false;
            if(backtrack(index-1, new_carry)) return true;
        }
        return false;
    }
    if(a_digit != -1 && c_digit != -1){
        int b_val = c_digit - a_digit - carry;
        if(b_val < 0){
            b_val += n;
        }
        int new_carry = (c_digit - a_digit - carry < 0) ? 1 : 0;
        if(b_val >= n) return false;
        if(b_digit == -1){
            if(digit_used_flag[b_val]) return false;
            letter_to_digit[b_idx] = b_val;
            digit_used_flag[b_val] = true;
            if(backtrack(index-1, new_carry)) return true;
            letter_to_digit[b_idx] = -1;
            digit_used_flag[b_val] = false;
        }
        else{
            if(b_digit != b_val) return false;
            if(backtrack(index-1, new_carry)) return true;
        }
        return false;
    }
    if(b_digit != -1 && c_digit != -1){
        int a_val = c_digit - b_digit - carry;
        if(a_val < 0){
            a_val += n;
        }
        int new_carry = (c_digit - b_digit - carry < 0) ? 1 : 0;
        if(a_val >= n) return false;
        if(a_digit == -1){
            if(digit_used_flag[a_val]) return false;
            letter_to_digit[a_idx] = a_val;
            digit_used_flag[a_val] = true;
            if(backtrack(index-1, new_carry)) return true;
            letter_to_digit[a_idx] = -1;
            digit_used_flag[a_val] = false;
        }
        else{
            if(a_digit != a_val) return false;
            if(backtrack(index-1, new_carry)) return true;
        }
        return false;
    }
    if(a_digit != -1){
        for(int b_try = 0; b_try < n; ++b_try){
            if(letter_to_digit[b_idx] == -1 && digit_used_flag[b_try]) continue;
            if(letter_to_digit[b_idx] != -1 && letter_to_digit[b_idx] != b_try) continue;
            int total = a_digit + b_try + carry;
            int c_try = total % n;
            int new_carry = total / n;
            if(letter_to_digit[c_idx] == -1 && digit_used_flag[c_try]) continue;
            if(letter_to_digit[c_idx] != -1 && letter_to_digit[c_idx] != c_try) continue;
            if(letter_to_digit[b_idx] == -1 && letter_to_digit[c_idx] == -1){
                if(b_try == c_try && digit_used_flag[b_try]) continue;
                letter_to_digit[b_idx] = b_try;
                letter_to_digit[c_idx] = c_try;
                digit_used_flag[b_try] = true;
                digit_used_flag[c_try] = true;
                if(backtrack(index-1, new_carry)) return true;
                letter_to_digit[b_idx] = -1;
                letter_to_digit[c_idx] = -1;
                digit_used_flag[b_try] = false;
                digit_used_flag[c_try] = false;
            }
            else if(letter_to_digit[b_idx] == -1){
                letter_to_digit[b_idx] = b_try;
                digit_used_flag[b_try] = true;
                if(letter_to_digit[c_idx] == -1){
                    letter_to_digit[c_idx] = c_try;
                    digit_used_flag[c_try] = true;
                    if(backtrack(index-1, new_carry)) return true;
                    letter_to_digit[c_idx] = -1;
                    digit_used_flag[c_try] = false;
                }
                else{
                    if(backtrack(index-1, new_carry)) return true;
                }
                letter_to_digit[b_idx] = -1;
                digit_used_flag[b_try] = false;
            }
            else if(letter_to_digit[c_idx] == -1){
                letter_to_digit[c_idx] = c_try;
                digit_used_flag[c_try] = true;
                if(backtrack(index-1, new_carry)) return true;
                letter_to_digit[c_idx] = -1;
                digit_used_flag[c_try] = false;
            }
            else{
                if(backtrack(index-1, new_carry)) return true;
            }
        }
        return false;
    }
    if(b_digit != -1){
        for(int a_try = 0; a_try < n; ++a_try){
            if(letter_to_digit[a_idx] == -1 && digit_used_flag[a_try]) continue;
            if(letter_to_digit[a_idx] != -1 && letter_to_digit[a_idx] != a_try) continue;
            int total = a_try + b_digit + carry;
            int c_try = total % n;
            int new_carry = total / n;
            if(letter_to_digit[c_idx] == -1 && digit_used_flag[c_try]) continue;
            if(letter_to_digit[c_idx] != -1 && letter_to_digit[c_idx] != c_try) continue;
            if(letter_to_digit[a_idx] == -1 && letter_to_digit[c_idx] == -1){
                if(a_try == c_try && digit_used_flag[a_try]) continue;
                letter_to_digit[a_idx] = a_try;
                letter_to_digit[c_idx] = c_try;
                digit_used_flag[a_try] = true;
                digit_used_flag[c_try] = true;
                if(backtrack(index-1, new_carry)) return true;
                letter_to_digit[a_idx] = -1;
                letter_to_digit[c_idx] = -1;
                digit_used_flag[a_try] = false;
                digit_used_flag[c_try] = false;
            }
            else if(letter_to_digit[a_idx] == -1){
                letter_to_digit[a_idx] = a_try;
                digit_used_flag[a_try] = true;
                if(letter_to_digit[c_idx] == -1){
                    letter_to_digit[c_idx] = c_try;
                    digit_used_flag[c_try] = true;
                    if(backtrack(index-1, new_carry)) return true;
                    letter_to_digit[c_idx] = -1;
                    digit_used_flag[c_try] = false;
                }
                else{
                    if(backtrack(index-1, new_carry)) return true;
                }
                letter_to_digit[a_idx] = -1;
                digit_used_flag[a_try] = false;
            }
            else if(letter_to_digit[c_idx] == -1){
                letter_to_digit[c_idx] = c_try;
                digit_used_flag[c_try] = true;
                if(backtrack(index-1, new_carry)) return true;
                letter_to_digit[c_idx] = -1;
                digit_used_flag[c_try] = false;
            }
            else{
                if(backtrack(index-1, new_carry)) return true;
            }
        }
        return false;
    }
    if(c_digit != -1){
        for(int a_try = 0; a_try < n; ++a_try){
            if(letter_to_digit[a_idx] == -1 && digit_used_flag[a_try]) continue;
            if(letter_to_digit[a_idx] != -1 && letter_to_digit[a_idx] != a_try) continue;
            int b_val = c_digit - a_try - carry;
            if(b_val < 0){
                b_val += n;
            }
            int new_carry = (c_digit - a_try - carry < 0) ? 1 : 0;
            if(b_val >= n) continue;
            if(letter_to_digit[b_idx] != -1 && letter_to_digit[b_idx] != b_val) continue;
            if(letter_to_digit[b_idx] == -1 && digit_used_flag[b_val]) continue;
            if(letter_to_digit[a_idx] == -1 && letter_to_digit[b_idx] == -1){
                if(a_try == b_val && digit_used_flag[a_try]) continue;
                letter_to_digit[a_idx] = a_try;
                letter_to_digit[b_idx] = b_val;
                digit_used_flag[a_try] = true;
                digit_used_flag[b_val] = true;
                if(backtrack(index-1, new_carry)) return true;
                letter_to_digit[a_idx] = -1;
                letter_to_digit[b_idx] = -1;
                digit_used_flag[a_try] = false;
                digit_used_flag[b_val] = false;
            }
            else if(letter_to_digit[a_idx] == -1){
                letter_to_digit[a_idx] = a_try;
                digit_used_flag[a_try] = true;
                if(letter_to_digit[b_idx] == -1){
                    letter_to_digit[b_idx] = b_val;
                    digit_used_flag[b_val] = true;
                    if(backtrack(index-1, new_carry)) return true;
                    letter_to_digit[b_idx] = -1;
                    digit_used_flag[b_val] = false;
                }
                else{
                    if(backtrack(index-1, new_carry)) return true;
                }
                letter_to_digit[a_idx] = -1;
                digit_used_flag[a_try] = false;
            }
            else if(letter_to_digit[b_idx] == -1){
                letter_to_digit[b_idx] = b_val;
                digit_used_flag[b_val] = true;
                if(backtrack(index-1, new_carry)) return true;
                letter_to_digit[b_idx] = -1;
                digit_used_flag[b_val] = false;
            }
            else{
                if(backtrack(index-1, new_carry)) return true;
            }
        }
        return false;
    }
    for(int a_try = 0; a_try < n; ++a_try){
        if(letter_to_digit[a_idx] == -1 && digit_used_flag[a_try]) continue;
        for(int b_try = 0; b_try < n; ++b_try){
            if(b_try == a_try) continue;
            if(letter_to_digit[b_idx] == -1 && digit_used_flag[b_try]) continue;
            int total = a_try + b_try + carry;
            int c_try = total % n;
            int new_carry = total / n;
            if(c_try >= n) continue;
            if(letter_to_digit[c_idx] == -1 && digit_used_flag[c_try]) continue;
            if(letter_to_digit[c_idx] != -1 && letter_to_digit[c_idx] != c_try) continue;
            if(letter_to_digit[c_idx] == -1 && (c_try == a_try || c_try == b_try)) continue;
            if(letter_to_digit[a_idx] == -1 && letter_to_digit[b_idx] == -1 && letter_to_digit[c_idx] == -1){
                if(a_try == b_try || a_try == c_try || b_try == c_try) continue;
                letter_to_digit[a_idx] = a_try;
                letter_to_digit[b_idx] = b_try;
                letter_to_digit[c_idx] = c_try;
                digit_used_flag[a_try] = true;
                digit_used_flag[b_try] = true;
                digit_used_flag[c_try] = true;
                if(backtrack(index-1, new_carry)) return true;
                letter_to_digit[a_idx] = -1;
                letter_to_digit[b_idx] = -1;
                letter_to_digit[c_idx] = -1;
                digit_used_flag[a_try] = false;
                digit_used_flag[b_try] = false;
                digit_used_flag[c_try] = false;
            }
            else{
                if(letter_to_digit[a_idx] == -1){
                    letter_to_digit[a_idx] = a_try;
                    digit_used_flag[a_try] = true;
                }
                if(letter_to_digit[b_idx] == -1){
                    letter_to_digit[b_idx] = b_try;
                    digit_used_flag[b_try] = true;
                }
                if(letter_to_digit[c_idx] == -1){
                    letter_to_digit[c_idx] = c_try;
                    digit_used_flag[c_try] = true;
                }
                if(backtrack(index-1, new_carry)) return true;
                if(letter_to_digit[c_idx] == c_try){
                    letter_to_digit[c_idx] = -1;
                    digit_used_flag[c_try] = false;
                }
                if(letter_to_digit[b_idx] == b_try){
                    letter_to_digit[b_idx] = -1;
                    digit_used_flag[b_try] = false;
                }
                if(letter_to_digit[a_idx] == a_try){
                    letter_to_digit[a_idx] = -1;
                    digit_used_flag[a_try] = false;
                }
            }
        }
    }
    return false;
}

int main(){
    cin >> n;
    cin >> s1 >> s2 >> s_sum;
    for(int i = 0; i < 26; ++i){
        letter_to_digit[i] = -1;
    }
    for(int i = 0; i < n; ++i){
        digit_used_flag[i] = false;
    }
    backtrack(n-1, 0);
    for(int i = 0; i < n; ++i){
        cout << solution[i];
        if(i != n-1) cout << ' ';
    }
    return 0;
}