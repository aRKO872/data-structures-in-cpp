#include <iostream>
#include <utility>
#include <vector>
using namespace std;

//Ternary Search (VVV Important)
int search (int arr[], int low, int high, int K) {
    if (low > high) {
        return -1;
    }
    int mid1 = low + (high-low)/3;
    int mid2 = high - (high-low)/3;
    if (arr[mid1] == K) return 1;
    if (arr[mid2] == K) return 1;
    if (K < arr[mid1]) return search (arr, low, mid1-1, K);
    else if (K > arr[mid2]) return search (arr, mid2+1, high, K);
    else return search (arr, mid1+1, mid2-1, K);
}
int ternarySearch(int arr[], int N, int K) 
{ 
    // Your code here
    int low = 0, high = N-1;
    return search (arr, low, high, K);
}

//First Occurence of element
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

int findPairs(vector<int>& nums, int k) {
    set<pair<int, int>> store;
    sort(nums.begin(), nums.end());
    int st = 0, end = 1;
    while (end < nums.size()) {
        int diff = nums[end]-nums[st];
        if (diff == k) {
            store.insert({nums[st], nums[end]});
            st++; end++;
        } else if (diff > k) {
            st++;
        } else {
            end++;
        }
        if (st == end) end++;
    }
    return store.size();
}

vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    int st = 0, end = arr.size()-1;
    while (end-st+1 != k) {
        if (x-arr[st] > arr[end]-x) {
            st++;
        } else {
            end--;
        }
    }
    vector<int> ans;
    for (int i = st; i <= end; i++) {
        ans.push_back(arr[i]);
    }
    return ans;
}

// Koko eats bananas problem starts from here to min-eating speed. I used exponential binary search.

long long hoursTakenToEatBananas (vector<int>& piles, int speed) {
    long long countHours = 0;
    for (int i = 0; i < piles.size(); i++) {
        countHours += (piles[i]/speed);
        if (piles[i]%speed > 0) {
            countHours++;
        }
    }
    return countHours;
}
int minEatingSpeed(vector<int>& piles, int h) {
    int end = -1;
    for (int i = 0; i < piles.size(); i++) {
        if (end < piles[i]) {
            end = piles[i];
        }
    }
    int st = 1, res = 0;
    while (st <= end) {
        int mid = st + (end-st)/2;
        if ((long long)hoursTakenToEatBananas(piles, mid) <= (long long)h) {
            res = mid;
            end = mid-1;
        } else {
            st = mid+1;
        }
    }
    return res;
}

//Aggressive Cows :
bool isPossibleSol (vector<int> &arr, int n, int k, long long minDist) {
    int c = 1;
    int cow1Pos = 0, cow2Pos = 1;
    while (cow2Pos < n) {
        if (arr[cow2Pos] - arr[cow1Pos] >= minDist) {
            c++;
            cow1Pos = cow2Pos;
        }
        cow2Pos++;
        if (c == k) {
            return true;
        }
    }
    return false;
}
int solve(int n, int k, vector<int> &stalls) {
    // Write your code here
    sort(stalls.begin(), stalls.end());
    long long st = 0, res = -1;
    long long end = stalls[n-1] - stalls[0];
    while (st <= end) {
        long long mid = st + (end-st)/2;
        if (isPossibleSol(stalls, n, k, mid)) {
            res = mid;
            st = mid+1;
        } else {
            end = mid-1;
        }
    }
    return res;
}

// Book allocation
bool isPossibleSol (int A[], int N, int M, int total) {
    int c = 1, acc = 0;
    for (int i = 0; i < N; i++) {
        if (A[i] > total) {
            return false;
        }
        if (acc+A[i] > total) {
            c++;
            acc = A[i];
            if (c > M) {
                return false;
            }
        } else {
            acc += A[i];
        }
    }
    return true;
}
//Function to find minimum number of pages.
int findPages(int A[], int N, int M) 
{
    if (M > N) {
        return -1;
    }
    int total = accumulate(A, A+N, 0);
    int st = 0, end = total, res = -1;
    while (st <= end) {
        int mid = st + (end-st)/2;
        if (isPossibleSol(A, N, M, mid)) {
            res = mid;
            end = mid-1;
        } else {
            st = mid+1;
        }
    }
    return res;
}

// Painter Partition Problem
bool isPossibleSol (int arr[], int n, int k, long long totalHrs) {
    int p = 1;
    long long sumHrs = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > totalHrs) {
            return false;
        }
        if ((long long)(arr[i]+sumHrs) > totalHrs) {
            p++;
            sumHrs = arr[i];
            if (p > k) {
                return false;
            }
        } else {
            sumHrs += arr[i];
        }
    }
    return true;
}
long long minTime(int arr[], int n, int k)
{
    // code here
    // return minimum time
    long long st = 0, end = 0, res = 0;
    for (int i = 0; i < n; i++) {
        end += arr[i];
    }
    while (st <= end) {
        long long mid = st + (end-st)/2;
        if (isPossibleSol (arr, n, k, mid)) {
            res = mid;
            end = mid-1;
        } else {
            st = mid+1;
        }
    }
    return res;
}

//EKO SPOJ

long long getChoppedWood (vector<long long> arr, long long ht, int n){
	long long choppedAmt = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i] <= ht) {
			continue;
		}
		choppedAmt += (arr[i]-ht);
	}
	return choppedAmt;
}

int ekoSpoj(vector<long long> arr, int m, int n) {
	// your code here
	long long end = INT_MIN;
	for (int i = 0; i < n; i++) {
		end = max(end, arr[i]);
	}
	long long st = 0, res = 0;
	while (st <= end) {
		long long mid = st + (end-st)/2;
		if (getChoppedWood (arr, mid, n) >= m) {
			res = mid;
			st = mid+1;
		} else {
			end = mid-1;
		}
	}
	return res;
}

//ROTI PRATA SPOJ
bool isPossibleSol(vector<int> arr, int P, long long mid) {
	long long countP = 0;
	for (int i = 0; i < arr.size(); i++) {
	    long long j = 1, sum = 0;
		while (sum + (arr[i]*j) <= mid) {
		    sum += (arr[i]*j);
			j++; countP++;
		}
		if (countP >= P) return true;
	}
	return false;
}

int rotiPrata(vector<long long> arr, int P, int size) {
    sort (arr.begin(), arr.end());
    long long end = INT_MIN;
    for (int i = 0; i < size; i++) {
        end = max(end, arr[i]);
    }
    end = end*(P*(P+1))/2;
    long long st = 0, res = 0;
    while (st <= end) {
        long long mid = st + (end-st)/2;
        if (possibleSol(arr, mid, P)) {
            res = mid;
            end = mid-1;
        } else {
            st = mid+1;
        }
    }
    return res;
}

int main () {
  int arr[] = {3, 4, 5, 6, 7, 1, 2};
  cout << findPivotElement(arr, 7);
  return 0;
}

// Median of Two Sorted Arrays
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int n1 = nums1.size(), n2 = nums2.size();
    if (n1 > n2) return findMedianSortedArrays(nums2, nums1);
    
    int st = 0, end = n1;
    int left = (n1 + n2 + 1) / 2;
    int n = n1+n2;
    while (st <= end) {
        int mid1 = (end+st)/2;
        int mid2 = left - mid1;
        int l1 = INT_MIN, l2 = INT_MIN;
        int r1 = INT_MAX, r2 = INT_MAX;
        if (mid1 < n1) r1 = nums1[mid1];
        if (mid2 < n2) r2 = nums2[mid2];
        if (mid1-1 >= 0) l1 = nums1[mid1-1];
        if (mid2-1 >= 0) l2 = nums2[mid2-1];
        
        if (l1 <= r2 && l2 <= r1) {
            if (n%2 == 1) return max (l1, l2);
            double total = max (l1, l2) + min (r1, r2);
            return (total/2.0);
        } else if (l1 > r2) end = mid1-1;
        else st = mid1+1;
    }
    return 0;
}