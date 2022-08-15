#include <iostream>
#include <fstream>

using namespace std; //It’s a midterm, let’s be nice to each other and use this
#include <stack>

int main() {

    ifstream fin("inputData.txt"); //this opens a file stream for reading

    char nextInput = 0;

    stack<char> istack;

    //assume nextInput is the current character in the string

    while (fin>>nextInput) {

        if(!istack.empty() && nextInput == ')' && istack.top() == '(' ) {
            istack.pop();
        
        }   else if (!istack.empty() && nextInput == ']' && istack.top() == '[' ) {
            istack.pop();
        
        }   else if (nextInput == '[' || nextInput == '(') {
            istack.push(nextInput);
        
        }
    
    }

    if ( istack.empty() ) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
    
    return 0;

}
