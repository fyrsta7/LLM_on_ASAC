#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int s, t, w;
    cin >> s >> t >> w;
    string jamNumber;
    cin >> jamNumber;

    vector<char> validChars;
    for (int i = s - 1; i < t; ++i) {
        validChars.push_back('a' + i);
    }

    vector<string> results;
    for (int i = 0; i < w; ++i) {
        for (char c = jamNumber[i] + 1; c <= validChars[t - s]; ++c) {
            if (c > validChars[s - 1 + (i == 0 ? 0 : 1)]) {
                string nextJamNumber = jamNumber.substr(0, i);
                nextJamNumber += c;

                int lastChar = validChars[s - 1 + 1 + i]; // Next character after c
                for (int j = i + 1; j < w; ++j) {
                    nextJamNumber += lastChar++;
                    if (lastChar > validChars[t - s]) break;
                }

                if (nextJamNumber.length() == w) {
                    results.push_back(nextJamNumber);
                    if (results.size() == 5) break;
                }
            }
        }
        if (results.size() == 5) break;
    }

    for (const auto& num : results) {
        cout << num << endl;
    }

    return 0;
}