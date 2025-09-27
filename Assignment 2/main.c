 #include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to swap elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for QuickSort
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // pivot = last element
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// QuickSort (Recursive)
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Merge function for MergeSort
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

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

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// MergeSort (Recursive)
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Function to print array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Function to copy array
void copyArray(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

int main() {
    int arr[] = {12, 4, 7, 9, 1, 3, 15, 8, 6, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    int arr1[n], arr2[n];
    copyArray(arr, arr1, n);
    copyArray(arr, arr2, n);

    printf("Original Array: ");
    printArray(arr, n);

    // Measure MergeSort
    clock_t start = clock();
    mergeSort(arr1, 0, n - 1);
    clock_t end = clock();
    double mergeTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nSorted Array using MergeSort: ");
    printArray(arr1, n);

    // Measure QuickSort
    start = clock();
    quickSort(arr2, 0, n - 1);
    end = clock();
    double quickTime = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nSorted Array using QuickSort: ");
    printArray(arr2, n);

    // Performance comparison
    printf("\nPerformance Comparison:\n");
    printf("MergeSort Time: %f seconds\n", mergeTime);
    printf("QuickSort Time: %f seconds\n", quickTime);

    return 0;
}

