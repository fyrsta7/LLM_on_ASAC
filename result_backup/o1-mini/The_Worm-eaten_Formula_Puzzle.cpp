#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int n;
string s1, s2, s3;
vector<pair<char, pair<char, char>>> columns;
int assignments_arr[26];
bool used_digits_arr[26];
bool found = false;
int result[26];

bool backtrack(int col, int carry, int assignments[], bool used_digits[]) {
    if (found) return false;
    if (col == n) {
        if (carry == 0) {
            for(int i=0;i<n;i++) result[i]=assignments[i];
            found = true;
            return true;
        }
        return false;
    }
    char a = columns[col].first;
    char b = columns[col].second.first;
    char c = columns[col].second.second;
    int a_val = assignments[a - 'A'];
    int b_val = assignments[b - 'A'];
    int c_val = assignments[c - 'A'];
    // All assigned
    if (a_val != -1 && b_val != -1 && c_val != -1) {
        int total = a_val + b_val + carry;
        if (total % n == c_val) {
            int new_carry = total / n;
            return backtrack(col + 1, new_carry, assignments, used_digits);
        }
        return false;
    }
    // Two assigned
    if (a_val != -1 && b_val != -1 && c_val == -1) {
        int total = a_val + b_val + carry;
        int expected_c = total % n;
        if (!used_digits[expected_c]) {
            assignments[c - 'A'] = expected_c;
            used_digits[expected_c] = true;
            int new_carry = total / n;
            if (backtrack(col + 1, new_carry, assignments, used_digits)) return true;
            assignments[c - 'A'] = -1;
            used_digits[expected_c] = false;
        }
        return false;
    }
    if (a_val != -1 && b_val == -1 && c_val != -1) {
        int total_c = c_val;
        int possible = total_c - a_val - carry;
        if (possible < 0) possible += n;
        int carry_out = (a_val + possible + carry) >= n ? 1 : 0;
        if ((a_val + possible + carry) % n == c_val) {
            if (!used_digits[possible]) {
                assignments[b - 'A'] = possible;
                used_digits[possible] = true;
                if (backtrack(col + 1, carry_out, assignments, used_digits)) return true;
                assignments[b - 'A'] = -1;
                used_digits[possible] = false;
            }
        }
        return false;
    }
    if (a_val == -1 && b_val != -1 && c_val != -1) {
        int total_c = c_val;
        int possible = total_c - b_val - carry;
        if (possible < 0) possible += n;
        int carry_out = (possible + b_val + carry) >= n ? 1 : 0;
        if ((possible + b_val + carry) % n == c_val) {
            if (!used_digits[possible]) {
                assignments[a - 'A'] = possible;
                used_digits[possible] = true;
                if (backtrack(col + 1, carry_out, assignments, used_digits)) return true;
                assignments[a - 'A'] = -1;
                used_digits[possible] = false;
            }
        }
        return false;
    }
    // One or none assigned
    // Try all possible assignments
    // Assign a
    if (a_val == -1 && b_val == -1 && c_val == -1) {
        for(int da=0; da<n; da++) {
            if (!used_digits[da]) {
                assignments[a - 'A'] = da;
                used_digits[da] = true;
                for(int db=0; db<n; db++) {
                    if (!used_digits[db]) {
                        assignments[b - 'A'] = db;
                        used_digits[db] = true;
                        int total = da + db + carry;
                        int dc = total % n;
                        if (!used_digits[dc]) {
                            assignments[c - 'A'] = dc;
                            used_digits[dc] = true;
                            int new_carry = total / n;
                            if (backtrack(col + 1, new_carry, assignments, used_digits)) return true;
                            assignments[c - 'A'] = -1;
                            used_digits[dc] = false;
                        }
                        assignments[b - 'A'] = -1;
                        used_digits[db] = false;
                    }
                }
                assignments[a - 'A'] = -1;
                used_digits[da] = false;
            }
        }
        return false;
    }
    // Assign a
    if (a_val == -1 && b_val != -1 && c_val == -1) {
        for(int da=0; da<n; da++) {
            if (!used_digits[da]) {
                assignments[a - 'A'] = da;
                used_digits[da] = true;
                int total = da + b_val + carry;
                int dc = total % n;
                int new_carry = total / n;
                if (!used_digits[dc]) {
                    assignments[c - 'A'] = dc;
                    used_digits[dc] = true;
                    if (backtrack(col + 1, new_carry, assignments, used_digits)) return true;
                    assignments[c - 'A'] = -1;
                    used_digits[dc] = false;
                }
                assignments[a - 'A'] = -1;
                used_digits[da] = false;
            }
        }
        return false;
    }
    // Assign b
    if (a_val != -1 && b_val == -1 && c_val == -1) {
        for(int db=0; db<n; db++) {
            if (!used_digits[db]) {
                assignments[b - 'A'] = db;
                used_digits[db] = true;
                int total = a_val + db + carry;
                int dc = total % n;
                int new_carry = total / n;
                if (!used_digits[dc]) {
                    assignments[c - 'A'] = dc;
                    used_digits[dc] = true;
                    if (backtrack(col + 1, new_carry, assignments, used_digits)) return true;
                    assignments[c - 'A'] = -1;
                    used_digits[dc] = false;
                }
                assignments[b - 'A'] = -1;
                used_digits[db] = false;
            }
        }
        return false;
    }
    // Assign c
    if (a_val != -1 && b_val != -1 && c_val == -1) {
        int total = a_val + b_val + carry;
        int dc = total % n;
        int new_carry = total / n;
        if (!used_digits[dc]) {
            assignments[c - 'A'] = dc;
            used_digits[dc] = true;
            if (backtrack(col + 1, new_carry, assignments, used_digits)) return true;
            assignments[c - 'A'] = -1;
            used_digits[dc] = false;
        }
        return false;
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    cin >> s1 >> s2 >> s3;
    // Reverse for least to most
    reverse(s1.begin(), s1.end());
    reverse(s2.begin(), s2.end());
    reverse(s3.begin(), s3.end());
    // Prepare columns
    columns.resize(n);
    for(int i=0;i<n;i++) {
        columns[i].first = s1[i];
        columns[i].second.first = s2[i];
        columns[i].second.second = s3[i];
    }
    // Initialize assignments
    for(int i=0;i<26;i++) assignments_arr[i]=-1;
    for(int i=0;i<26;i++) used_digits_arr[i]=false;
    // Start backtracking
    backtrack(0, 0, assignments_arr, used_digits_arr);
    // Output the result
    for(int i=0;i<n;i++) {
        if(i>0) cout << ' ';
        cout << result[i];
    }
}
