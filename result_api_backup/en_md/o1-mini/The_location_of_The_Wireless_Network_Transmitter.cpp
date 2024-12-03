#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Point {
    int x;
    int y;
    int k;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int d, n;
    cin >> d >> n;
    vector<Point> points(n);
    for(int i=0;i<n;i++) cin >> points[i].x >> points[i].y >> points[i].k;
    long long max_sum = 0;
    long long count = 0;
    for(int X=0; X<=128; X++){
        for(int Y=0; Y<=128; Y++){
            long long current = 0;
            for(int i=0;i<n;i++) {
                if(abs(points[i].x - X) <= d && abs(points[i].y - Y) <= d){
                    current += points[i].k;
                }
            }
            if(current > max_sum){
                max_sum = current;
                count = 1;
            }
            else if(current == max_sum){
                count++;
            }
        }
    }
    cout << count << " " << max_sum;
}