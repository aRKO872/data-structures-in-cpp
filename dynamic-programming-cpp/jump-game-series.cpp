// Jump Game 1 :
bool recSol (vector<int>& nums, int index) {
    if (index >= nums.size()-1) return true;

    int steps = nums[index];
    for (int i = 1; i <= steps; i++) {
        if (recSol (nums, index+i)) return true;
    }

    return false;
}

bool canJump(vector<int>& nums) {
    // return recSol (nums, 0);
    vector<bool> dp (nums.size()+1, false);
    dp[nums.size()-1] = true;
    dp[nums.size()] = true;

    for (int i = nums.size()-2; i >= 0; i--) {
        if (nums[i] == 0) continue;
        int steps = nums[i];
        for (int j = 1; j <= steps; j++) {
            if (i + j < dp.size() && dp[i+j]) {
                dp[i] = true;
                break;
            }
        }
    }

    return dp[0];
}

// Jump Game 2 :
int recSol (vector<int>& nums, int index) {
    if (index >= nums.size()-1) return 0;

    int steps = nums[index];
    int ans = INT_MAX;
    for (int i = 1; i <= steps; i++) {
        int addition = recSol (nums, index+i);
        if (addition == INT_MAX) continue;
        ans = min (ans, 1+addition);
    }

    return ans;
}

int jump(vector<int>& nums) {
    // return recSol (nums, 0);
    vector<int> dp (nums.size(), INT_MAX);
    dp[nums.size()-1] = 0;

    for (int i = nums.size()-2; i >= 0; i--) {

        int steps = nums[i];
        int ans = INT_MAX;
        for (int j = 1; j <= steps; j++) {
            if (i+j < nums.size()) {
                int addition = dp[i+j];
                if (addition == INT_MAX) continue;
                ans = min (ans, 1+addition);
            }
        }

        dp[i] = ans;
    }

    return dp[0];
}

// Jump Game 3 :
bool canReach(vector<int>& arr, int start) {
    if (start >= arr.size() || start < 0) return false;
    if (arr[start] == -1) return false;
    if (arr[start] == 0) return true;
    int step = arr[start];
    arr[start] = -1;
    return canReach (arr, start-step) || canReach (arr, start+step);
}