//printing all subsequences
void printAllSubsequences (string& s, int ind, string store) {
  if (ind == s.size()) {
    cout << store << endl;
    return;
  }
  printAllSubsequences(s, ind+1, store);
  printAllSubsequences(s, ind+1, store + s[ind]);
}

//coin change problem 
int coinChange(vector<int>& coins, int amount) {
        if (amount == 0) return 0;
        if (amount < 0) return INT_MAX;
        int minI = INT_MAX;
        for (int i = 0; i < coins.size(); i++) {
            int ans = coinChange(coins, amount-coins[i]);
            if (ans != INT_MAX) {
                minI = min(minI, ans+1);    // it is ans+1, to add up the previous element required to make target the way it was.
            }
        }
        return (minI == INT_MAX || minI == 0) ? -1 : minI;
    }
}

//cut in x, y, z segments problem:
int recSol(int n, int x, int y, int z) {
	if (n == 0) {
          return 0;
	}
	if (n < 0) {
		return INT_MIN;
	}
	int a = recSol(n-x, x, y, z)+1;
	int b = recSol(n-y, x, y, z)+1;
	int c = recSol(n-z, x, y, z)+1;

	int ans = max(a, max(b, c));
	return ans; 
}

int cutSegments(int n, int x, int y, int z) {
	// Write your code here.
    int ans = recSol(n, x, y, z);
    return (ans < 0) ? 0 : ans;
}

//House robber problem: find subsequence with largest sum that has no adjectent numbers:
int recSol (vector<int>& nums, int ind, int sum, int tempSum) {
    if (ind >= nums.size()) {
        sum = max(sum, tempSum);
        return sum; 
    }
    int robHouse = recSol (nums, ind+2, sum, tempSum+nums[ind]);
    int notRobHouse = recSol (nums, ind+1, sum, tempSum);
    return max(robHouse, notRobHouse);
} 
int rob(vector<int>& nums) {
    int sol = recSol (nums, 0, 0, 0);
    return sol;
}

//last occurence of a character in a string
int lastOccurence (string& str, char target, int ind, int store) {
  if (ind < 0) {
    return store;
  }
  if (str[ind] == target) return ind;
  return lastOccurence(str, target, ind+1, store);
}

// Add Strings recursively
string add (string& num1, string& num2, int i, int j, int carry, string ans) {
    if (i >= num1.size() && j >= num2.size()) {
        while (carry > 0) {
            ans += ((carry%10) + '0');
            carry /= 10;
        } 
        return ans;
    }
    int sum;
    if (i >= num1.size()) {
        int sum = (num2[j] - '0') + carry;
        return (to_string(sum%10) + add (num1, num2, i, j+1, (sum/10), ans));
    } else if (j >= num2.size()) {
        int sum = (num1[i] - '0') + carry;
        return (to_string(sum%10) + add (num1, num2, i+1, j, (sum/10), ans));
    } else {
        int sum = (num1[i] - '0') + (num2[j]-'0') + carry;
        return (to_string(sum%10) + add (num1, num2, i+1, j+1, (sum/10), ans));
    }
}
string addStrings(string num1, string num2) {
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    string ans = add (num1, num2, 0, 0, 0, "");
    reverse(ans.begin(), ans.end());
    return ans;
}

// Print contiguous subarrays recursively
void recSol(vector<int> arr, int st, int end) {
  if (end >= arr.size()) return;
  for (int i = st; i <= end; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
  recSol(arr, st, end+1);
}

void rec(vector<int> arr) {
  for (int i = 0; i < arr.size(); i++) {
    recSol(arr, i, i);
  }
  return;
}

// Best time to buy and sell stock recursively
int recSol (vector<int>& prices, int ind, int minNum, int maxProfit) {
    if (ind == prices.size()) return maxProfit;
    int minI = min(minNum, prices[ind]);
    return recSol(prices, ind+1, minI, max(maxProfit, prices[ind]-minI)); 
}
int maxProfit(vector<int>& prices) {
    return recSol (prices, 0, INT_MAX, 0);
}

// Turn integer into number string : For eg - 4276 - Four Thousand Two Hundred Seventy Six
string recSol (vector<pair<string, int>>& arr, int num) {
    if (num == 0) {
        return "Zero";
    }
    for (auto i : arr) {
        if (num >= i.second) {
            string a = "";
            if (num >= 100) {
                a = recSol (arr, num/i.second) + " ";
            }
            string b = i.first;
            string c = "";
            if (num%i.second > 0) {
                c = " " + recSol (arr, num%i.second);
            }
            return a+b+c;
        }
    }
    return "";
}
string numberToWords(int num) {
    vector<pair<string, int>> arr { {"Billion", 1000000000}, {"Million", 1000000}, {"Thousand", 1000}, {"Hundred", 100}, {"Ninety", 90}, {"Eighty", 80}, {"Seventy", 70}, {"Sixty", 60}, {"Fifty", 50}, {"Forty", 40}, {"Thirty", 30}, {"Twenty", 20}, {"Nineteen", 19}, {"Eighteen", 18}, {"Seventeen", 17}, {"Sixteen", 16}, {"Fifteen", 15}, {"Fourteen", 14}, {"Thirteen", 13}, {"Twelve", 12}, {"Eleven", 11}, {"Ten", 10}, {"Nine", 9}, {"Eight", 8}, {"Seven", 7}, {"Six", 6}, {"Five", 5}, {"Four", 4}, {"Three", 3}, {"Two", 2}, {"One", 1}};
    return recSol (arr, num);
}

// Wildcard Pattern Matching
bool recSol (string& s, string& p, int indS, int indP) {
    // base case 1
    if (indS == s.size() && indP == p.size()) return true;
    // base case 2
    if (indS == s.size() && indP < p.size()) {
        while (indP < p.size()) {
            if (p[indP] != '*') return false;
            indP++;
        }
        return true;
    }

    if (s[indS] == p[indP] || p[indP] == '?') return recSol (s, p, indS+1, indP+1);
    if (p[indP] == '*') {
        bool take = recSol (s, p, indS+1, indP);
        bool notTake = recSol (s, p, indS, indP+1);
        return (take || notTake);
    }
    return false; // for case in which s[indS] != p[indP]
}
bool isMatch(string s, string p) {
    int indS = 0, indP = 0;
    return recSol (s, p, indS, indP);
}

//minimum number of squares required to form a given number
int numberOfSquares (int n, int sq) {
    if (n == 0) return 0;
    if (n < 0) return INT_MAX;
    int minI = INT_MAX;
    for (int i = sq; i*i <= n; i++) {
        int ans = numberOfSquares (n-(i*i), i);
        if (ans != INT_MAX) {
            minI = min(minI, ans+1);
        }
    }
    return minI;
}
int numSquares(int n) {
    return numberOfSquares (n, 1);
}

//Minimum Cost for Tickets : Find the minimum cost required for tickets priced for: 
//1 day at costs[0]
//2 days at costs[1]
//30 days at costs[2]
// for days in the days array for which a guy has booked holidays for:
int binarySearch (vector<int>& days, int target, int st) {
    if (target > days[days.size()-1]) return days.size();
    int end = days.size()-1, res = 0;
    while (st <= end) {
        int mid = st + (end-st)/2;
        if (target <= days[mid]) {
            res = mid;
            end = mid-1;
        } else {
            st = mid+1;
        }
    }
    return res;
}
int recSol (vector<int>& days, vector<int>& costs, int ind) {
    if (ind == days.size()) {
        return 0;
    }
    int a = costs[0] + recSol (days, costs, binarySearch(days, days[ind]+1, ind));
    int b = costs[1] + recSol (days, costs, binarySearch(days, days[ind]+7, ind));
    int c = costs[2] + recSol (days, costs, binarySearch(days, days[ind]+30, ind));
    return min(a, min(b, c));
}
int mincostTickets(vector<int>& days, vector<int>& costs) {\
    return recSol (days, costs, 0);
}

// Number of Dice Rolls n with k faces to form target :
int numRollsToTarget(int n, int k, int target) {
    if (target < 0) return 0;
    if (n == 0 && target == 0) return 1;
    if (n == 0 && target != 0) return 0;
    if (n != 0 && target == 0) return 0;
    int count = 0;
    for (int i = 1; i <= k; i++) {
        count += numRollsToTarget (n-1, k, target-i);
    }
    return count;
}