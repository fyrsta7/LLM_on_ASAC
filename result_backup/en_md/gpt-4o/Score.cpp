#include <iostream>
using namespace std;

int main() {
    int A, B, C;
    cin >> A >> B >> C;
    int totalGrade = static_cast<int>(A * 0.2 + B * 0.3 + C * 0.5);
    cout << totalGrade << endl;
    return 0;
}