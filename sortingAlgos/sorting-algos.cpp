#include <iostream>
using namespace std;

void merge(int arr[], int l, int m, int r)
{
      // Your code here
      int *merged = new int[r-l+1];
      int k = 0, i = l, j = m+1;
      while (i <= m && j <= r) {
          if (arr[i] < arr[j]) {
              merged[k++] = arr[i++]; 
          } else {
              merged[k++] = arr[j++];
          }
      }
      while (i <= m) {
          merged[k++] = arr[i++]; 
      }
      while (j <= r) {
          merged[k++] = arr[j++];
      }
      k = 0;
      for (int i = l; i <= r; i++, k++) {
          arr[i] = merged[k];
      }
}

void mergeSort(int arr[], int l, int r)
{
    //code here
    if (l >= r) return;
    int mid = l + (r-l)/2;
    mergeSort (arr, l, mid);
    mergeSort(arr, mid+1, r);
    merge(arr, l, mid, r);
}

int partition (int arr[], int low, int high)
{
    // Your code here
    int pivot = arr[high], st = low;
    for (int i = low; i < high; i++) {
        if (arr[i] <= pivot) {
            int temp = arr[i];
            arr[i] = arr[st];
            arr[st++] = temp;
        }
    }
    arr[high] = arr[st];
    arr[st] = pivot;
    return st;
}

void quickSort(int arr[], int low, int high)
{
    // code here
    if (low < high) {
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot-1);
        quickSort(arr, pivot+1, high);
    }
}

void selectionSort (vector<int> &arr) {
    for (int i = 0; i < arr.size()-1; i++) {
        int j = i+1, min = i;
        while (j < arr.size()) {
            if (arr[min] > arr[j]) {
                min = j;
            }
            j++;
        }
        int temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}

void insertionSort (vector<int> &arr) {
    for (int i = 1; i < arr.size(); i++) {
        int j = i-1;
        while (j >= 0 && arr[j] > arr[j+1]) {
            int temp = arr[j];
            arr[j] = arr[j+1];
            arr[j+1] = temp;
            j--;
        }
    }
}

void bubbleSort (vector<int> &arr) {
    for (int i = arr.size()-1; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main () {

  return 0;
} 