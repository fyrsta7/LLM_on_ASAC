#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, NA, NB;
    cin >> N >> NA >> NB;

    vector<int> A(NA), B(NB);
    for (int i = 0; i < NA; ++i) cin >> A[i];
    for (int i = 0; i < NB; ++i) cin >> B[i];

    int scoreA = 0, scoreB = 0;

    for (int i = 0; i < N; ++i) {
        int gestureA = A[i % NA];
        int gestureB = B[i % NB];
        
        if (gestureA == gestureB) {
            continue; // Even
        } else if ((gestureA == 0 && (gestureB == 4 || gestureB == 1)) ||
                   (gestureA == 1 && (gestureB == 0 || gestureB == 3)) ||
                   (gestureA == 2 && (gestureB == 1 || gestureB == 4)) ||
                   (gestureA == 3 && (gestureB == 2 || gestureB == 0)) ||
                   (gestureA == 4 && (gestureB == 3 || gestureB == 1))) {
            scoreB++; // B wins
        } else {
            scoreA++; // A wins
        }
    }

    cout << scoreA << " " << scoreB << endl;
    return 0;
}