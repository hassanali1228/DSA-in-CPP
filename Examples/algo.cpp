#include <iostream>
using namespace std;

int main();

int main(){

    int a = 0;

    cout << a++ << endl;
    cout << a << endl;
    cout << ++a << endl;
    cout << a << endl;

    int b = (a++, ++a, 3*a);    //evaluates from left to right

    cout << "b: " << b << endl;

    return 0;

}
