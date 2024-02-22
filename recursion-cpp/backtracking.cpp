// Find Permutations of a string :
void swap (string& s, int i, int j) {
    int temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}
void find (string s, int ind, set<string>& ans) {
    if (ind == s.size()) {
        ans.insert(s);
        return;
    }
    for (int j = ind; j < s.size(); j++) {
        swap (s, ind, j);
        find (s, ind+1, ans);
        swap (s, ind, j);
    }
}
vector<string>find_permutation(string S)
{
  // Code here there
  set<string> set;
  find (S, 0, set);
  vector<string> ans (set.begin(), set.end());
  sort(ans.begin(), ans.end());
  return ans;
}

// Rat In a Maze. Find all the ways in which a rat can reach m[n-1][n-1] position from m[0][0] position:
void findWays (vector<vector<int>> &m, int i, int j, int n, string direction, vector<string>& ans) {
    if (i == n-1 && j == n-1) {
        ans.push_back(direction); return;
    }
    if (m[i][j] == 0) {
        return;
    } else {
        m[i][j] = 0;
        if (i-1 >= 0 && m[i-1][j] != 0) {
            findWays (m, i-1, j, n, direction+'U', ans);
        }
        if (i+1 < n && m[i+1][j] != 0) {
            findWays (m, i+1, j, n, direction+'D', ans);
        }
        if (j-1 >= 0 && m[i][j-1] != 0) {
            findWays (m, i, j-1, n, direction+'L', ans);
        }
        if (j+1 < n && m[i][j+1] != 0) {
            findWays (m, i, j+1, n, direction+'R', ans);
        }
        m[i][j] = 1;
    }
}
vector<string> findPath(vector<vector<int>> &m, int n) {
    // Your code goes here
    vector<string> ans;
    findWays (m, 0, 0, n, "", ans);
    return ans;
}

//N Queens Problem 
bool isSafe (vector<string>& chessB, int i, int j) {
    for (int k = 0; k < chessB.size(); k++) {
        if (chessB[k][j] == 'Q') return false;
    }
    for (int k = 0; k < chessB.size(); k++) {
        if (chessB[i][k] == 'Q') return false;
    }
    for (int k = i, l = j; k >= 0 && l >= 0; k--, l--) {
        if (chessB[k][l] == 'Q') return false;
    }
    for (int k = i, l = j; k < chessB.size() && l < chessB.size(); k++, l++) {
        if (chessB[k][l] == 'Q') return false;
    }
    for (int k = i, l = j; k < chessB.size() && l >= 0; k++, l--) {
        if (chessB[k][l] == 'Q') return false;
    }
    for (int k = i, l = j; k >= 0 && l < chessB.size(); k--, l++) {
        if (chessB[k][l] == 'Q') return false;
    }
    return true;
}
void queenSol (vector<vector<string>>& ans, vector<string>& chessB, int i) {
    if (i == chessB.size()) {
        ans.push_back(chessB);
        return;
    }
    for (int j = 0; j < chessB.size(); j++) {
        if (isSafe(chessB, i, j)) {
            chessB[i][j] = 'Q';
            queenSol (ans, chessB, i+1);
            chessB[i][j] = '.';
        }
    }
}
vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> ans;
    vector<string> chessB(n, string(n, '.'));
    queenSol (ans, chessB, 0);
    return ans;
}

//Generate all parentheses from pair of parentheses
void generate (vector<string>& ans, string s, int open, int close) {
    if (open == 0 && close == 0) {
        ans.push_back(s); return;
    }
    s += '(';
    if (open > 0) generate(ans, s, open-1, close);
    s.pop_back();
    s += ')';
    if (open < close) generate(ans, s, open, close-1);
    s.pop_back();
}

vector<string> generateParenthesis(int n) {
    vector<string> set;
    generate(set, "", n, n);
    return set;
}

//Letter Combinations of a phone number:
void recSol (vector<string>& ans, unordered_map<int, string>& map, string digits, int numInd, string comb) {
    if (comb.size() == digits.size()) {
        ans.push_back(comb); return;
    }
    string s = map[digits[numInd]-'0'];
    for (int i = 0; i < s.size(); i++) {
        recSol (ans, map, digits, numInd+1, comb+s[i]);
    }
}

vector<string> letterCombinations(string digits) {
    vector<string> ans;
    if (digits.size() == 0) return ans;
    unordered_map<int, string> map;
    map[2] = "abc"; map[3] = "def"; map[4] = "ghi"; map[5] = "jkl"; map[6] = "mno"; map[7] = "pqrs"; map[8] = "tuv"; map[9] = "wxyz";
    recSol (ans, map, digits, 0, "");
    return ans;
}

// Sudoku Solver (very very important!!!) 
bool isValidEntry (vector<vector<char>>& board, int row, int col, int val) {
    int n = board.size();

    for(int i=0; i<n; i++) {
        if(board[row][i] == val+'0')
            return false;
        if(board[i][col] == val+'0') 
            return false;

        //3*3 box check
        if(board[3*(row/3)+(i/3)][3*(col/3)+(i%3)] == val+'0') 
            return false;
    }

    return true;
}
bool generateValidSudoku (vector<vector<char>>& board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == '.') {
                for (char k = 1; k <= 9; k++) {
                    if (isValidEntry(board, i, j, k)) {
                        board[i][j] = k+'0';
                        bool val = generateValidSudoku (board);
                        if (val == true){
                            return true;
                        } else {
                            board[i][j] = '.';
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}
void solveSudoku(vector<vector<char>>& board) {
    generateValidSudoku (board);
}

//Combination Sum-1 Leetcode
void findCombos (vector<vector<int>>& ans, vector<int> candidates, vector<int>& poss, int target, int index) {
    if (target <= 0) {
        if (target == 0) {
            ans.push_back(poss);
        }
        return;
    }
    for (int i = index; i < candidates.size(); i++) {
        poss.push_back(candidates[i]);
        findCombos (ans, candidates, poss, target-candidates[i], i);
        poss.pop_back();
    }
}
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> s;
    vector<int> poss;
    findCombos (s, candidates, poss, target, 0);
    return s;
}

//Combination Sum-2 Leetcode
void recSol (vector<vector<int>>& ans, vector<int>& candidates, vector<int>& s, int target, int index) {
    if (target <= 0) {
        if (target == 0) ans.push_back(s);
        return;
    }
    for (int i = index; i < candidates.size(); i++) {
        if (i > index && candidates[i] == candidates[i-1]) continue;
        s.push_back(candidates[i]);
        recSol (ans, candidates, s, target-candidates[i], i+1);
        s.pop_back();
    }
}
vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    vector<vector<int>> set;
    vector<int> s;
    sort (candidates.begin(), candidates.end());
    recSol (set, candidates, s, target, 0);
    return set;
}

//Find permutations of an array : 
 void permuteRec (vector<vector<int>>& ans, vector<int>& nums, int ind) {
    if (ind == nums.size()) {
        ans.push_back (nums);
    }
    for (int i = ind; i < nums.size(); i++) {
        swap (nums[i], nums[ind]);
        permuteRec (ans, nums, ind+1);
        swap (nums[i], nums[ind]);
    }
}
vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> ans;
    permuteRec (ans, nums, 0);
    return ans;
}

//Find Permutations 2 - Leetcode (distinct permutations containing duplicates)
void permuteRec (vector<vector<int>>& ans, vector<int>& nums, int ind) {
    if (ind == nums.size()) {
        ans.push_back(nums);
    }
    unordered_map<int, bool> map;
    for (int i = ind; i < nums.size(); i++) {
        if (map.find(nums[i]) != map.end()) continue;
        map[nums[i]] = true;
        swap (nums[i], nums[ind]);
        permuteRec (ans, nums, ind+1);
        swap (nums[i], nums[ind]);
    }
}
vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<vector<int>> ans;
    permuteRec (ans, nums, 0);
    return ans;
}

//Beautiful Arrangement - Leetcode : 
void countRec (vector<int>& store, int ind, int& count) {
    if (ind == store.size()) {
        count++; return;
    }
    for (int i = 1; i < store.size(); i++) {
        if (store[i] == 0 && (ind%i == 0 || i%ind == 0)) {
            store[i] = ind;
            countRec (store, ind+1, count);
            store[i] = 0;
        }
    }
}
int countArrangement(int n) {
    vector<int> store (n+1, 0);
    int count = 0;
    countRec(store, 1, count);
    return count;
}

//Distribute repeating integers among quantity array (Leetcode) : 
bool recSol (vector<int>& counts, vector<int>& quantity, int ind) {
    if (ind == quantity.size()) return true;
    for (int i = 0; i < counts.size(); i++) {
        if (quantity[ind] <= counts[i]) {
            counts[i] -= quantity[ind];
            if (recSol (counts, quantity, ind+1)) {
                return true;
            }
            counts[i] += quantity[ind];
        }
    }
    return false;
}
bool canDistribute(vector<int>& nums, vector<int>& quantity) {
    unordered_map<int, int> countMap;
    for (auto i : nums) {
        if (countMap.find(i) == countMap.end()) {
            countMap[i] = 1;
        } else {
            countMap[i]++;
        }
    }
    vector<int> countArr;
    for (auto i : countMap) {
        countArr.push_back(i.second);
    }
    sort(quantity.rbegin(), quantity.rend());
    return recSol (countArr, quantity, 0);
}

// Print all ascending permutations of a binary string of given size (VVV Imp) :
void generate (int arr[], int n, int k) {
    if (n == k) {
        for (int i = 0; i < n; i++) cout << arr[i] << " ";
        cout << endl;
        return;
    }
    arr[k] = 0;
    generate (arr, n, k+1);
    arr[k] = 1;
    generate (arr, n, k+1);
}

void generateAllBinaryStrings(int n) 
{
    int* arr = new int[n];
    generate (arr, n, 0);
} 

// Partition array into k subsets of same value (VVV IMP!) : 
bool recSol (vector<int>& nums, vector<bool>& vis, int k, int ind, int sum, int target) {
    if (k == 0) return true;
    if (sum == target) {
        return recSol (nums, vis, k-1, 0, 0, target);
    }
    
    for (int i = ind; i < nums.size(); i++) {
        if (vis[i] == true || nums[i]+sum > target) continue;
        vis[i] = true;
        if (recSol(nums, vis, k, i+1, sum+nums[i], target)) return true;
        vis[i] = false;
    }
    
    return false;
}
bool canPartitionKSubsets(vector<int>& nums, int k) {
    int total = 0;
    for (int i = 0; i < nums.size(); i++) {
        total += nums[i];
    }
    if (total%k != 0) return false;
    sort (nums.begin(), nums.end(), [](int& n1, int& n2) {
        return n1 > n2;
    });
    vector<bool> vis (nums.size(), false);
    return recSol (nums, vis, k, 0, 0, total/k);
}

// Max Length of Concatenated String with Unique Characters :
bool isUnique (string word) {
    unordered_set<char> set;
    for (auto c: word) {
        if (set.find(c) != set.end()) return false;
        else set.insert(c);
    }
    return true;
}
int recSol (vector<string>& arr, string word, int ind) {
    if (!isUnique(word)) return 0;
    if (ind == arr.size()) return word.size();
    
    int ans = word.size();
    for (int i = ind; i < arr.size(); i++) {
        ans = max(ans, recSol (arr, word+arr[i], i+1));
    }
    return ans;
}
int maxLength(vector<string>& arr) {
    return recSol (arr, "", 0);
}