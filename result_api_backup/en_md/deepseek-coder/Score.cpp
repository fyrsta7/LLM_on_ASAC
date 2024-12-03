#include <iostream>
using namespace std;

int main() {
    int A, B, C;
    cin >> A >> B >> C;
    int totalGrade = (A * 20 + B * 30 + C * 50) / 100;
    cout << totalGrade << endl;
    return 0;
}