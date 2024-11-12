#include<iostream>
#include<vector>
#include<ctime>
using namespace std;
void swap(int &a,int &b){
    int temp = a;
    a = b;
    b = temp;
}
// Partition function to pivot element in the correct position
int partition(vector<int> &arr, int low, int high){
    int pivot = arr[high]; //choose the last element as pivot
    int i = low - 1; // index of the smallest element

    for (int j = low; j<high; j++){
        if(arr[j] < pivot){ //If current element is samller then ppivot
           i++;
           swap(arr[i],arr[j]); //swap it with the element at index i             
        }
    }
    swap(arr[i+1], arr[high]); //Place the pivot in its correct position
    return i + 1; //Return the pivot index
}
//Quick Sort Function
void quickSort(vector<int> &arr, int low, int high){
    if(low<high){
        int pivotIndex = partition(arr, low, high);

        //Recursively sort elements before and after partition
        quickSort(arr, low, pivotIndex-1);
        quickSort(arr, pivotIndex+1, high);
    }
}
// Utility function to print the array
void printArray(const vector<int> &arr){
    for(int num : arr){
        cout<< num <<" ";
    }
    cout<< endl;
}
int main(){
    vector<int> arr = {33, 12, 52, 3, 75, 29, 41, 6, 19};
    int n = arr.size();
    cout<<"Original Array: ";
    printArray(arr);
    //Measure the time talen for quick Sort
    clock_t start = clock();
    quickSort(arr, 0, n-1);
    clock_t end = clock();

    cout<<"Sorted Array: ";
    printArray(arr);

    double time_taken = double(end- start) /    CLOCKS_PER_SEC;
    cout<<"Time taken by Quick Sort: "<<time_taken<<"Seconds "<<endl;
    return 0;
}
