#include <stdio.h>

void bubbleSort(int arr[], int n, int *trocas) {
    *trocas = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                (*trocas)++;
            }
        }
    }
}

void quickSort(int arr[], int low, int high, int *trocas) {
    if (low < high) {
        int pi = partition(arr, low, high, trocas);
        quickSort(arr, low, pi - 1, trocas);
        quickSort(arr, pi + 1, high, trocas);
    }
}

int partition(int arr[], int low, int high, int *trocas) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            (*trocas)++;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    (*trocas)++;

    return i + 1;
}

void selectionSort(int arr[], int n, int *trocas) {
    *trocas = 0;
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            int temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
            (*trocas)++;
        }
    }
}

int main() {
    int arrBubble[] = {64, 34, 25, 12, 22, 11, 90};
    int arrQuick[] = {64, 34, 25, 12, 22, 11, 90};
    int arrSelection[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arrBubble) / sizeof(arrBubble[0]);

    int trocasBubble, trocasQuick, trocasSelection;

    bubbleSort(arrBubble, n, &trocasBubble);
    quickSort(arrQuick, 0, n - 1, &trocasQuick);
    selectionSort(arrSelection, n, &trocasSelection);

    printf("Bubble Sort - Trocas: %d\n", trocasBubble);
    printf("Quick Sort - Trocas: %d\n", trocasQuick);
    printf("Selection Sort - Trocas: %d\n", trocasSelection);

    return 0;
}
