#include <iostream>
#include <string>

using namespace std;

int main() {
    int N;
    cin >> N;

    string name;
    int avgScore, classScore, totalScholarships = 0;
    char isLeader, isWestern;
    int publishedPapers;

    string maxScholarshipName;
    int maxScholarshipAmount = 0;

    for (int i = 0; i < N; ++i) {
        cin >> name >> avgScore >> classScore >> isLeader >> isWestern >> publishedPapers;

        int scholarshipAmount = 0;

        if (avgScore > 80 && publishedPapers > 0) {
            scholarshipAmount += 8000; // Academician Scholarship
        }
        if (avgScore > 85 && classScore > 80) {
            scholarshipAmount += 4000; // May 4th Scholarship
        }
        if (avgScore > 90) {
            scholarshipAmount += 2000; // Outstanding Academic Results Scholarship
        }
        if (isWestern == 'Y' && avgScore > 85) {
            scholarshipAmount += 1000; // Western Scholarship
        }
        if (isLeader == 'Y' && classScore > 80) {
            scholarshipAmount += 850; // Class Contribution Scholarship
        }

        totalScholarships += scholarshipAmount;

        if (scholarshipAmount > maxScholarshipAmount) {
            maxScholarshipAmount = scholarshipAmount;
            maxScholarshipName = name;
        }
    }

    cout << maxScholarshipName << endl;
    cout << maxScholarshipAmount << endl;
    cout << totalScholarships << endl;

    return 0;
}