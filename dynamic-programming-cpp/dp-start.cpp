// Fibonacci Top-Down Approach : 
int generate (vector<int>& dp, int n) {
    if (dp[n] != INT_MIN) return dp[n];
    dp[n] = generate (dp, n-1) + generate (dp, n-2);
    return dp[n];
}
int fib(int n) {
    if (n == 1 || n == 0) return n;
    vector<int> dp (n+1, INT_MIN);
    dp[0] = 0; dp[1] = 1;
    return generate (dp, n);
}

// Fibonacci Bottom Up Approach : 
int fib(int n) {
    if (n == 1 || n == 0) return n;
    vector<int> dp (n+1, -1);
    dp[0] = 0; dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}

// Coin Change Problem (Top Down Approach) : 
int recSol (vector<int>& coins, int amount, vector<int>& dp) {
    if (amount == 0) return 0;
    if (amount < 0) return INT_MAX;
    if (dp[amount] != -1) return dp[amount];
    int minCount = INT_MAX;
    for (int i = coins.size()-1; i >= 0; i--) {
        if (amount >= coins[i]) {
            int res = recSol (coins, amount - coins[i], dp);
            if (res != INT_MAX) {
                minCount = min (minCount, 1 + res);
            }
        }
    }
    dp[amount] = minCount;
    return dp[amount];
}
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp (amount+1, -1);
    int minCount = recSol (coins, amount, dp);
    return minCount == INT_MAX ? -1 : minCount;
}

// Coin Change Problem (Bottom Up Approach) : 
int bottomUp (vector<int>& coins, int amount) {
    vector<int> dp (amount+1, INT_MAX);
    dp[0] = 0;
    for (int target = 1; target <= amount; target++) {
        for (int j = 0; j < coins.size(); j++) {
            if (target-coins[j] < 0) continue;
            int coinsToReachAmount = dp[target-coins[j]];
            if (coinsToReachAmount >= 0 && coinsToReachAmount != INT_MAX) {
                dp[target] = min (dp[target], 1 + coinsToReachAmount);
            }
        }
    }
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}
int coinChange(vector<int>& coins, int amount) {
    return bottomUp (coins, amount);
}

// House Robber Problem (Top Down Approach) : 
int robRec (vector<int>& nums, int index, vector<int>& dp) {
    if (index >= nums.size()) return 0;
    if (dp[index] != -1) return dp[index];
    int take = nums[index] + robRec (nums, index + 2, dp);
    int notTake = robRec (nums, index + 1, dp);
    dp[index] = max (take, notTake);
    return dp[index];
}
int rob(vector<int>& nums) {
    vector<int> dp (nums.size()+1, -1);
    return robRec (nums, 0, dp);
}

// House Robber Problem (Bottom Up Approach) : 
int robRecBottomUp (vector<int>& nums) {
    vector<int> dp (nums.size()+1, 0);
    dp[0] = nums[0];
    for (int index = 1; index < nums.size(); index++) {
        int take = 0, notTake = 0;
        take = nums[index];
        if (index-2 >= 0) take += dp[index-2];
        if (index-1 >= 0) notTake = dp[index - 1];
        dp[index] = max (take, notTake);
    }
    return dp[nums.size()-1];
}
int rob(vector<int>& nums) {
    return robRecBottomUp (nums);
}

// House Robber 2 (Houses are in a circular fashion, first and last houses are neighbours) :
int robRec (vector<int>& nums, int index, int size, vector<int>& dp) {
    if (index >= size) return 0;
    if (dp[index] != -1) return dp[index];
    int notTake = robRec (nums, index+1, size, dp);
    int take = nums[index] + robRec (nums, index+2, size, dp);
    dp[index] = max (take, notTake);
    return dp[index];
}
int rob(vector<int>& nums) {
    if (nums.size() == 1) return nums[0];
    vector<int> dp1 (nums.size(), -1);
    vector<int> dp2 (nums.size(), -1);
    int first = robRec (nums, 0, nums.size()-1, dp1);
    int second = robRec (nums, 1, nums.size(), dp2);
    return max (first, second);
}


// Paint Fence DP Problem VVVVVVV IMP! (Top Down Approach) : 
long long countRec (int n, int k, vector<long long>& dp) {
    if (n == 1) return k;
    if (n == 2) return k + k*(k-1);
    if (dp[n] != 0) return dp[n];
    dp[n] = (countRec(n-2, k, dp) + countRec(n-1, k, dp)) * (k-1);
    return dp[n];
}
long long countWays(int n, int k){
    vector<long long> dp (n+1, 0);
    return countRec (n, k, dp);
}


// Count Derangements Problem (VVVV Important!): 
long long mod = (1e9 + 7);
long long int recSol (int n, vector<long long int>& dp) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (dp[n] != -1) return dp[n]%mod;
    return dp[n] = ((n-1) * (recSol (n-2, dp)%mod + recSol (n-1, dp)%mod)%mod)%mod; 
}
long long int countDerangements(int n) {
    // Write your code here.
    vector<long long int> dp (n+1, -1);
    return recSol (n, dp);
}

// Counting Bits (VVVV IMP!) :
vector<int> countBits(int num) {
    vector<int> result (num+1);
    int offset = 1;
    for (int index = 1; index < num + 1; ++index){
        if (offset * 2 == index){
            offset *= 2;
        }
        result[index] = result[index - offset] + 1;
    }
    return result;
}

// Decode Ways (VV IMP!) : 
int numDecodings(string s) {
    vector<int> dp (s.size()+1, 0);
    return numDecodings (s, dp);
}

int numDecodings (string s, vector<int>& dp) {
    dp[s.size()] = 1;
    
    for (int ind = s.size()-1; ind >= 0; ind--) {
        if (s[ind] == '0') dp[ind] = 0;
        else {
            int ans = 0;
            ans += dp [ind+1];
            if (ind + 1 < s.size() && (s[ind] == '1' || (s[ind] == '2' && s[ind+1] <= '6'))) 
                ans += dp[ind+2];

            dp[ind] = ans;
        }
    }
    
    return dp[0];
}

// Delete And Earn : 
int deleteAndEarn(vector<int>& nums) {
    unordered_map<int, int> mp;
    for (auto i: nums) mp[i]++;
    vector<int> arr;
    for (auto i: mp) {
        arr.push_back(i.first);
    }
    sort (arr.begin(), arr.end());
    vector<int> dp (nums.size()+1, 0);
    // return recSol (arr, mp, dp, 0);
    
    for (int ind = arr.size()-1; ind >= 0; ind--) {
        int notTake = dp[ind+1];
        int take = arr[ind]*mp[arr[ind]];

        if (ind+1 < arr.size()) {
            if (arr[ind]+1 == arr[ind+1]) take += dp[ind+2];
            else take += dp[ind+1];
        }

        dp[ind] = max (notTake, take);
    }
    
    return dp[0];
}