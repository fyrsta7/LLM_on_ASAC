#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    string word;
    cin >> word;
    // Convert word to lower case
    for(char &c: word){
        c = tolower(c);
    }
    
    string article;
    getline(cin, article); // to consume the newline after word
    getline(cin, article);
    
    int count = 0;
    int first_pos = -1;
    int n = article.size();
    int i = 0;
    while(i < n){
        // Skip any leading spaces
        while(i < n && article[i] == ' ') i++;
        if(i >= n) break;
        int start = i;
        // Find the end of the word
        while(i < n && article[i] != ' ') i++;
        int end = i;
        int word_len = end - start;
        if(word_len == (int)word.size()){
            bool match = true;
            for(int k = 0; k < word_len; k++){
                char c1 = tolower(article[start + k]);
                char c2 = word[k];
                if(c1 != c2){
                    match = false;
                    break;
                }
            }
            if(match){
                count++;
                if(first_pos == -1){
                    first_pos = start;
                }
            }
        }
    }
    
    if(count > 0){
        cout << count << " " << first_pos;
    }
    else{
        cout << "-1";
    }
}