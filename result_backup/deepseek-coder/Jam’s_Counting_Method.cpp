#include <iostream>
#include <string>
using namespace std;

bool nextJamNumber(string &jam, int s, int t) {
    int n = jam.size();
    for (int i = n - 1; i >= 0; --i) {
        if (jam[i] < 'a' + t - (n - i)) {
            jam[i]++;
            for (int j = i + 1; j < n; ++j) {
                jam[j] = jam[i] + (j - i);
            }
            return true;
        }
    }
    return false;
}

int main() {
    int s, t, w;
    string jam;
    cin >> s >> t >> w >> jam;

    for (int i = 0; i < 5; ++i) {
        if (nextJamNumber(jam, s, t)) {
            cout << jam << endl;
        } else {
            break;
        }
    }

    return 0;
}
