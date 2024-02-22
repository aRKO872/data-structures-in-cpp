#include <iostream>
#include <vector>
using namespace std;

int findUnique(vector<int> arr) {           //This approach is very important as it uses XoR operation
  int xorSum = 0;
  for (int i = 0; i < arr.size(); i++) {
    xorSum = xorSum ^ arr[i];
  }
  return xorSum;
}

vector<int> intersection (vector<int> a, vector<int> b, int sizeA, int sizeB) {
  vector<int> inter;
  int i = 0, j = 0;
  if (sizeB < sizeA) {
    while (i < sizeA) {
      if (a[i] == b[j]) {
        inter.push_back(a[i]);
        j++;
      }
      i++;
    }
  } else {
    while (j < sizeB) {
      if (b[j] == a[i]) {
        inter.push_back(b[j]);
        i++;
      }
      j++;
    }
  }
  
  return inter;
}

vector<int> sortedUnion(vector<int> a, vector<int> b, int sizeA, int sizeB) {
  vector<int> sorted;
  int i = 0, j = 0;
  while(i < sizeA && j < sizeB) {
    if (a[i] > b[j]) {
      sorted.push_back(b[j++]);
    } else {
      sorted.push_back(a[i++]);
    }
  }
  while (i < sizeA) {
    sorted.push_back(a[i++]);
  }
  while (j < sizeB) {
    sorted.push_back(b[j++]);
  }
  return sorted;
}

int main () {
  int list1[] = {1, 2, 3, 3, 4, 6, 8};
  int list2[] = {3, 3, 4, 9, 10};
  int size1 = sizeof(list1)/sizeof(int);
  int size2 = sizeof(list2)/sizeof(int);
  vector<int> arr1(list1, list1+size1);
  vector<int> arr2(list2, list2+size2);
  vector<int> res = intersection(arr1, arr2, size1, size2);
  cout << "The intersection is ";
  for (int i = 0; i < res.size(); i++) {
    cout << res[i] << " ";
  }
}

// Next Permutation : Very Important! 
void nextPermutation(vector<int>& nums) {
    int pos = -1;
    for (int i = 0; i < nums.size()-1; i++) {
        if (nums[i] < nums[i+1]) pos = i;
    } 
    
    if (pos == -1) {
        reverse (nums.begin(), nums.end());
    } else {
        int solInd = pos+1, num = INT_MAX;
        for (int i = pos+1; i < nums.size(); i++) {
            if (nums[i] > nums[pos] && nums[i] < num) {
                num = nums[i];
                solInd = i;
            }
        }
        
        swap (nums[solInd], nums[pos]);
        sort (nums.begin()+pos+1, nums.end());
    }
}

// Container with most water : 
int maxArea(vector<int>& height) {
    int st = 0, end = height.size()-1;
    int ans = 0;
    while (st < end) {
        int curr = min(height[st], height[end]) * (end-st);
        ans = max (ans, curr);
        
        if (height[st] > height[end]) {
            end--;
        } else {
            st++;
        }
    }
    
    return ans;
}

// number of pairs divisible by 60 : 
int numPairSumDivisibleBy60(vector<int>& time) {
    unordered_map<int, int> mp;
    int count = 0;
    for (int i = 0; i < time.size(); i++) {
        int a = time[i]%60;
        if (a == 0) {
            count += mp[a];
        } else {
            count += mp[60-a];
        }
        
        mp[a]++;
    }
    
    return count;
}

// find the duplicate number (Leetcode VVVV IMP) : 
int findDuplicate(vector<int>& nums) {
    int fast = nums[nums[0]], slow = nums[0];
    
    while (fast != slow) {
        int tempFast = fast, tempSlow = slow;
        fast = nums[nums[tempFast]]; 
        slow = nums[tempSlow];
    }
    
    slow = 0;
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
    }
    
    return slow;
}

// Maximum Points to obtain from Cards (Sliding Window VV IMP) :
int maxScore(vector<int>& cardPoints, int k) {
    int windowSize = cardPoints.size()-k;
    int i = 0, j = 0, total = 0;
    int sumTotal = 0;
    
    for (auto a: cardPoints)  {
        sumTotal += a;
    }
    
    while (j < windowSize) {
        total += cardPoints[j];
        j++;
    }
    
    int maxI = sumTotal-total;
    
    while (j < cardPoints.size()) {
        total -= cardPoints[i];
        total += cardPoints[j];
        
        maxI = max (maxI, (sumTotal-total));
        
        i++;
        j++;
    }
    
    return maxI;
}

// Maximum Area of a Piece of Cake After Horizontal and Vertical Cuts
int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts) {
    sort (horizontalCuts.begin(), horizontalCuts.end());
    sort (verticalCuts.begin(), verticalCuts.end());
    
    horizontalCuts.push_back(h);
    verticalCuts.push_back(w);
    
    int longestH = horizontalCuts[0], longestW = verticalCuts[0];
    
    for (int i = 0; i < horizontalCuts.size()-1; i++) {
        longestH = max(longestH, horizontalCuts[i+1]-horizontalCuts[i]);
    }
    
    for (int i = 0; i < verticalCuts.size()-1; i++) {
        longestW = max(longestW, verticalCuts[i+1]-verticalCuts[i]);
    }
    int mod = 1e9+7;
    
    long ans = ((long)(longestW%mod)*(long)(longestH%mod))%mod;
    return (int)ans;
}

// find all duplicates in a number (Leetcode VVV IMP!) :
vector<int> findDuplicates(vector<int>& nums) {
    vector<int> ans;
    for (int i = 0; i < nums.size(); i++) {
        int val = abs(nums[i])-1;
        if (nums[val] < 0) ans.push_back(val+1);
        nums[val] = -nums[val];
    }
    return ans;
}

// find K-Diff Pairs (O(n) sol) :
int findPairs(vector<int>& nums, int k) {
    unordered_map<int, int> mp;
    for (auto p: nums) {
        mp[p]++;
    }
    
    int count = 0;
    for (auto p: mp) {
        if (k == 0) {
            if (p.second > 1) count++;
        } else {
            if (mp.find(p.first+k) != mp.end()) count++;
        }
    }
    
    return count;
}

// Find Number of Subarrays divisible by K (VVV IMP!) : 
int subarraysDivByK(vector<int>& nums, int k) {
    unordered_map<int, int> mp;
    mp[0] = 1;
    int total = 0;
    int count = 0;
    for (int i = 0; i < nums.size(); i++) {
        total = ((total+nums[i])%k);
        if (total < 0) total += k;
        count += mp[total];
        mp[total]++;
    }
    
    return count;
}

// Largest Rectangle in a Histogram : 
int largestRectangleArea(vector<int>& heights) {
    vector<int> right; stack<int> rightSt;
    vector<int> left; stack<int> leftSt;
    
    for (int i = 0; i < heights.size(); i++) {
        while (!leftSt.empty() && heights[leftSt.top()] >= heights[i]) {
            leftSt.pop();
        }
        int ele = (leftSt.empty()) ? 0 : leftSt.top()+1;
        left.push_back(ele);
        leftSt.push(i);
    }
    
    for (int i = heights.size()-1; i >= 0; i--) {
        while (!rightSt.empty() && heights[rightSt.top()] >= heights[i]) {
            rightSt.pop();
        }
        int ele = (rightSt.empty()) ? heights.size()-1 : rightSt.top()-1;
        right.push_back(ele);
        rightSt.push(i);
    }
    
    reverse(right.begin(), right.end());
    
    int maxI = 0;
    for (int i = 0; i < heights.size(); i++) {
        int ans = heights[i];
        maxI = max (maxI, (ans*(right[i]-left[i]+1)));
    }
    
    return maxI;
}

// Insert Delete GetRandom O(1) with Duplicates : 
class RandomizedCollection {
public:
    unordered_map<int, vector<int>> mp;
    vector<pair<int, int>> arr;
    RandomizedCollection() {
    }
    
    bool insert(int val) {
        bool result;
        if (mp.find(val) == mp.end()) {
            result = true;
        } else {
            result = false;
        }
        mp[val].push_back(arr.size());
        arr.push_back({val, mp[val].size()-1});
        return result;
    }
    
    bool remove(int val) {
        if (mp.find(val) == mp.end()) return false;
        auto last = arr.back();
        mp[last.first][last.second] = mp[val].back();
        arr[mp[val].back()] = last;
        mp[val].pop_back();
        if(mp[val].empty()) mp.erase(val);
        arr.pop_back();
        return true;
    }
    
    int getRandom() {
        int ind = rand() % arr.size();
        return arr[ind].first;
    }
};

// Find Power of x^n (Important!) : 
double myPow(double x, int n) {
    if (n < 0) {
        x = 1/x;
    }
    long lim = labs(n);
    double sum = 1;
    while (lim > 0) {
        if (lim%2 != 0) {
            sum = sum*x;
        }
        x = x*x;
        lim /= 2;
    }
    return sum;
}