// Longest Common Subsequence (VVVV Imp!)
int recSol (string& text1, string& text2, int ind1, int ind2, vector<vector<int>>& dp) {
    if (ind1 >= text1.size() || ind2 >= text2.size()) return 0;
    if (dp[ind1][ind2] != -1) return dp[ind1][ind2];

    if (text1[ind1] == text2[ind2]) return dp[ind1][ind2] = 1 + recSol (text1, text2, ind1+1, ind2+1, dp);
    return dp[ind1][ind2] = max (recSol (text1, text2, ind1+1, ind2, dp), recSol (text1, text2, ind1, ind2+1, dp));
}
int bottomUp (string& text1, string& text2) {
    vector<vector<int>> dp (text1.size()+1, vector<int> (text2.size()+1, 0));
    for (int i = text1.size()-1; i >= 0; i--) {
        for (int j = text2.size()-1; j >= 0; j--) {
            if (text1[i] == text2[j]) dp[i][j] = 1 + dp[i+1][j+1];
            else dp[i][j] = max (dp[i+1][j], dp[i][j+1]);
        }
    }

    return dp[0][0];
}
int longestCommonSubsequence(string text1, string text2) {
    vector<vector<int>> dp (text1.size()+1, vector<int> (text2.size()+1, -1));
    return bottomUp(text1, text2);
}

// Longest Palindromic Subsequence (VVVVV Imp!) (Also totally same as LCS Problem): 
int recSol (string& text1, string& text2, int ind1, int ind2, vector<vector<int>>& dp) {
    if (ind1 >= text1.size() || ind2 >= text2.size()) return 0;
    if (dp[ind1][ind2] != -1) return dp[ind1][ind2];

    if (text1[ind1] == text2[ind2]) return dp[ind1][ind2] = 1 + recSol (text1, text2, ind1+1, ind2+1, dp);
    return dp[ind1][ind2] = max (recSol (text1, text2, ind1+1, ind2, dp), recSol (text1, text2, ind1, ind2+1, dp));
}
int longestPalindromeSubseq(string s) {
    string s1 = s;
    reverse (s1.begin(), s1.end());
    string text1 = s, text2 = s1;
    vector<vector<int>> dp (text1.size()+1, vector<int> (text2.size()+1, 0));

    for (int i = text1.size()-1; i >= 0; i--) {
        for (int j = text2.size()-1; j >= 0; j--) {

            if (text1[i] == text2[j]) dp[i][j] = 1 + dp[i+1][j+1];
            else dp[i][j] = max (dp[i+1][j], dp[i][j+1]);

        }
    }

    return dp[0][0];
}

// Edit Distance (Super Important) (You need to update, delete or insert characters to string 1 to make it equal to string 2): 
int recSol (string word1, string word2, int ind1, int ind2) {
    if (ind1 == word1.size()) return word2.size()-ind2;
    if (ind2 == word2.size()) return word1.size()-ind1;

    if (word1[ind1] == word2[ind2]) return recSol (word1, word2, ind1+1, ind2+1);
    else {
        int update = 1 + recSol (word1, word2, ind1+1, ind2+1);
        int del = 1 + recSol (word1, word2, ind1+1, ind2);
        int add = 1 + recSol (word1, word2, ind1, ind2+1);

        return min ({update, del, add});
    }
}
int minDistance(string word1, string word2) {
    // return recSol (word1, word2, 0, 0);
    vector<vector<int>> dp (word1.size()+1, vector<int> (word2.size()+1, 0));

    for (int i = 0; i <= word2.size(); i++) dp[word1.size()][i] = word2.size() - i;
    for (int i = 0; i <= word1.size(); i++) dp[i][word2.size()] = word1.size() - i;

    for (int i = word1.size()-1; i >= 0; i--) {
        for (int j = word2.size()-1; j >= 0; j--) {

            if (word1[i] == word2[j]) dp[i][j] = dp[i+1][j+1];
            else {
                int update = 1 + dp[i+1][j+1];
                int del = 1 + dp[i+1][j];
                int add = 1 + dp[i][j+1];

                dp[i][j] = min ({update, del, add});
            }

        }
    }

    return dp[0][0];
}

// Distinct Subsequences (Super Important too, find total number of ways you can generate word2 from word1) : 
int recSol (string s, string t, int i1, int i2) {
    if (i2 == t.size()) return 1;
    if (i1 == s.size() && i2 != t.size()) return 0;

    if (s[i1] == t[i2]) return (recSol (s, t, i1+1, i2) + recSol (s, t, i1+1, i2+1));
    else return recSol (s, t, i1+1, i2);
}
int numDistinct(string s, string t) {
    // return recSol (s, t, 0, 0);

    if (s == t) return 1;
    vector<vector<double>> dp (s.size()+1, vector<double> (t.size()+1, 0));
    for (int i = 0; i <= s.size(); i++) dp[i][t.size()] = 1;
    
    for (int i = s.size()-1; i >= 0; i--) {
        for (int j = t.size()-1; j >= 0; j--) {

            if (s[i] == t[j]) dp[i][j] = dp[i+1][j] + dp[i+1][j+1];
            else dp[i][j] = dp[i+1][j];

        }
    }

    double ans = dp[0][0];
    if(ans > INT_MAX)
        return -1;
    return (int)dp[0][0];
}

// Word Break : 
bool subExists ( vector<string>& wordDict, string sub) {
    for (auto i: wordDict) if (i == sub) return true;
    return false;
}
bool recSol (string s, vector<string>& wordDict, int start, vector<int>& dp) {
    if (start == s.size()) return true;
    if (dp[start] != -1) return dp[start];

    string sub = "";
    bool flag = false;
    for (int i = start; i < s.size(); i++) {
        sub += s[i];
        if (subExists (wordDict, sub)) {
            flag = flag || recSol (s, wordDict, i+1, dp);
        }
    }

    return dp[start] = flag;
}
bool bottomUp (string s, vector<string>& wordDict) {
    vector<int> dp (s.size()+1, 0);
    dp[s.size()] = 1;

    for (int i = s.size()-1; i >= 0; i--) {
        string sub = "";
        bool flag = false;
        for (int k = i; k < s.size(); k++) {
            sub += s[k];
            if (subExists (wordDict, sub)) {
                flag = flag || dp[k+1];
            }
        }

        dp[i] = flag;
    }

    return dp[0];
}
bool wordBreak(string s, vector<string>& wordDict) {
    vector<int> dp (s.size()+1, -1);
    return bottomUp(s, wordDict);
}

// Word Break 2 : 
bool subExist (string s, vector<string>& wordDict) {
    for (auto i : wordDict) if (s == i) return true;
    return false;
}
void recSol (string s, vector<string>& wordDict, int ind, string miniSt, vector<string>& ans) {
    if (ind == s.size()) {
        if (miniSt.size() > 0) miniSt.pop_back();
        ans.push_back(miniSt);
        return;
    }

    string str = ""; 
    for (int i = ind; i < s.size(); i++) {
        str += s[i];
        if (subExist (str, wordDict)) {
            recSol (s, wordDict, i+1, (miniSt+str+" "), ans);
        }
    }
}
vector<string> wordBreak(string s, vector<string>& wordDict) {
    vector<string> ans;
    recSol (s, wordDict, 0, "", ans);
    return ans;
}

// Minimum ASCII Delete Sum for 2 strings : 
int recSol (string& s1, string& s2, int indS1, int indS2, vector<vector<int>>& dp) {
    if (indS1 == s1.size()) {
        int sum = 0;
        for (int i = indS2; i < s2.size(); i++) {
            sum += s2[i];
        }
        return sum;
    }

    if (indS2 == s2.size()) {
        int sum = 0;
        for (int i = indS1; i < s1.size(); i++) {
            sum += s1[i];
        }
        return sum;
    }

    if (dp[indS1][indS2] != -1) return dp[indS1][indS2];

    if (s1[indS1] == s2[indS2]) return dp[indS1][indS2] = recSol (s1, s2, indS1+1, indS2+1, dp);
    return dp[indS1][indS2] = min (s1[indS1] + recSol (s1, s2, indS1+1, indS2, dp), s2[indS2] + recSol (s1, s2, indS1, indS2+1, dp));
}

int bottomUp (string& s1, string& s2) {
    vector<vector<int>> dp (s1.size()+1, vector<int> (s2.size()+1, 0));

    for (int i = s2.size()-1; i >= 0; i--) {
        dp[s1.size()][i] = s2[i] + dp[s1.size()][i+1];
    }

    for (int i = s1.size()-1; i >= 0; i--) {
        dp[i][s2.size()] = s1[i] + dp[i+1][s2.size()];
    }

    for (int i = s1.size()-1; i >= 0; i--) {
        for (int j = s2.size()-1; j >= 0; j--) {
            if (s1[i] == s2[j]) dp[i][j] = dp[i+1][j+1];
            else dp[i][j] = min (s1[i] + dp[i+1][j], s2[j] + dp[i][j+1]);
        }
    }

    return dp[0][0];
}

int minimumDeleteSum(string s1, string s2) {
    // vector<vector<int>> dp (s1.size()+1, vector<int> (s2.size()+1, -1));
    // return recSol (s1, s2, 0, 0, dp);
    return bottomUp (s1, s2);
}

// Interleaving String (Famous Important Question) :
bool recSol (string& s1, string& s2, string& s3, int ind1, int ind2, int ind3, vector<vector<vector<int>>>& dp) {
    if (ind1 == s1.size() && ind2 == s2.size() && ind3 == s3.size()) return true;

    if (dp[ind1][ind2][ind3] != -1) return dp[ind1][ind2][ind3];

    if (s1[ind1] == s3[ind3] && s2[ind2] == s3[ind3]) return dp[ind1][ind2][ind3] = recSol (s1, s2, s3, ind1+1, ind2, ind3+1, dp) || recSol (s1, s2, s3, ind1, ind2+1, ind3+1, dp);
    if (s1[ind1] == s3[ind3]) return dp[ind1][ind2][ind3] = recSol (s1, s2, s3, ind1+1, ind2, ind3+1, dp);
    if (s2[ind2] == s3[ind3]) return dp[ind1][ind2][ind3] = recSol (s1, s2, s3, ind1, ind2+1, ind3+1, dp);
    return dp[ind1][ind2][ind3] = false;
}

bool bottomUp (string& s1, string& s2, string& s3) {
    vector<vector<vector<int>>> dp (s1.size()+1, vector<vector<int>> (s2.size()+1, vector<int> (s3.size()+1, 0)));
    dp[s1.size()][s2.size()][s3.size()] = 1;

    for (int i = s1.size(); i >= 0; i--) {
        for (int j = s2.size(); j >= 0; j--) {
            for (int k = s3.size(); k >= 0; k--) {
                if (i == s1.size() && j == s2.size() && k == s3.size()) {
                    dp[i][j][k] = 1; continue;
                }
                if (i < s1.size() && j < s2.size() && s1[i] == s3[k] && s2[j] == s3[k]) dp[i][j][k] = dp[i+1][j][k+1] || dp[i][j+1][k+1];
                else if (i < s1.size() && s1[i] == s3[k]) dp[i][j][k] = dp[i+1][j][k+1];
                else if (j < s2.size() && s2[j] == s3[k]) dp[i][j][k] = dp[i][j+1][k+1];
            }
        }
    }

    return dp[0][0][0];
}

bool isInterleave(string s1, string s2, string s3) {
    // vector<vector<vector<int>>> dp (s1.size()+1, vector<vector<int>> (s2.size()+1, vector<int> (s3.size()+1, -1)));
    // if (s1.size() + s2.size() != s3.size()) return false;
    // return recSol (s1, s2, s3, 0, 0, 0, dp);

    return bottomUp (s1, s2, s3);
}

// Minimum number of words to be inserted into given word to make it a palindrome : 
int recSol (string s1, string s2, int ind1, int ind2) {
    if (ind1 == s1.size() || ind2 == s2.size()) return 0;

    if (s1[ind1] == s2[ind2]) return  1 + recSol (s1, s2, ind1+1, ind2+1);
    return max (recSol (s1, s2, ind1+1, ind2), recSol (s1, s2, ind1, ind2+1));
}

int bottomUp (string s1, string s2) {
    vector<vector<int>> dp (s1.size()+1, vector<int> (s1.size()+1, 0));

    for (int i = s1.size()-1; i >= 0; i--) {
        for (int j = s2.size()-1; j >= 0; j--) {

            if (s1[i] == s2[j]) dp[i][j] = 1 + dp[i+1][j+1];
            else dp[i][j] = max (dp[i+1][j], dp[i][j+1]);

        }
    }

    return dp[0][0];
}

int minInsertions(string s) {
    string s1 = s;
    reverse (s1.begin(), s1.end());
    // return s.size()-recSol (s, s1, 0, 0);
    return s.size()-bottomUp (s, s1);
}