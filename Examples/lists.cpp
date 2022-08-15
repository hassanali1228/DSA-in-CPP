#include <iostream>
#include <vector>       //use STL
using namespace std;

int main();

int main(){

    long long arr[] = {10,20,30,40,50,60,70,80,89,0,68,9,53,8494,354,894,45618654189532418,53,4894,48,9,4,489,4};

    // cout << sizeof(arr)/sizeof(arr[0]);

    vector<int> v(10,0);

    v[0] = 42;
    v[9] = 91;

    // cout << v.empty();
    // cout << v.capacity();

    for (int k = 0; k < v.size(); ++k) cout << v[k] << endl;

    // can add stuff more than capacity but that requires copy operation

    return 0;

}
