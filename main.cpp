#include <iostream>
#include <chrono>
using namespace std;

void stopSymbolHeuristic(string str, int size, int stopSymbol[256]) {

    for (int i = 0; i < 256; i++)
        stopSymbol[i] = -1;


    for (int i = 0; i < size; i++)
        stopSymbol[(int) str[i]] = i;
}


void search(string text, string pattern) {
    int m = pattern.size();
    int n = text.size();

    int stopSymbol[256];

    stopSymbolHeuristic(pattern, m, stopSymbol);

    int shift = 0;
    while (shift <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[shift + j])
            j--;

        if (j < 0) {
            cout << "pattern occurs at shift = " << shift << endl;

            shift += (shift + m < n) ? m - stopSymbol[text[shift + m]] : 1;

        } else
            shift += max(1, j - stopSymbol[text[shift + j]]);
    }
}

auto start = chrono::steady_clock::now();
int main() {
    string text1 = "ABAAABCDABAA";
    string pattern1 = "ABC";
    search(text1, pattern1);  // середній показник часу
    cout << endl;


//    string text2 = "DDDDDDDDDDDDDDDDD";
//    string pattern2 = "DDDD";
//    search(text2, pattern2);  // найгірший показник часу
//    cout << endl;


//    string text3 = "DEMIAN";
//    string pattern3 = "MIA";             // найкращий показник часу
//    search(text3, pattern3);

    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << chrono::duration<double, milli>(diff).count() << "ms" << endl;

    return 0;
}



