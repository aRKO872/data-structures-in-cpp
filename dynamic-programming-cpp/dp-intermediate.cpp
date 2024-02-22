// 0/1 Knapsack Problem (Top - Down) VVVVV IMPORTANT! : 
int topDown (int W, int wt[], int val[], int n, vector<vector<int>>& dp) {
    if (W <= 0) return 0;
    if (n <= 0) return 0;
    if (dp[W][n] != -1) return dp[W][n];
    int take = 0, notTake = 0;
    if (wt[n-1] <= W) take = val[n-1] + topDown (W-wt[n-1], wt, val, n-1, dp);
    notTake = topDown (W, wt, val, n-1, dp);
    dp[W][n] = max (take, notTake);
    return dp[W][n];
}
int bottomUp (int W, int wt[], int val[], int n, vector<vector<int>>& dp) {
    for (int i = 0; i <= n; i++) dp[0][i] = 0;
    for (int i = 0; i <= W; i++) dp[i][0] = 0;
    
    for (int i = 1; i <= W; i++) {
        for (int j = 1; j <= n; j++) {
            int take = 0, notTake = 0;
            if (wt[j-1] <= i) take = val[j-1] + dp[i-wt[j-1]][j-1];
            notTake = dp[i][j-1];
            dp[i][j] = max (take, notTake);
        }
    }
    return dp[W][n];
}
int knapSack(int W, int wt[], int val[], int n) 
{ 
    // Your code here
    vector<vector<int>> dp (W+1, vector<int> (n+1, -1));
    return bottomUp (W, wt, val, n, dp);
}

// Subset Sum Problem (VVVVVVVV Important!!!) : 
bool subsetExists (vector<int>& arr, int index, int target, vector<vector<int>>& dp) {
    if (target == 0) return true;
    if (index == 0) return false;
    if (dp[index-1][target] != -1) return dp[index-1][target];
    if (target >= arr[index-1]) return dp[index-1][target] = (subsetExists (arr, index-1, target-arr[index-1], dp) || subsetExists (arr, index-1, target, dp));
    else return dp[index-1][target] = subsetExists (arr, index-1, target, dp);
}
bool bottomUp (vector<int>& arr, int sum, int index, vector<vector<int>>& dp) {
    for (int i = 0; i <= index; i++) dp[0][i] = 1;
    for (int i = 1; i <= sum; i++) dp[i][0] = 0;
    
    for (int i = 1; i <= sum; i++) {
        for (int j = 1; j <= index; j++) {
            if (arr[j-1] <= i) dp[i][j] = dp[i-arr[j-1]][j-1] || dp[i][j-1];
            if (arr[j-1] > i) dp[i][j] = dp[i][j-1];
        }
    }
    return dp[sum][index];
}
bool isSubsetSum(vector<int>arr, int sum){
    vector<vector<int>> dp (arr.size()+1, vector<int> (sum+1, -1));
    return subsetExists (arr, arr.size(), sum, dp);
}

// Partition Equal Subset Sum (VVVVV Important) : 
bool partitionRec (vector<int>& nums, int index, int sumTotal, vector<vector<int>>& dp) {
    if (index == 0) return false;
    if (sumTotal == 0) return true;
    if (dp[index-1][sumTotal] != -1) return dp[index-1][sumTotal];
    if (sumTotal >= nums[index-1]) return dp[index-1][sumTotal] = (partitionRec (nums, index-1, sumTotal-nums[index-1], dp) || partitionRec (nums, index-1, sumTotal, dp));
    else return dp[index-1][sumTotal] = partitionRec (nums, index-1, sumTotal, dp);
}
bool canPartition(vector<int>& nums) {
    int total = 0; 
    for (auto i : nums) total += i;
    if (total%2 != 0) return false;
    vector<vector<int>> dp (nums.size()+1, vector<int> ((total/2)+1, -1));
    return partitionRec (nums, nums.size(), total/2, dp);
}

// Minimum Sum Difference (Divide array into two halves such that subsets have minimum difference) (VVVVVVV IMP!): 
int minDiffRec (int arr[], int n, int leftSub, int rightSub, auto& map) {
    if (n < 0) return abs (leftSub-rightSub);
    if (map.find(to_string(leftSub) + to_string(n)) != map.end()) return map[to_string(leftSub) + to_string(n)];
    int s1 = minDiffRec (arr, n-1, leftSub+arr[n], rightSub, map);
    int s2 = minDiffRec (arr, n-1, leftSub, rightSub+arr[n], map);
    map[to_string(leftSub) + to_string(n)] = min (s1, s2);
    return map[to_string(leftSub) + to_string(n)];
}
int minDifference(int arr[], int n)  { 
    unordered_map <string, int> map;
    return minDiffRec (arr, n-1, 0, 0, map);
} 

// Another Approach for Minimum Sum Difference : 
bool bottomUp (int arr[], int sum, int index, vector<vector<int>>& dp) {
    for (int i = 0; i <= index; i++) dp[0][i] = 1;
    for (int i = 1; i <= sum; i++) dp[i][0] = 0;
    
    for (int i = 1; i <= sum; i++) {
        for (int j = 1; j <= index; j++) {
            if (arr[j-1] <= i) dp[i][j] = dp[i-arr[j-1]][j-1] || dp[i][j-1];
            if (arr[j-1] > i) dp[i][j] = dp[i][j-1];
        }
    }
}
int minDifference(int arr[], int n)  { 
    // Your code goes here
    int sum = accumulate (arr, arr+n, 0);
    vector<vector<int>> dp (sum+1, vector<int> (n+1, -1));
    bottomUp (arr, sum, n, dp);
    int half = sum/2;
    int lowerHalf = 0;
    for (int i = 0; i <= half; i++) {
        if (dp[i][n]) lowerHalf = i;
    }
    return (sum- (2*lowerHalf));
} 

// Number of Dice Rolls with Target Sum (Important!) : 
long long mod = 1e9+7;
// Top Down Approach
long long recSol (int n, int k, int target, vector<vector<long long>>& dp) {
    if (n < 0) return 0;
    if (n == 0 && target == 0) return 1;
    if (n != 0 && target == 0) return 0;
    if (n == 0 && target < 0) return 0;
    if (dp[n][target] > -1) return dp[n][target];
    long long ways = 0;
    for (int i = 1; i <= k; i++) {
        if (target-i >= 0) ways = (ways%mod) + (recSol (n-1, k, target-i, dp))%mod;
    }
    dp[n][target] = ways%mod;
    return dp[n][target];
}

// Bottom Up approach
long long bottomUp (int n, int k, int target, vector<vector<long long>>& dp) {
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) dp[i][0] = 0;
    for (int i = 1; i <= target; i++) dp[0][i] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= target; j++) {
            long long ways = 0;
            for (int l = 1; l <= k; l++) {
                if (j-l >= 0) ways = (ways%mod) + (dp [i-1][j-l])%mod;
            }
            dp[i][j] = ways%mod;
        }
    }
    return dp[n][target];
}

int numRollsToTarget(int n, int k, int target) {
    vector<vector<long long>> dp (n+1, vector<long long> (target+1, -1));
    return recSol (n, k, target, dp);
}

// Minimum Swaps to make Subsequences Increasing (Top Down Approach) VVVVVVV IMPORTANT: 
int recSol (vector<int> nums1, vector<int> nums2, int index, int swapped, vector<vector<int>>& dp) {
    if (index == nums1.size()) return 0;

    if (dp[index][swapped] != -1) return dp[index][swapped];

    int prev1 = nums1[index-1];
    int prev2 = nums2[index-1];

    if (swapped) {
        swap (prev1, prev2);
    }

    int minSwaps = INT_MAX;

    if (nums1[index] > prev1 && nums2[index] > prev2) minSwaps = recSol (nums1, nums2, index+1, 0, dp);
    
    if (nums1[index] > prev2 && nums2[index] > prev1) minSwaps = min(minSwaps, 1 + recSol (nums1, nums2, index+1, 1, dp));

    return dp[index][swapped] = minSwaps;
}
int minSwap(vector<int>& nums1, vector<int>& nums2) {
    nums1.insert (nums1.begin(), -1);
    nums2.insert (nums2.begin(), -1);
    vector<vector<int>> dp (nums1.size()+1, vector<int> (2, -1));
    return recSol (nums1, nums2, 1, 0, dp);
}

// Minimum Swaps to make Subsequences Increasing (Bottom Up Approach) VVVVVVV IMPORTANT: 
int tabSol (vector<int>& nums1, vector<int>& nums2) {
    vector<vector<int>> dp (nums1.size()+1, vector<int> (2, 0));
    for (int i = nums1.size()-1; i >= 1; i--) {
        for (int j = 1; j >= 0; j--) {
            int prev1 = nums1[i-1];
            int prev2 = nums2[i-1];

            if (j == 1) {
                swap (prev1, prev2);
            }

            int minSwaps = INT_MAX;

            if (nums1[i] > prev1 && nums2[i] > prev2) minSwaps = dp[i+1][0];
            if (nums1[i] > prev2 && nums2[i] > prev1) minSwaps = min(minSwaps, 1 + dp[i+1][1]);
            dp[i][j] = minSwaps;
        }
    }
    return dp[1][0];
}
int minSwap(vector<int>& nums1, vector<int>& nums2) {
    nums1.insert (nums1.begin(), -1);
    nums2.insert (nums2.begin(), -1);
    return tabSol (nums1, nums2);
}

// Minimum Swaps to make Sequences Increases : 
int recSol (vector<int>& nums1, vector<int>& nums2, int index, int swapped, vector<vector<int>>& dp) {
    if (index == nums1.size()) return 0;
    if (dp[index][swapped] != -1) return dp[index][swapped];

    int prev1 = nums1[index-1];
    int prev2 = nums2[index-1];

    if (swapped == 1) {
        prev1 = nums2[index-1];
        prev2 = nums1[index-1];
    } 

    int minVal = INT_MAX;

    if (nums1[index] > prev1 && nums2[index] > prev2) {
        minVal = recSol (nums1, nums2, index+1, 0, dp);
    }

    if (nums1[index] > prev2 && nums2[index] > prev1) {
        minVal = min (minVal, 1 + recSol (nums1, nums2, index+1, 1, dp));
    }

    return dp[index][swapped] = minVal;
}

int bottomUp (vector<int>& nums1, vector<int>& nums2) {
    vector<vector<int>> dp (nums1.size()+1, vector<int> (2, 0));

    for (int i = nums1.size()-1; i >= 1; i--) {
        for (int j = 0; j <= 1; j++) {

            int prev1 = nums1[i-1];
            int prev2 = nums2[i-1];

            if (j == 1) {
                prev1 = nums2[i-1];
                prev2 = nums1[i-1];
            } 

            int minVal = INT_MAX;

            if (nums1[i] > prev1 && nums2[i] > prev2) {
                minVal = dp[i+1][0];
            }

            if (nums1[i] > prev2 && nums2[i] > prev1) {
                minVal = min (minVal, 1 + dp[i+1][1]);
            }

            dp[i][j] = minVal;

        }
    }

    return dp[1][0];
}

int minSwap(vector<int>& nums1, vector<int>& nums2) {
    nums1.insert (nums1.begin(), -1);
    nums2.insert (nums2.begin(), -1);

    vector<vector<int>> dp (nums1.size()+1, vector<int> (2, -1));

    return bottomUp (nums1, nums2);
}

// Perfect Squares :
int recSol (int n, vector<int>& dp) {
    if (n == 0) return 0;
    if (n < 0) return INT_MAX;

    if (dp[n] != -1) return dp[n];

    int minI = INT_MAX, sq = 1;
    for (int i = sq; i*i <= n; i++) {
        minI = min (minI, 1 + recSol (n-(i*i), dp));
    }

    return dp[n] = minI;
}

int bottomUp (int n) {
    vector<int> dp (n+1, 0);

    for (int i = 1; i <= n; i++) {
        int minI = INT_MAX;

        for (int k = 1; k*k <= n; k++) {
            if (i-(k*k) >= 0) minI = min (minI, 1 + dp[i-(k*k)]);
        }

        dp[i] = minI;
    }

    return dp[n];
}

int numSquares(int n) {
    vector<int> dp (n+1, -1);
    return bottomUp (n);
}

// Reducing Dishes Leetcode : 
int recSol (vector<int>& arr, int index, int time) {
    if (index >= arr.size()) return 0;

    return max (recSol (arr, index+1, time), arr[index]*time + recSol (arr, index+1, time+1));
}

int tabulate (vector<int>& arr, vector<vector<int>>& dp) {
    for (int i = arr.size()-1; i >= 0; i--) {
        for (int j = arr.size(); j >= 1; j--) {
            dp[i][j] = max (dp[i+1][j], arr[i]*j + dp[i+1][j+1]);
        }
    }

    return dp[0][1];
}

int maxSatisfaction(vector<int>& satisfaction) {
    sort (satisfaction.begin(), satisfaction.end());
    // return recSol (satisfaction, 0, 1);
    vector<vector<int>> dp (satisfaction.size()+1, vector<int> (satisfaction.size()+2, 0));
    return tabulate (satisfaction, dp);
}

// Ones and Zeroes Leetcode : 
pair<int, int> find0And1 (string str) {
    int zero = 0, one = 0;
    for (auto i: str) {
        if (i == '1') one++;
        else zero++;
    }
    return {zero, one};
}

int recSol (vector<string>& strs, int index, int m, int n) {
    if (index == strs.size()) return 0;

    pair<int, int> check = find0And1 (strs[index]);
    int zero = check.first;
    int one = check.second;

    if (zero > m || one > n) {
        return recSol (strs, index+1, m, n);
    }
    return max (recSol (strs, index+1, m, n), 1 + recSol (strs, index+1, m-zero, n-one));
}

int tabulate (vector<string>& strs, int m, int n) {
    vector<vector<vector<int>>> dp (strs.size()+1, vector<vector<int>> (m+1, vector<int> (n+1, 0)));

    for (int i = strs.size()-1; i >= 0; i--) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= n; k++) {

                pair<int, int> check = find0And1 (strs[i]);
                int zero = check.first;
                int one = check.second;

                if (zero > j || one > k) dp[i][j][k] = dp[i+1][j][k];
                else dp[i][j][k] = max (dp[i+1][j][k], 1 + dp[i+1][j-zero][k-one]);

            }
        }
    }

    return dp[0][m][n];
}

int findMaxForm(vector<string>& strs, int m, int n) {
    // return recSol (strs, 0, m, n);
    return tabulate (strs, m, n);
}

// Predict The Winner (Leetcode) :
int recSol (vector<int>& nums, int st, int end) {
    if (st == end) return nums[st];

    int takeStart = nums[st] - recSol (nums, st+1, end);
    int takeEnd = nums[end] - recSol (nums, st, end-1);

    return max (takeStart, takeEnd);
}
bool tabulate (vector<int>& nums) {
    vector<vector<int>> dp (nums.size()+1, vector<int> (nums.size()+1, 0));
    for (int i = 0; i < nums.size(); i++) {
        dp[i][i] = nums[i];
    }

    for (int i = nums.size()-1; i >= 0; i--) {
        for (int j = 0; j < nums.size(); j++) {
            if (i < j) {
                int takeStart = 0, takeEnd = 0;
                takeStart = nums[i] - recSol (nums, i+1, j);
                takeEnd = nums[j] - recSol (nums, i, j-1);

                dp[i][j] = max (takeStart, takeEnd);
            }
        }
    }

    return dp[0][nums.size()-1] >= 0 ? true : false;
}
bool predictTheWinner(vector<int>& nums) {
    // int dec = recSol (nums, 0, nums.size()-1);
    // return dec >= 0 ? true : false;
    return tabulate (nums);
}

// Egg Dropping Problem - VVVV Important : 
int eggDrop(int n, int k) {
    // your code here
    // if (k == 0 || k == 1) return k;
    // if (n == 0 || n == 1) return k;
    
    // int minI = INT_MAX;
    
    // for (int i = 1; i <= k; i++) {
    //     int breaks = eggDrop (n-1, i-1);
    //     int notBreaks = eggDrop (n, k-i);
        
    //     int maxI = max (breaks, notBreaks);
    //     if (maxI != INT_MAX) {
    //         minI = min(minI, 1 + maxI);
    //     }
    // }
    
    // return minI;
    
    vector<vector<int>> dp (n+1, vector<int> (k+1, 0));
    for (int i = 0; i <= n; i++) {
        dp[i][1] = 1;
    }
    for (int i = 0; i <= k; i++) {
        dp[1][i] = i;
        dp[0][i] = i;
    }
    
    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= k; j++) {
            int minI = INT_MAX;
    
            for (int a = 1; a <= j; a++) {
                int breaks = dp[i-1][a-1];
                int notBreaks = dp[i][j-a];
                
                int maxI = max (breaks, notBreaks);
                if (maxI != INT_MAX) {
                    minI = min(minI, 1 + maxI);
                }
            }
            
            dp[i][j] = minI;
        }
    }
    
    return dp[n][k];
}

// Maximum Length of Repeated Subarray (VVV Imp):
int recSol (vector<int>& nums1, vector<int>& nums2, int ind1, int ind2, vector<vector<int>>& dp, int& ans) {
    if (ind1 == nums1.size()) return 0;
    if (ind2 == nums2.size()) return 0;
    if (dp[ind1][ind2] != -1) return dp[ind1][ind2];
    
    recSol (nums1, nums2, ind1 + 1, ind2, dp, ans);
    recSol (nums1, nums2, ind1, ind2 + 1, dp, ans);
    
    dp[ind1][ind2] = (nums1[ind1] == nums2[ind2]) ? 1 + recSol (nums1, nums2, ind1+1, ind2+1, dp, ans) : 0;
    
    ans = max (dp[ind1][ind2], ans);
    return dp[ind1][ind2];
}

int findLength(vector<int>& nums1, vector<int>& nums2) {
    vector<vector<int>> dp (nums1.size()+1, vector<int> (nums2.size()+1, -1));
    dp[nums1.size()][nums2.size()] = 0;
    int ans = 0;
    recSol (nums1, nums2, 0, 0, dp, ans);
    return ans;
} 

// Range Sum 2D Query (Leetcode) :
class NumMatrix {
public:
    vector<vector<int>> dp;
    NumMatrix(vector<vector<int>>& matrix) {
        dp = vector<vector<int>> (matrix.size()+1, vector<int> (matrix[0].size()+1, 0));
        
        for (int i = 1; i < dp.size(); i++) {
            int prefix = 0;
            for (int j = 1; j < dp[0].size(); j++) {
                prefix += matrix[i-1][j-1];
                int above = dp[i-1][j];
                dp[i][j] = prefix+above;
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return dp[row2+1][col2+1] - dp[row1][col2+1] - dp[row2+1][col1] + dp[row1][col1];
    }
};

// Longest Arithmetic Subsequence - TopDown (VVV IMPORTANT!!) : 
int recSol (vector<int>& nums, int ind, int diff, vector<unordered_map<int, int>>& dp) {
    if (ind < 0) return 0;
    if (dp[ind].count(diff)) return dp[ind][diff];
    
    int ans = 0;
    for (int i = ind-1; i >= 0; i--) {
        if (nums[i] - nums[ind] == diff) {
            ans = max (ans, 1 + recSol (nums, i, diff, dp));
        }
    }
    
    return dp[ind][diff] = ans;
}

int longestArithSeqLength(vector<int>& nums) {
    int count = 0;
    int lowest = INT_MAX, highest = INT_MIN;
    
    vector<unordered_map<int, int>> dp (nums.size()+1, unordered_map<int, int> ());
    
    for (int i = 0; i < nums.size()-1; i++) {
        for (int j = i+1; j < nums.size(); j++) {
            count = max (count, 2 + recSol (nums, i, nums[i]-nums[j], dp));
        }
    }
    
    return count;
}

// Longest Arithmetic Subsequence (Bottom Up) :
int longestArithSeqLength(vector<int>& nums) {
    int count = 0;
    int lowest = INT_MAX, highest = INT_MIN;
    
    vector<unordered_map<int, int>> dp (nums.size()+1, unordered_map<int, int> ());
    int ans = 0;
    
    for (int i = 1; i < nums.size(); i++) {
        for (int j = 0; j < i; j++) {
            int diff = nums[i] - nums[j];
            int count = 1;
            
            if (dp[j].count(diff)) count = dp[j][diff];
            
            dp[i][diff] = count+1;
            ans = max (ans, dp[i][diff]);
        }
    }
    
    return ans;
}

// Regular Expression Matching (Leetcode VVV IMP!) :
bool recSol (string s, string p, int indS, int indP, vector<vector<int>>& dp) {
    if (indS < 0 && indP < 0) return true;
    if (indP < 0 && indS >= 0) return false;
    
    if (indS < 0 && indP >= 0 && p[indP] == '*') {
        while (indP >= 0) {
            if (p[indP] != '*') return false;
            indP -= 2;
        }
        return true;
    }
    
    if (indS < 0 && indP >= 0) return false;
    if (dp[indS][indP] != -1) return dp[indS][indP];
    
    if (s[indS] == p[indP] || p[indP] == '.') return dp[indS][indP] = recSol (s, p, indS-1, indP-1, dp);
    else if (p[indP] == '*') {
        if (p[indP-1] != s[indS] && p[indP-1] != '.') return dp[indS][indP] = recSol (s, p, indS, indP-2, dp);
        else {
            // First for multiple occurence, second for single occurence, third for no occurence
            return dp[indS][indP] = (
                recSol (s, p, indS-1, indP, dp) ||
                recSol (s, p, indS, indP-1, dp) ||
                recSol (s, p, indS, indP-2, dp)
            );
        }
    }
    
    return dp[indS][indP] = false;
}
bool isMatch(string s, string p) {
    vector<vector<int>> dp (s.size()+1, vector<int> (p.size()+1, -1));
    return recSol (s, p, s.size()-1, p.size()-1, dp);
}

// Minimum Difficulty Of a Job Schedule : 
int recSol (vector<int>& arr, int ind, int d, vector<vector<int>>& dp) {
    if (dp[ind][d] != -1) return dp[ind][d];
    if (d == 1) {
        int maxI = 0;
        for (int i = ind; i < arr.size(); i++) {
            maxI = max (maxI, arr[i]);
        }
        return dp[ind][d] = maxI;
    }
    
    int ans = INT_MAX;
    int maxI = 0;
    for (int i = ind; i < arr.size()-(d-1); i++) {
        maxI = max(maxI, arr[i]);
        ans = min (ans, maxI + recSol (arr, i+1, d-1, dp));
    }
    
    return dp[ind][d] = ans;
}
int minDifficulty(vector<int>& arr, int d) {
    if (arr.size() < d) return -1;
    vector<vector<int>> dp (arr.size()+1, vector<int> (d+1, -1));
    int ans = recSol (arr, 0, d, dp);
    return (ans == INT_MAX) ? -1 : ans; 
}

// Frog Jump Leetcode (VVV IMP!) :
bool recSol (vector<int>& stones, int ind, int prevJump, vector<unordered_map<int, bool>>& dp) {
    if (ind == stones.size()-1) return true;
    if (dp[ind].count(prevJump)) return dp[ind][prevJump];
    
    if (prevJump == 0) {
        if (stones[ind+1] != stones[ind]+1) return dp[ind][prevJump] = false;
        else return dp[ind][prevJump] = recSol (stones, ind+1, 1, dp);
    } else {
        
        int newInd = ind+1;
        while (newInd < stones.size() && stones[newInd] <= stones[ind]+prevJump+1) {
            bool flag = false;
            if (stones[newInd]-stones[ind] == prevJump) flag = flag || recSol (stones, newInd, prevJump, dp);
            if (stones[newInd]-stones[ind] == prevJump-1) flag = flag ||  recSol (stones, newInd, prevJump-1, dp);
            if (stones[newInd]-stones[ind] == prevJump+1) flag = flag ||  recSol (stones, newInd, prevJump+1, dp);
            
            if (flag) return dp[ind][prevJump] = true;
            newInd++;
        }
        
        return dp[ind][prevJump] = false;
    }
}
bool canCross(vector<int>& stones) {
    vector<unordered_map<int, bool>> dp (stones.size()+1, unordered_map<int, bool> ());
    return recSol (stones, 0, 0, dp);
}