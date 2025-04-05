#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s; // Input string
    
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '?') {
            // Check left and right neighbors (ignore '?')
            char left = (i > 0) ? s[i-1] : '\0';
            char right = (i < s.size()-1) ? s[i+1] : '\0';
            
            // Find the smallest valid character (A/B/C/D)
            for (char c : {'A', 'B', 'C', 'D'}) {
                if (c != left && c != right) {
                    s[i] = c;
                    break;
                }
            }
        }
    }
    
    cout << s << endl;
    return 0;
}