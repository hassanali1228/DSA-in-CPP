#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<int> istack;

    int limit = 10;

    if(istack.size() <= limit){

        //StackAsArray istack { 10 };

        //StackAsArray istack = new StackAsArray(size);
        //top(), size(), empty(), full()

        istack.push( 13 );
        istack.push( 42 );
        istack.empty();

        cout << "Top: " << istack.top() << endl;
        cout << "Size: " << istack.size() << endl;

        istack.pop();                             // no return value

        cout << "Top: " << istack.top() << endl;
        cout << "Size: " << istack.size() << endl;

    } else {

        std::cout << "you ran out hehe";

    }

    return 0;

}
