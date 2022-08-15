#include <iostream>
using namespace std;

int main();
int binarysearch(int array[], int size, int val);
void selection_sort(int *array, int n);

int main(){

    int arr[] = {10,20,30,40,50,60,70,80,89,0,68,9,53,8494,354,894,35894,53,4894,48,9,4,489,4};

    cout << binarysearch(arr, sizeof(arr)/sizeof(arr[0]), 53) << "th val is: " << arr[binarysearch(arr, sizeof(arr)/sizeof(arr[0]), 53)] << endl;

    return 0;

}

int binarysearch(int array[], int size, int val){

    int a = 0;
    int b = size - 1;

    while(a <= b){

        int mid = a + ((b-a)/2);

        // cout << a << mid << b << endl;

        if (val == array[mid]) return mid;

        if(val < array[mid]){

            b = mid - 1;

        } else if (val > array[mid]){

            a = mid + 1;

        }

    }

    return -1;

}

void selection_sort(int *array, int n) {

    if (n <= 1) {
        return; // special case:  0 or 1 items are always sorted
    }

    int posn = 0; // assume the first entry is the smallest
    int max = array[posn];

    for (int i = 1; i < n; ++i) { // search through the remaining entries
        
        if (array[i] > max) { // if a larger one is found
            posn = i; // update both the position and value
            max = array[posn];
        }
    
    }

    int tmp = array[n - 1]; // swap the largest entry with the last
    
    array[n - 1] = array[posn];
    array[posn] = tmp;

    selection_sort(array, n - 1); //recursively sort everything else
    
}
