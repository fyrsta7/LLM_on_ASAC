#include <iostream>
#include <string>

using namespace std;

int main() {
    string numstr;
    cin >> numstr;

    int one_num = 0;
    for (char c : numstr) {
        if (c == '1') {
            one_num++;
        }
    }

    cout << one_num << endl;
    return 0;
}