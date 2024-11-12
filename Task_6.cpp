#include <iostream>
#include <chrono>
#include <cstdlib>

using namespace std;

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int partition(int arr[], int low, int high) {
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

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
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

void quickSortRandomPivot(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partitionRandomPivot(arr, low, high);
        quickSortRandomPivot(arr, low, pivotIndex - 1);
        quickSortRandomPivot(arr, pivotIndex + 1, high);
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void measurePerformance(void (*sortFunc)(int[], int, int), int arr[], int size, const string& sortName) {
    auto start = chrono::high_resolution_clock::now();
    sortFunc(arr, 0, size - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << sortName << " - Array Size: " << size << " - Time taken: " << duration.count() << " seconds\n";
}

void measurePerformanceInsertionSort(void (*sortFunc)(int[], int), int arr[], int size, const string& sortName) {
    auto start = chrono::high_resolution_clock::now();
    sortFunc(arr, size);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << sortName << " - Array Size: " << size << " - Time taken: " << duration.count() << " seconds\n";
}

int main() {
    const int sizes[] = {100, 1000, 10000};

    for (int size : sizes) {
        int* arrQuickSort = new int[size];
        int* arrQuickSortRandom = new int[size];
        int* arrMergeSort = new int[size];
        int* arrInsertionSort = new int[size];

        srand(time(0));
        for (int i = 0; i < size; i++) {
            int value = rand() % 1000;
            arrQuickSort[i] = value;
            arrQuickSortRandom[i] = value;
            arrMergeSort[i] = value;
            arrInsertionSort[i] = value;
        }

        cout << "\nTesting with Array Size: " << size << "\n";
        measurePerformance(quickSort, arrQuickSort, size, "Quick Sort (Regular Pivot)");
        measurePerformance(quickSortRandomPivot, arrQuickSortRandom, size, "Quick Sort (Random Pivot)");
        measurePerformance(mergeSort, arrMergeSort, size, "Merge Sort");
        measurePerformanceInsertionSort(insertionSort, arrInsertionSort, size, "Insertion Sort");

        delete[] arrQuickSort;
        delete[] arrQuickSortRandom;
        delete[] arrMergeSort;
        delete[] arrInsertionSort;
    }

    return 0;
}
