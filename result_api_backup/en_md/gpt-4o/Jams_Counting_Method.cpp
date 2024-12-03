#include <iostream>
#include <vector>
#include <string>
using namespace std;

void getNextJamNumber(string &jamNumber, int s, int t, int w) {
    int n = t - s + 1;
    vector<int> indices(w);
    for (int i = 0; i < w; ++i) {
        indices[i] = jamNumber[i] - 'a' - s;
    }
    for (int i = w - 1; i >= 0; --i) {
        if (indices[i] != i + n - w) {
            ++indices[i];
            for (int j = i + 1; j < w; ++j) {
                indices[j] = indices[j - 1] + 1;
            }
            for (int k = 0; k < w; ++k) {
                jamNumber[k] = 'a' + s + indices[k];
            }
            return;
        }
    }
    jamNumber = ""; // If no next number is possible
}

int main() {
    int s, t, w;
    cin >> s >> t >> w;
    string jamNumber;
    cin >> jamNumber;
    
    int count = 0;
    while (count < 5) {
        getNextJamNumber(jamNumber, s, t, w);
        if (jamNumber == "") break;
        cout << jamNumber << endl;
        ++count;
    }
    
    return 0;
}