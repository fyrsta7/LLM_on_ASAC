#include <iostream>
#include <string>
using namespace std;

string constructFBI(const string &S) {
    if (S.size() == 1) {
        if (S[0] == '0')
            return "B";
        else
            return "I";
    }
    string left = constructFBI(S.substr(0, S.size() / 2));
    string right = constructFBI(S.substr(S.size() / 2));
    if (left[0] == 'B' && right[0] == 'B')
        return left + right + "B";
    else if (left[0] == 'I' && right[0] == 'I')
        return left + right + "I";
    else
        return left + right + "F";
}

int main() {
    int N;
    cin >> N;
    string S;
    cin >> S;
    cout << constructFBI(S) << endl;
    return 0;
}