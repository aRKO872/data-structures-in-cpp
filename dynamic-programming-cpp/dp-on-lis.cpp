// Longest Increasing Subsequences : 
int recSol (vector<int>& nums, int index, int prev, vector<vector<int>>& dp) {
    if (index == nums.size()) return 0;

    if (dp[index][prev] != -1) return dp[index][prev];

    if (nums[index] > nums[prev]) return dp[index][prev] = max (1+recSol (nums, index+1, index, dp), recSol (nums, index+1, prev, dp));
    return dp[index][prev] = recSol (nums, index+1, prev, dp);
}
int bottomUp (vector<int>& nums) {
    vector<vector<int>> dp (nums.size()+1, vector<int> (nums.size()+1, 0));

    for (int curr = nums.size()-1; curr >= 0; curr--) {
        for (int prev = curr-1; prev >= -1; prev--) {
            
            if (prev == -1 || nums[curr] > nums[prev]) dp[curr][prev+1] = max (1 + dp[curr+1][curr+1], dp[curr+1][prev+1]);
            else dp[curr][prev+1] = dp[curr+1][prev+1];

        }
    }

    return dp[0][0];
}
int optimalSolUsingBS (vector<int>& nums) {
    vector<int> ans;
    ans.push_back(nums[0]);

    for (int i = 1; i < nums.size(); i++) {
        if (ans.back() < nums[i]) {
            ans.push_back(nums[i]);
        } else {

            int st = 0, end = ans.size()-1;
            while (st < end) {
                int mid = st + ((end-st)/2);

                if (ans[mid] < nums[i]) {
                    st = mid+1;
                } else {
                    end = mid;
                }
            }

            ans[st] = nums[i];
        }
    }
    return ans.size();
}
int lengthOfLIS(vector<int>& nums) {
    // vector<vector<int>> dp (nums.size()+1, vector<int> (nums.size()+1, -1));
    // return bottomUp (nums);
    return optimalSolUsingBS (nums);
}

// Russian Dolls Envelope :
int compare (vector<vector<int>>& envelopes, int index, int prev) {
    return (envelopes[index][0] > envelopes[prev][0] && envelopes[index][1] > envelopes[prev][1]);
}

int lisRec (vector<vector<int>>& envelopes, int index, int prev) {
    if (index == envelopes.size()) return 0;

    if (compare (envelopes, index, prev)) return max(1 + lisRec (envelopes, index+1, index), lisRec (envelopes, index+1, prev));
    return lisRec (envelopes, index+1, prev);
}

int bottomUp (vector<vector<int>>& envelopes, vector<vector<int>>& dp) {
    for (int i = envelopes.size()-1; i >= 1; i--) {
        for (int j = envelopes.size()-1; j >= 0; j--) {

            if (compare (envelopes, i, j)) dp[i][j] = max(1 + dp[i+1][i], dp[i+1][j]);
            else dp[i][j] = dp[i+1][j];

        }
    }

    return dp[1][0];
}

int maxEnvelopes(vector<vector<int>>& envelopes) {
    sort (envelopes.begin(), envelopes.end(), [](vector<int>& arr1, vector<int>& arr2) {
        if (arr1[0] == arr2[0]) return (arr1[1] > arr2[1]);
        return arr1[0] < arr2[0];
    });

    envelopes.insert (envelopes.begin(), {-1, -1});

    vector<vector<int>> dp (envelopes.size()+1, vector<int> (envelopes.size()+1, 0));
    // return lisRec (envelopes, 1, 0);
    return bottomUp (envelopes, dp);
}

// Longest Subsequence With Diff 1 : 
int longestSubsequence(int N, int A[])
{
    // code here
    vector<vector<int>> dp (N+1, vector<int> (N+1, 0));
    
    for (int i = N-1; i >= 0; i--) {
        for (int j = i-1; j >= -1; j--) {
            // Having condition as difference between prev an curr values being just 1
            if (j == -1 || abs(A[i] - A[j]) == 1) dp[i][j+1] = max (1 + dp[i+1][i+1], dp[i+1][j+1]);
            else dp[i][j+1] = dp[i+1][j+1];
            
        }
    }
    return dp[0][0];
}

// Maximum Height by stacking cuboids
bool compare (vector<vector<int>>& cuboids, int i, int j) {
    return ( cuboids[i][0] >= cuboids[j][0] && cuboids[i][1] >= cuboids[j][1] && cuboids[i][2] >= cuboids[j][2] );
}

int bottomUp (vector<vector<int>>& nums) {
    vector<vector<int>> dp (nums.size()+1, vector<int> (nums.size()+1, 0));

    for (int i = nums.size()-1; i >= 1; i--) {
        for (int j = nums.size()-1; j >= 0; j--) {

            if (compare (nums, i, j)) dp[i][j] = max (nums[i][2]+dp[i+1][i], dp[i+1][j]);
            else dp[i][j] = dp[i+1][j];
            
        }
    }

    return dp[1][0];
}

int lisRec (vector<vector<int>>& envelopes, int index, int prev) {
    if (index == envelopes.size()) return 0;

    if (compare (envelopes, index, prev)) return max(envelopes[index][2] + lisRec (envelopes, index+1, index), lisRec (envelopes, index+1, prev));
    return lisRec (envelopes, index+1, prev);
}

int maxHeight(vector<vector<int>>& cuboids) {
    for (auto& arr: cuboids) {
        sort (arr.begin(), arr.end());
    }

    sort (cuboids.begin(), cuboids.end());

    cuboids.insert (cuboids.begin(), {0, 0, 0});

    // return bottomUp (cuboids);
    return bottomUp (cuboids);
}

// Make Array Strictly Increasing (Leetcode) : 
int justBigger (vector<int>& arr, int num) {
    int st = 0, end = arr.size()-1;
    int ans = -1;
    while (st <= end) {
        int mid = st + ((end-st)/2);
        if (arr[mid] > num) {
            ans = arr[mid];
            end = mid-1;
        } else {
            st = mid+1;
        }
    }
    return ans;
}
int recSol (vector<int>& arr1, vector<int>& arr2, int ind, int prev, map<pair<int, int>, int>& mp) {
    if (ind == arr1.size()) return 0;
    if (mp.find({ind, prev}) != mp.end()) return mp[{ind, prev}];

    int x = INT_MAX, y = INT_MAX, z = INT_MAX;
    if (prev < arr1[ind]) {
        x = recSol (arr1, arr2, ind+1, arr1[ind], mp);

        int bigger = justBigger (arr2, prev);
        if (bigger > prev) {
            y = recSol (arr1, arr2, ind+1, bigger, mp);
        }
        if (y != INT_MAX) {
            y++;
        }
    } else {
        int bigger = justBigger (arr2, prev);
        if (bigger > prev) {
            z = recSol (arr1, arr2, ind+1, bigger, mp);
        }
        if (z != INT_MAX) {
            z++;
        }
    }

    return mp[{ind, prev}] = min ({x, y, z});
}
int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
    sort (arr2.begin(), arr2.end());
    map<pair<int, int>, int> mp;
    int ans = recSol (arr1, arr2, 0, -1, mp);
    return ans == INT_MAX ? -1 : ans;
}