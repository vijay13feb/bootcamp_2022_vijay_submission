#include <iostream>
#include <cstring>
// #include <string.h>
#include <sstream>

using namespace std;

struct Complex{
    int real_part;
    int img_part;
    
    Complex(int real, int imaginary){
        real_part = real;
        img_part = imaginary;
    }

    Complex Add(Complex num){ // return a complex number by adding another complex number to itself
        Complex result(0, 0);
        result.real_part = real_part + num.real_part;
        result.img_part = img_part + num.img_part;
        return result;
    }
};

int main(){
    string s1, s1_r, s1_i;
    cout << "Enter first complex number: ";
    getline(cin, s1);

    istringstream is1(s1);
    is1 >> s1_r >> s1_i;

    string s2, s2_r, s2_i;
    cout << "Enter second complex number: ";
    getline(cin, s2);

    istringstream is2(s2);
    is2 >> s2_r >> s2_i;

    Complex c1(stoi(s1_r), stoi(s1_i));
    Complex c2(stoi(s2_r), stoi(s2_i));

    Complex result = c1.Add(c2);

    cout << "Result: " << result.real_part << " " << result.img_part << endl;
    return 0;
}