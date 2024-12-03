#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string toLower(string s) {
    for (char &c : s) {
        c = tolower(c);
    }
    return s;
}

bool isDelimiter(char c) {
    return c == ' ';
}

int main() {
    string word, article;
    getline(cin, word);
    getline(cin, article);

    word = toLower(word);
    article = toLower(article);

    int wordLength = word.length();
    int articleLength = article.length();
    int firstPosition = -1;
    int count = 0;

    for (int i = 0; i <= articleLength - wordLength; ) {
        if ((i == 0 || isDelimiter(article[i - 1])) && (i + wordLength >= articleLength || isDelimiter(article[i + wordLength]))) {
            string sub = article.substr(i, wordLength);
            if (sub == word) {
                if (count == 0) {
                    firstPosition = i;
                }
                count++;
                i += wordLength;
            } else {
                while (i < articleLength && !isDelimiter(article[i])) {
                    i++;
                }
                i++;
            }
        } else {
            while (i < articleLength && !isDelimiter(article[i])) {
                i++;
            }
            i++;
        }
    }

    if (count > 0) {
        cout << count << " " << firstPosition << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}