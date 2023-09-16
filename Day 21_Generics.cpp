#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
void printArray(const vector<T>& arr) {
    for (const T& element : arr) {
        cout << element << endl;
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    int n;
    cin >> n;
    
    vector<int> intArray(n);
    for (int i = 0; i < n; i++) {
        cin >> intArray[i];
    }
    
    int m;
    cin >> m;
    
    vector<string> stringArray(m);
    cin.ignore();  // Consume the newline character left by previous input
    
    for (int i = 0; i < m; i++) {
        getline(cin, stringArray[i]);
    }
    
    printArray(intArray);
    printArray(stringArray);
    
    return 0;
}