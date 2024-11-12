#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(vector<int> &arr, int low, int high) {
    int pivot = arr[high]; 
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

int partitionRandom(vector<int> &arr, int low, int high) {
    int randomIndex = low + rand() % (high - low + 1); 
    swap(arr[randomIndex], arr[high]);  
    return partition(arr, low, high); 
}

void quickSort(vector<int> &arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

void quickSortRandom(vector<int> &arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partitionRandom(arr, low, high);
        quickSortRandom(arr, low, pivotIndex - 1);
        quickSortRandom(arr, pivotIndex + 1, high);
    }
}

void printArray(const vector<int> &arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

void measurePerformance(vector<int> arr) {
    vector<int> arrCopy = arr; 

    clock_t start = clock();
    quickSort(arr, 0, arr.size() - 1);
    clock_t end = clock();
    double timeOriginal = double(end - start) / CLOCKS_PER_SEC;
    cout << "Time taken by Quick Sort (original): " << timeOriginal << " seconds" << endl;

    start = clock();
    quickSortRandom(arrCopy, 0, arrCopy.size() - 1);
    end = clock();
    double timeRandom = double(end - start) / CLOCKS_PER_SEC;
    cout << "Time taken by Quick Sort (random pivot): " << timeRandom << " seconds" << endl;
}

int main() {
    srand(time(0));

    int n = 10000; 
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000; 
    }

    cout << "Comparing Quick Sort with Original and Random Pivot Selection on Array of Size " << n << ":\n";
    measurePerformance(arr);

    return 0;
}
