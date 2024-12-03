#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

struct BirdProblem {
    int n;
    vector<float> x;
    vector<float> y;
};

float square(float value) {
    return value * value;
}

int solve(const BirdProblem& problem) {
    int n = problem.n;
    const vector<float>& x = problem.x;
    const vector<float>& y = problem.y;
    int count = 0;
    
    for (int i = 0; i < n; ++i) {
        bool hasSolution = false;
        for (float a = -10.0f; a < 0; a += 0.1f) {
            for (float b = -10.0f; b <= 10.0f; b += 0.1f) {
                bool valid = true;
                for (int j = 0; j < n; ++j) {
                    if (fabs(a * square(x[j]) + b * x[j] - y[j]) > 1e-6) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    hasSolution = true;
                    break;
                }
            }
            if (hasSolution) break;
        }
        if (hasSolution) count++;
    }
    
    return count;
}

int main() {
    int T;
    cin >> T;

    vector<BirdProblem> problems(T);
    vector<int> answer(T);
    
    for (int t = 0; t < T; ++t) {
        cin >> problems[t].n;
        problems[t].x.resize(problems[t].n);
        problems[t].y.resize(problems[t].n);
        
        for (int i = 0; i < problems[t].n; ++i) {
            cin >> problems[t].x[i];
            cin >> problems[t].y[i];
        }
    }
    
    for (int t = 0; t < T; ++t) {
        answer[t] = solve(problems[t]);
    }
    
    for (int t = 0; t < T; ++t) {
        cout << answer[t] << " ";
    }
    cout << endl;
    
    return 0;
}
