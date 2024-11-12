#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
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

void generateRandomArray(vector<int> &arr, int size){
    srand(time(0));
    for(int i = 0; i < size; i++){
        arr.push_back(rand() % 1000);
    }
}

void measurePerformance(int size){
    vector<int> arr;
    generateRandomArray(arr, size);

    clock_t start=clock();
    quickSort(arr, 0, size-1);
    clock_t end=clock();

    double time_taken = double(end-start)/CLOCKS_PER_SEC;
    cout<<"Size: "<<size<<", Time taken: "<<time_taken<<" Seconds"<<endl;
}

int main(){
    int sizes[] = {100, 1000, 10000, 50000, 100000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    for(int i = 0; i < numSizes; i++){
        measurePerformance(sizes[i]);
    }

    return 0;
}