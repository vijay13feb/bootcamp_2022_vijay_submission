#include <iostream>

using namespace std;

int main(){
    cout << "Enter Number: ";
    string s;
    cin >> s;
    int n = stoi(s);
    cout << "Factors: ";
    for (int i=1; i <= n; i++){
        if(n % i == 0){
            cout << i << " ";
        }
    }
    cout << endl;
    return 0;
}