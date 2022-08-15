#include <iostream>
#include <queue>
using namespace std;

int main() {
    queue<int> iqueue;

    iqueue.push( 5 );
    iqueue.push( 6 );
    iqueue.push( 87 );
    iqueue.pop();
    iqueue.push(9);
    iqueue.pop();
    iqueue.pop();
    iqueue.push(1);
    iqueue.push(12);
    iqueue.pop();
    iqueue.pop();

    cout << "Top: " << iqueue.back() << endl;
    cout << "Size: " << iqueue.size() << endl;

    return 0;

}
