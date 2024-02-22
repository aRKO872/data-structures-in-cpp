// Guess Number Higher or Lower II (Leetcode)
int getMoneyRec (int st, int end, vector<vector<int>>& dp) {
    if (st >= end) return 0;
    if (dp[st][end] != -1) return dp[st][end];

    int ans = INT_MAX;
    for (int i = st; i <= end; i++) {
        ans = min(ans, i + max (getMoneyRec (st, i-1, dp), getMoneyRec (i+1, end, dp)));
    }

    return dp[st][end] = ans;
}
int bottomUp (vector<vector<int>>& dp, int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= n; j++) {
            if (i >= j) continue;
            int ans = INT_MAX;
            for (int k = i; k <= j; k++) {
                ans = min (ans, k + max (dp[i][k-1], dp[k+1][j]));
            }

            dp[i][j] = ans;

        }
    }
    return dp[1][n];
}
int getMoneyAmount(int n) {
    vector<vector<int>> dp (n+2, vector<int> (n+2, -1));
    // return bottomUp (dp, n);
    return getMoneyRec (0, n, dp);
}

// Minimum Cost Tree From Leaf Values
int recSol (vector<int>& arr, map<pair<int, int>, int>& map, int st, int end, vector<vector<int>>& dp) {
    if (st >= end) return 0;

    if (dp[st][end] != -1) return dp[st][end]; 
    int ans = INT_MAX;
    for (int i = st; i < end; i++) {
        ans = min (ans, (map[{st, i}]*map[{i+1, end}] + recSol (arr, map, st, i, dp) + recSol (arr, map, i+1, end, dp)));
    }

    return dp[st][end] = ans;
}

int bottomUp (vector<int>& arr, map<pair<int, int>, int>& map) {
    vector<vector<int>> dp (arr.size()+1, vector<int> (arr.size()+1, 0));

    for (int i = arr.size()-1; i >= 0; i--) {
        for (int j = 0; j < arr.size(); j++) {
            if (i >= j) continue;

            int ans = INT_MAX;

            for (int k = i; k < j; k++) {
                ans = min (ans, (map[{i, k}]*map[{k+1, j}] + dp[i][k] + dp[k+1][j]));
            }

            dp[i][j] = ans;
        }
    }

    return dp[0][arr.size()-1];
}

int mctFromLeafValues(vector<int>& arr) {
    map<pair<int, int>, int> maxI;
    for (int i = 0; i < arr.size(); i++) {
        maxI[{i, i}] = arr[i];
        for (int j = i+1; j < arr.size(); j++) {
            maxI[{i, j}] = max (arr[j], maxI[{i, j-1}]);
        }
    }

    // return recSol (arr, mp, 0, arr.size()-1);
    vector<vector<int>> dp (arr.size()+1, vector<int> (arr.size()+1, -1));
    return bottomUp (arr, maxI);
}

// Burst Balloons (VV IMP) 
int recSol (vector<int>& nums, int st, int end, vector<vector<int>>& dp) {
    if (st > end) return 0;
    if (dp[st][end] != -1) return dp[st][end];

    int ans = 0;
    for (int i = st; i <= end; i++) {
        int add = nums[i] * nums[st-1] * nums[end+1];
        ans = max (ans, add+recSol(nums, st, i-1, dp)+recSol(nums, i+1, end, dp));
    }

    return dp[st][end] = ans;
}

int bottomUp (vector<int>& nums) {
    vector<vector<int>> dp (nums.size()+1, vector<int> (nums.size()+1, 0));

    for (int i = nums.size()-2; i >= 1; i--) {
        for (int j = 1; j <= nums.size()-2; j++) {
            if (i > j) continue;

            int ans = 0;
            for (int k = i; k <= j; k++) {
                int add = nums[k] * nums[i-1] * nums[j+1];
                ans = max (ans, add+dp[i][k-1]+dp[k+1][j]);
            }

            dp[i][j] = ans;
        }
    }

    return dp[1][nums.size()-2];
}

int maxCoins(vector<int>& nums) {
    nums.push_back(1);
    nums.insert (nums.begin(), 1);
    // vector<vector<int>> dp (nums.size()+1, vector<int> (nums.size()+1, -1));
    // return recSol (nums, 1, nums.size()-2, dp);
    return bottomUp (nums);
}

// Stone Game 1 : 
bool recSol (vector<int>& piles, int st, int end) {
    if (st >= end) return 0;
    return max (piles[st] - recSol (piles, st+1, end), piles[end] - recSol (piles, st, end-1));
}

int bottomUp (vector<int>& piles, vector<vector<int>>& dp) {
    for (int i = piles.size()-1; i >= 0; i--) {
        for (int j = 0; j < piles.size(); j++) {
            if (i >= j) continue;
            dp[i][j] = max (piles[i] - dp[i+1][j], piles[j] - dp[i][j-1]);
        }
    }

    return dp[0][piles.size()-1];
}

bool stoneGame(vector<int>& piles) {
    vector<vector<int>> dp (piles.size()+1, vector<int> (piles.size()+1, 0));
    // return recSol (piles, 0, piles.size()-1);
    return bottomUp (piles, dp);
}

// stone game 2:
int recSol (vector<int>& piles, int index, int M, bool alice) {
    if (index >= piles.size()) return 0;

    int sum = 0, maxStones = alice ? INT_MIN : INT_MAX;
    
    for (int i = 1; i <= 2*M; i++) {
        if (index + i -1 >= piles.size()) break;
        sum += piles[index+i-1];
        if (alice) {
            maxStones = max (maxStones, sum + recSol (piles, index+i, max (M, i), !alice));
        } else {
            maxStones = min (maxStones, recSol (piles, index+i, max (M, i), !alice));
        }
    }

    return maxStones;
}

int bottomUp (vector<int>& piles) {
    if (piles.size() == 1 && piles[0] == 1) return 1;
    
    vector<vector<vector<int>>> dp (piles.size()+1, vector<vector<int>> (piles.size()+1, vector<int> (2, 0)));

    for (int i = piles.size()-1; i >= 0; i--) {
        for (int j = piles.size()-1; j >= 1; j--) {
            for (int k = 1; k >= 0; k--) {

                if (i >= piles.size()) continue;

                int sum = 0, maxStones = k == 1 ? INT_MIN : INT_MAX;
                
                for (int l = 1; l <= 2*j; l++) {
                    if (i + l - 1 >= piles.size()) break;
                    sum += piles[i+l-1];

                    if (k == 1) {
                        maxStones = max (maxStones, sum + dp[i+l][max (j, l)][0]);
                    } else {
                        maxStones = min (maxStones, dp[i+l][max (j, l)][1]);
                    }
                }

                dp[i][j][k] = maxStones;

            }
        }
    }

    return dp[0][1][1];
}

int stoneGameII(vector<int>& piles) {
    // return recSol (piles, 0, 1, 1);
    return bottomUp (piles);
}

// Stone Game 3 : 
int recSol (vector<int>& stones, int index) {
    if (index >= stones.size()) return 0;

    int takeOne = stones[index] - recSol (stones, index+1);

    int takeTwo = INT_MIN;
    if (index + 1 < stones.size()) takeTwo = stones[index] + stones[index+1] - recSol (stones, index+2);

    int takeThree = INT_MIN;
    if (index+2 < stones.size()) takeThree = stones[index] + stones[index+1] + stones[index+2] - recSol (stones, index+3);

    return max (takeOne, max (takeTwo, takeThree));
}

int bottomUp (vector<int>& stones, vector<int>& dp) {
    for (int i = stones.size()-1; i >= 0; i--) {
        int takeOne = stones[i] - dp[i+1];

        int takeTwo = INT_MIN;
        if (i + 1 < stones.size()) takeTwo = stones[i] + stones[i+1] - dp[i+2];

        int takeThree = INT_MIN;
        if (i+2 < stones.size()) takeThree = stones[i] + stones[i+1] + stones[i+2] - dp[i+3];

        dp[i] = max (takeOne, max (takeTwo, takeThree));
    }

    return dp[0];
}

string stoneGameIII(vector<int>& stoneValue) {
    vector<int> dp (stoneValue.size()+3, 0);
    int value = bottomUp (stoneValue, dp);

    if (value == 0) {
        return "Tie";
    } else if (value < 0) {
        return "Bob";
    } else {
        return "Alice";
    }
}

// Stone Game 4
bool recSol (int n, vector<int>& dp) {
    if (n <= 0) return 0;
    if (dp[n] != -1) return dp[n];

    for (int i = 1; i*i <= n; i++) {
        if (recSol (n-i*i, dp) == 0) return dp[n] = 1;
    }

    return dp[n] = 0;
}

bool bottomUp (int n) {
    vector<int> dp (n+1, 0);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j*j <= i; j++) {
            if (dp[i-j*j] == 0) {
                dp[i] = 1;
                break;
            }
        }
    }

    return dp[n];
}

bool winnerSquareGame(int n) {
    // vector<int> dp (n+1, -1);
    // return recSol (n, dp);

    return bottomUp (n);
}

// Stone Game 5
int recSol (vector<int>& piles, vector<int>& prefix, int st, int end) {
    if (st > end) return 0;

    int ans = INT_MIN;
    for (int i = st; i <= end; i++) {
        int sum1 = 0, sum2 = 0;

        if (st-1 >= 0) sum1 = prefix[i] - prefix[st-1];
        else sum1 = prefix[i];
        sum2 = prefix[end] - prefix[i];
        // for (int j = st; j <= i; j++) sum1 += piles[j];
        // for (int j = i+1; j <= end; j++) sum2 += piles[j];

        if (sum1 < sum2) {
            ans = max (ans, sum1 + recSol (piles, prefix, st, i));
        } else if (sum1 > sum2) {
            ans = max (ans, sum2 + recSol (piles, prefix, i+1, end));
        } else {
            ans = max ({ans, sum1 + recSol (piles, prefix, st, i), sum2 + recSol (piles, prefix, i+1, end)});
        }
    }

    return ans;
}

int bottomUp (vector<int>& piles, vector<int>& prefix) {
    vector<vector<int>> dp (piles.size()+1, vector<int> (piles.size()+1, 0));

    for (int s = piles.size()-1; s >= 0; s--) {
        for (int e = 0; e < piles.size(); e++) {

            if (s > e) continue;

            int ans = INT_MIN;
            for (int i = s; i <= e; i++) {
                int sum1 = 0, sum2 = 0;

                if (s-1 >= 0) sum1 = prefix[i] - prefix[s-1];
                else sum1 = prefix[i];
                sum2 = prefix[e] - prefix[i];

                if (sum1 < sum2) {
                    ans = max (ans, sum1 + dp[s][i]);
                } else if (sum1 > sum2) {
                    ans = max (ans, sum2 + dp[i+1][e]);
                } else {
                    ans = max ({ans, sum1 + dp[s][i], sum2 + dp[i+1][e]});
                }
            }

            dp[s][e] = ans;

        }
    }

    return dp[0][piles.size()-1];
} 

int stoneGameV(vector<int>& stoneValue) {
    vector<int> prefix (stoneValue.size(), 0);
    int sum = 0;
    for (int i = 0; i < stoneValue.size(); i++) {
        sum += stoneValue[i];
        prefix[i] = sum;
    }
    // return recSol (stoneValue, prefix, 0, stoneValue.size()-1);
    return bottomUp (stoneValue, prefix);
}