#include <iostream>
#include <utility>
#include <vector>
using namespace std;

long long firstOccurence (vector<long long> v, long long x) {
    long long start = 0, end = v.size()-1, result = -1;
    while (start <= end) {
        long long mid = start + ((end-start)/2);
        if (v[mid] == x) {
            result = mid;
            end = mid-1;
        } else if (v[mid] < x) {
            start = mid+1;
        } else {
            end = mid-1;
        }
    }
    return result;
}
long long lastOccurence (vector<long long> v, long long x) {
    long long start = 0, end = v.size()-1, result = -1;
    while (start <= end) {
        long long mid = start + ((end-start)/2);
        if (v[mid] == x) {
            result = mid;
            start = mid+1;
        } else if (v[mid] > x) {
            end = mid-1;
        } else {
            start = mid+1;
        }
    }
    return result;
}
pair<long,long> indexes(vector<long long> v, long long x) {
    // code here
    return pair<long, long>{firstOccurence(v, x), lastOccurence(v, x)};
}

pair<long, long> indexesUsingFunction(vector<long long> v, long long x) {
  return pair<long, long>{lower_bound(v.begin(), v.end(), x)-v.begin(), upper_bound(v.begin(), v.end(), x)-v.begin()};
}

bool exists (int arr[], int n, int target) {
   return binary_search(arr, arr+n, target);
}

bool existsVector (vector<int> arr, int target) {
  return binary_search(arr.begin(), arr.end(), target);
}

int findPeakElement(vector<int>& nums) {
    int st = 0, end = nums.size()-1;
    while (st < end) {
        int mid = st + ((end-st)/2);
        if (nums[mid] < nums[mid+1]) {
            st = mid+1;
        } else if (nums[mid] > nums[mid+1]) {
            end = mid;
        }
    }
    return st;
}

int binarySearch(vector<int>& nums, int target, int st, int end) {
    while (st <= end) {
        int mid = st + ((end-st)/2);
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] > target) {
            end = mid-1;
        } else {
            st = mid+1;
        }
    }
    return -1;
}
int pivotElement(vector<int>& nums) {
    int st = 0, end = nums.size()-1;
    while (st < end) {
        int mid = st + ((end-st)/2);
        if (mid+1 < nums.size() && nums[mid] > nums[mid+1]) {
            return mid;
        }
        if (mid-1 >= 0 && nums[mid-1] > nums[mid]) {
            return mid-1;
        }
        if (nums[mid] >= nums[end]) {
            st = mid+1;
        } else {
            end = mid-1;
        }
        // Or you can do it this way :
        // if (nums[mid] <= nums[st]) {
        //     end = mid-1;
        // } else {
        //     st = mid+1;
        // }
    }
    return -1;
}
int search(vector<int>& nums, int target) {
    int pivot = pivotElement(nums);
    cout << pivot;
    int leftSearch = binarySearch(nums, target, 0, pivot);
    int rightSearch = binarySearch(nums, target, pivot+1, nums.size()-1);
    return (leftSearch+rightSearch+1);
}

float mySqrt(int x, int precision) {
    int st = 1, end = x;
    float res = 0;
    while (st <= end) {
      int mid = st + (end-st)/2;
      if ((long)mid*mid <= (long)x) {
        res = mid;
        st = mid+1;
      } else {
        end = mid-1;
      }
    }
    if (res*res == x) {
      return res;
    }
    
    float inc = 0.1;
    for (int i = 0; i < precision; i++) {
        while ((double)res*res <= (double)x) {
            res += inc;
        }
        res -= inc;
        inc /= 10;
    }
    return res;
}

bool search(vector<vector<int> > matrix, int n, int m, int x) {
    // code here 
    int i = 0, j = m-1;
    while (i < n && j >= 0) {
        if (matrix[i][j] == x) {
            return true;
        } else if (matrix[i][j] < x) {
            i++;
        } else {
            j--;
        }
    }
    return false;
}

bool searchInNearlySortedArr (vector<int> arr, int target) {
  int st = 0, end = arr.size()-1;
  while (st <= end) {
    int mid = st + (end-st)/2;
    if (arr[mid] == target) {
      return true;
    }
    if (mid-1 >= 0 && arr[mid-1] == target) {
      return true;
    }
    if (mid+1 < arr.size() && arr[mid+1] == target) {
      return true;
    }
    if (arr[mid] > target) {
      end = mid-2;
    } else {
      st = mid+2;
    }
  }
  return false;
}

int division(int dividend, int divisor) {
    if (dividend == 0) {
        return INT_MAX;
    }
    int st = 1, end = dividend, res = 0;
    while (st <= end) {
        int mid = st + (end-st)/2;
        if ((long)(abs(mid*divisor)) <= (long)(abs(dividend))) {
            res = mid;
            st = mid+1;
        } else if ((long)(abs(mid*divisor)) > (long)(abs(dividend)))  {
            end = mid-1;
        }
    }
    res = ((dividend < 0 && divisor < 0) || (dividend > 0 && divisor > 0)) ? res : -res;
    return res;
}

int findOdd (vector<int> arr) {
    int st = 0, end = arr.size()-1;
    while (st <= end) {
        if (st == end) {
            return arr[st];
        }
        int mid = st + (end-st)/2;
        if (mid%2 == 0) {
            if (arr[mid] == arr[mid+1]) {
                st = mid+2;
            } else {
                end = mid;
            }
        } else if (mid%2 != 0) {
            if (arr[mid] == arr[mid-1]) {
                st = mid+1;
            } else {
                end = mid-1;
            }
        }
    }
    return -1;
}

int main () {
  int arr[] = {3, 4, 5, 6, 7, 1, 2};
  cout << findPivotElement(arr, 7);
  return 0;
}