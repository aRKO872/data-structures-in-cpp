//Count Inversions (merge Sort): 
int merge(int arr[], int l, int m, int r)
{
      int count = 0;
      int i = l, j = m+1, k = 0;
      int store[r-l+1] = {0};
      while (i <= m && j <= r) {
          if (arr[i] < arr[j]) {
              store[k++] = arr[i++];
          } else {
              count += (mid-i+1);
              store[k++] = arr[j++];
          }
      }
      while (i <= m) {
          store[k++] = arr[i++];
      }
      while (j <= r) {
          store[k++] = arr[j++];
      }
      k = 0;
      for (int a = l; a <= r; a++) {
          arr[a] = store[k++];
      }
      return count;
}
int mergeSort(int arr[], int l, int r){
    int count = 0;
    if (l < r) {
        int mid = l + (r-l)/2;
        count += mergeSort (arr, l, mid);
        count += mergeSort (arr, mid+1, r);
        count += merge (arr, l, mid, r);
    }
    return count;
}

// Quick Sort :
void quickSort(int arr[], int low, int high)
{
    // code here
    if (low < high) {
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot-1);
        quickSort (arr, pivot+1, high);
    }
}
int partition (int arr[], int low, int high)
{
    // Your code here
    int pivot = arr[high], p = low;
    for (int i = low; i < high; i++) {
        if (arr[i] <= pivot) {
            int temp = arr[i];
            arr[i] = arr[p];
            arr[p++] = temp;
        }
    }
    arr[high] = arr[p];
    arr[p] = pivot;
    return p;
}

//In place mergeSort :
void merge (vector<int>& nums, int st, int mid, int end) {
    int gap = (end-st+1)/2 + (end-st+1)%2;
    while (gap > 0) {
        int i = st, j = st+gap;
        while (j <= end) {
            if (nums[i] > nums[j]) {
                swap (nums[i], nums[j]);
            }
            i++; j++;
        }
        gap = (gap == 1) ? 0 : (gap/2 + gap%2);
    }
}
void mergeSort (vector<int>& nums, int st, int end) {
    if (st < end) {
        int mid = st + (end-st)/2;
        mergeSort (nums, st, mid);
        mergeSort (nums, mid+1, end);
        merge (nums, st, mid, end);
    }
}
vector<int> sortArray(vector<int>& nums) {
    mergeSort (nums, 0, nums.size()-1);
    return nums;
}

//Find maximum sub array using divide and conquer approach
int recSol (vector<int>& nums, int st, int end) {
    if (st == end) return nums[st];
    int mid = st + (end-st)/2;
    int leftRecSum = recSol (nums, st, mid);
    int rightRecSum = recSol (nums, mid+1, end);
    int rightTotalSum = INT_MIN, leftTotalSum = INT_MIN, rightCurrSum = 0, leftCurrSum = 0;
    for (int i = mid; i >= st; i--) {
        leftCurrSum += nums[i];
        if (leftTotalSum < leftCurrSum) leftTotalSum = leftCurrSum;
    }
    for (int i = mid+1; i <= end; i++) {
        rightCurrSum += nums[i];
        if (rightTotalSum < rightCurrSum) rightTotalSum = rightCurrSum;
    }

    int crossSum = leftTotalSum+rightTotalSum;
    return max(leftRecSum, max(rightRecSum, crossSum));
}
int maxSubArray(vector<int>& nums) {
    return recSol (nums, 0, nums.size()-1);
}

