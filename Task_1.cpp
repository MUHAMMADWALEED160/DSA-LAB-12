#include<iostream>
#include<vector>
#include<ctime>
using namespace std;

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

int partition(vector<int> &arr, int low, int high){
    int pivot = arr[low];  
    int i = low + 1;
    for(int j = low + 1; j <= high; j++){
        if(arr[j] < pivot){
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[low], arr[i - 1]);
    return i - 1;
}

void quickSort(vector<int> &arr, int low, int high){
    if (low < high)
    {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

void printArray(const vector<int> &arr){
    for (int num:arr)
    {
        cout<<num<<" ";
    }
    cout<<endl;
}

int main(){
    vector<int> arr={16,14,53,31,7,29,41,6,19};
    int n=arr.size();

    cout<<"Original Array: ";
    printArray(arr);

    clock_t start=clock();
    quickSort(arr, 0, n-1);
    clock_t end=clock();

    cout<<"Sorted Array: ";
    printArray(arr);

    double time_taken = double(end-start)/CLOCKS_PER_SEC;
    cout<<"Time taken by quickSort: "<<time_taken<<" Seconds"<<endl;

    return 0;
}