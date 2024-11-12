#include <iostream>
#include <chrono>
#include <cstdlib> 

using namespace std;

void insertionSort(int arr[], int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int partitionRandomPivot(int arr[], int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);
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

void quickSortWithInsertionSort(int arr[], int low, int high) {
    const int threshold = 10; 

    if (high - low + 1 <= threshold) {
        insertionSort(arr, low, high);
    } else {
        if (low < high) {
            int pivotIndex = partitionRandomPivot(arr, low, high);
            quickSortWithInsertionSort(arr, low, pivotIndex - 1);
            quickSortWithInsertionSort(arr, pivotIndex + 1, high);
        }
    }
}

void measurePerformance(void (*sortFunc)(int[], int, int), int arr[], int size) {
    auto start = chrono::high_resolution_clock::now();
    sortFunc(arr, 0, size - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Array Size: " << size << " - Time taken: " << duration.count() << " seconds\n";
}

int main() {
    const int sizes[] = {100, 1000, 10000}; 

    for (int size : sizes) {
        int* arr = new int[size];
        
        srand(time(0));
        for (int i = 0; i < size; i++) {
            arr[i] = rand() % 1000;
        }

        cout << "\nHybrid Quick Sort (with Insertion Sort for small subarrays):\n";
        measurePerformance(quickSortWithInsertionSort, arr, size);

        delete[] arr; 
    }

    return 0;
}