#include <iostream>
#include <cstring>
#include <limits.h>
#include <vector>
using namespace std;

void usageOfMemset (int arr[], int size) {
  memset(arr, 0, size * sizeof(int));
}

void zeroAndOne(int arr[], int size) {
  int ones = 0, zeroes = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i] == 1) {
      ones++;
    } else {
      zeroes++;
    }
  }
  cout << "Zeroes : " << zeroes << endl << "Ones : " << ones << endl;
}

void maxMinInArr(int arr[], int size) {
  int max = INT_MIN;
  int min = INT_MAX;
  for (int i = 0; i < size; i++) {
    if (max < arr[i]) {
      max = arr[i];
    }
    if (min > arr[i]) {
      min = arr[i];
    }
  }
  cout << max << " " << min;
}

void printExtremes (int arr[], int size) {
  int lo = 0, hi = size-1;
  while(lo <= hi) {
    if (lo == hi) {
      cout << arr[lo]; break;
    } 
    cout << arr[lo++] << " ";
    cout << arr[hi--] << " ";
  }
}

void reverse(vector<int> &nums, int start, int endF) {
    int end = endF-1;
    while (start < end) {
        int temp = nums[start];
        nums[start++] = nums[end];
        nums[end--] = temp;
    }
}

void reverse(int nums[], int start, int endF) {
    int end = endF-1;
    while (start < end) {
        int temp = nums[start];
        nums[start++] = nums[end];
        nums[end--] = temp;
    }
}

void rightRotate(vector<int>& nums, int k) {
    if (nums.size() == 1 || k == 0) {
        return;
    }
    reverse(nums, 0, nums.size());
    reverse(nums, 0, (k%nums.size()));
    reverse(nums, k%nums.size(), nums.size());
}

void leftRotate(int arr[], int k, int n) {
    reverse(arr, 0, n);
    reverse(arr, 0, n-(k%n));
    reverse(arr, n-(k%n), n);
} 

void sort012(int a[], int n) {
    int start = 0, end = n-1, i = 0;
    while (i <= end) {
        if (a[i] == 0) {
            int temp = a[start];
            a[start++] = a[i];
            a[i++] = temp;
        } else if (a[i] == 2) {
            int temp = a[end];
            a[end--] = a[i];
            a[i] = temp;
        } else {
            i++;
        }
    }
}

vector<int> printDuplicates(int arr[], int n) {
    // code here
    unordered_map<int, int> store;
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        store[arr[i]]++;
    }
    for (auto i : store) {
        if (i.second > 1) {
            ans.push_back(i.first);
        }
    }
    if (ans.size() == 0) return {-1};
    sort(ans.begin(), ans.end());
    return ans;
}

void segregate0and1(int arr[], int n) {
  // code here
  if (n == 1) {
      return;
  }
  int j = 0, i = 1;
  while (i < n && j < n) {
      if (arr[j] == 1 && arr[i] == 0) {
          int temp = arr[j];
          arr[j++] = arr[i];
          arr[i++] = temp;
      } else if (arr[j] == 1 && arr[i] == 1) {
          i++;
      } else if (arr[j] == 0 && (arr[i] == 1 || arr[i] == 0)) {
          i++; j++;
      }
  }
}

int MissingNumber(vector<int>& array, int n) {
    int sum = ((n) * (n + 1)) / 2;
    for (int i = 0; i < n-1; i++){
        sum -= array[i];
    }
    return sum;
}

int firstRepeated(int arr[], int n) {
    unordered_map<int,int>mp;
    for(int i=0;i<n;i++)
    {
        mp[arr[i]]++;
    }
    for(int i=0;i<n;i++)
    {
        if(mp[arr[i]]>=2)
        return i+1;
    }
    return -1;
}

vector<int> factorialOfLargeNo(int N){
    // code here
    vector<int> ans = {1};
    for (int i = 1; i <= N; i++) {
        int carry = 0;
        for (int j = 0; j < ans.size(); j++) {
            int sum = (i*ans[j]) + carry;
            ans[j] = sum%10;
            carry = sum/10;
        }
        while (carry > 0) {
            ans.push_back(carry%10);
            carry /= 10;
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

vector<int> uniqueArr(int A[], int n) {
    unordered_set<int> unique;
    for (int i = 0; i < n; i++) {
        unique.insert(A[i]);
    }
    vector<int> ans(unique.begin(), unique.end());
    return ans;
}
vector <int> commonElements (int A[], int B[], int C[], int n1, int n2, int n3) {
    unordered_map <int, int> store;
    vector<int> ans;
    vector<int> uniqueA = uniqueArr(A, n1);
    vector<int> uniqueB = uniqueArr(B, n2);
    vector<int> uniqueC = uniqueArr(C, n3);
    for (int i = 0; i < uniqueA.size(); i++) {
        store[uniqueA[i]]++;
    }
    for (int i = 0; i < uniqueB.size(); i++) {
        store[uniqueB[i]]++;
    }
    for (int i = 0; i < uniqueC.size(); i++) {
        store[uniqueC[i]]++;
    }
    for (auto i : store) {
        if (i.second == 3) {
            ans.push_back(i.first);
        }
    }
    if (ans.size() == 0) return {-1};
    sort(ans.begin(), ans.end());
    return ans;
}

int indexWithSameTwoSideSum(vector<int>& nums) {
    int sol = -1;
    int totalSum = 0, leftSum = 0;
    for (int i = 0; i < nums.size(); i++) {
        totalSum += nums[i];
    }
    for (int i = 0; i < nums.size(); i++) {
        if (leftSum*2 == totalSum-nums[i]) {
            return i;
        }
        leftSum += nums[i];
    }
    return sol;
}

int main () {
  
}