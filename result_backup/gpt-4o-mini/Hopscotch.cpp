#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Square {
    long long position;
    long long score;
};

long long maxPoints(int n, int d, vector<Square>& squares, int g) {
    long long totalScore = 0;
    long long currentPos = 0;
    int currentIndex = 0;

    long long minJump = max(1LL, d - g);
    long long maxJump = d + g;

    while (currentIndex < n) {
        long long nextPos = currentPos + minJump;
        if (nextPos < squares[currentIndex].position) {
            currentPos += minJump;
            continue;
        }

        long long possibleScores = 0;
        while (currentIndex < n && currentPos >= squares[currentIndex].position) {
            possibleScores += squares[currentIndex].score;
            currentIndex++;
        }

        totalScore += possibleScores;
        
        if (totalScore >= k) return totalScore;
        
        long long currJump = min(maxJump, max(nextPos - currentPos, 1LL));
        if (currJump < 1) break;
        currentPos += currJump;
    }

    return totalScore;
}

int minGoldCoins(int n, int d, long long k, vector<Square>& squares) {
    int left = 0, right = 2000, result = INT_MAX;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (maxPoints(n, d, squares, mid) >= k)
            result = mid, right = mid - 1;
        else
            left = mid + 1;
    }

    return result == INT_MAX ? -1 : result;
}

int main() {
    int n, d, k;
    cin >> n >> d >> k;
    
    vector<Square> squares(n);
    for (int i = 0; i < n; i++) {
        cin >> squares[i].position >> squares[i].score;
    }

    int result = minGoldCoins(n, d, k, squares);
    cout << result << endl;

    return 0;
}