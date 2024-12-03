#include <iostream>
#include <string>
#include <vector>

using namespace std;

int to_int(char c) {
    return c >= 'a' ? c - 'a' + 1 : c - 'A' + 1;
}

char to_char(int i) {
    return 'A' + i - 1;
}

int main() {
    string M, k;
    cin >> M >> k;

    int M_len = M.length();
    int k_len = k.length();

    vector<int> y(M_len);
    vector<int> x(M_len);
    vector<int> z(M_len);

    for (int i = 0; i < M_len; ++i) {
        y[i] = to_int(M[i]);
        x[i] = to_int(k[i % k_len]);
        z[i] = (y[i] - x[i] + 26) % 26 + 1;
    }

    string out_str;
    for (int i = 0; i < M_len; ++i) {
        out_str += to_char(z[i]);
    }

    cout << out_str << endl;

    return 0;
}
