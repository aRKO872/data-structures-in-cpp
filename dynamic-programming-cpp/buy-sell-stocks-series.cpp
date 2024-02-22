// Buy and Sell Stocks 1 :
int maxProfit(vector<int>& prices) {
    int maxDiff = 0;
    int lowestNum = prices[0];
    for (int i = 1; i < prices.size(); i++) {
        lowestNum = min (lowestNum, prices[i-1]);
        if (lowestNum >= prices[i]) continue;
        maxDiff = max (maxDiff, prices[i] - lowestNum);
    }
    return maxDiff;
}

// Buy and Sell Stocks 2 : 
int recSol (vector<int>& prices, int index, int buy, vector<vector<int>>& dp) {
    if (index == prices.size()) return 0;
    if (dp[index][buy] != -1) return dp[index][buy];

    if (buy == 0) {
        return dp[index][buy] = max (-prices[index] + recSol (prices, index+1, 1, dp), recSol (prices, index+1, 0, dp));
    }
    return dp[index][buy] = max (prices[index] + recSol (prices, index+1, 0, dp), recSol (prices, index+1, 1, dp));
}
int bottomUp (vector<int>& prices) {
    vector<vector<int>> dp (prices.size()+1, vector<int> (2, 0));

    for (int i = prices.size()-1; i >= 0; i--) {
        for (int j = 1; j >= 0; j--) {
            if (j == 0) dp[i][j] = max (-prices[i] + dp[i+1][1], dp[i+1][0]);
            else dp[i][j] = max (prices[i] + dp[i+1][0], dp[i+1][1]);
        }
    }

    return dp[0][0];
}
int maxProfit(vector<int>& prices) {
    // vector<vector<int>> dp (prices.size()+1, vector<int> (2, -1));
    // return recSol (prices, 0, 0, dp);
    return bottomUp (prices);
}

// Buy and Sell Stocks 3 : 
int recSol (vector<int>& prices, int index, int buy, int buyCount, vector<vector<vector<int>>>& dp) {
    if (index == prices.size() || buyCount > 2) return 0;

    if (dp[index][buy][buyCount] != -1) return dp[index][buy][buyCount];

    if (buy == 0) {
        return dp[index][buy][buyCount] = max (-prices[index] + recSol (prices, index+1, 1, buyCount+1, dp), recSol (prices, index+1, buy, buyCount, dp));
    }
    return dp[index][buy][buyCount] = max (prices[index] + recSol (prices, index+1, 0, buyCount, dp), recSol (prices, index+1, buy, buyCount, dp));
}

int bottomUp (vector<int>& prices) {
    vector<vector<vector<int>>> dp (prices.size()+1, vector<vector<int>> (2, vector<int> (4, 0)));

    for (int i = prices.size()-1; i >= 0; i--) {
        for (int j = 1; j >= 0; j--) {
            for (int k = 2; k >= 0; k--) {
                  if (j == 0) {
                    dp[i][j][k] = max (-prices[i] + dp[i+1][1][k+1], dp[i+1][j][k]);
                } else dp[i][j][k] = max (prices[i] + dp[i+1][0][k], dp[i+1][j][k]);
            }
        }
    }

    return dp[0][0][0];
}

int maxProfit(vector<int>& prices) {
    // vector<vector<vector<int>>> dp (prices.size()+1, vector<vector<int>> (2, vector<int> (3, -1)));
    // return recSol (prices, 0, 0, 0, dp);
    return bottomUp (prices);
}

// Buy and Sell Stocks 4 : 
int bottomUp (vector<int>& prices, int total) {
    vector<vector<vector<int>>> dp (prices.size()+1, vector<vector<int>> (2, vector<int> (total+2, 0)));

    for (int i = prices.size()-1; i >= 0; i--) {
        for (int j = 1; j >= 0; j--) {
            for (int k = total; k >= 0; k--) {
                  if (j == 0) {
                    dp[i][j][k] = max (-prices[i] + dp[i+1][1][k+1], dp[i+1][j][k]);
                } else dp[i][j][k] = max (prices[i] + dp[i+1][0][k], dp[i+1][j][k]);
            }
        }
    }

    return dp[0][0][0];
}
int maxProfit(int k, vector<int>& prices) {
    return bottomUp (prices, k);
}