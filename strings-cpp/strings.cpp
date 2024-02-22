string removeDuplicates(string s) {
    string ans = "";
    ans.push_back(s[0]);
    cout << s.length();
    for (int i = 1; i < s.length(); i++) {
        if (ans.length() > 0 && ans[ans.length()-1] == s[i]) {
            ans.pop_back();
        } else {
            ans.push_back(s[i]);
        }
    }
    return ans;
}

string removeOccurrences(string s, string part) {
    int up = part.length();
    while (s.find(part) != string::npos) {
        int ind = s.find(part);
        s.erase(ind, up);
    }
    return s;
}

//Almost Palindrome
bool isPalindrome (string s, int st, int end) {
    while (st <= end) {
        if (s[st] != s[end]) {
            return false;
        } else {
            st++; end--;
        }
    }
    return true;
}
bool validPalindrome(string s) {
    int st = 0, end = s.length()-1;
    while (st <= end) {
        if (s[st] != s[end]) {
            return isPalindrome (s, st+1, end) || isPalindrome (s, st, end-1);
        } else {
            st++; end--;
        }
    }
    return true;
}

//Minimum Time Difference
int time(string times) {
    int mins = (stoi(times.substr(0, 2))*60) + stoi(times.substr(3, 5));
    return mins;
}
int findMinDifference(vector<string>& timePoints) {
    vector<int> timeArray;
    for (int i = 0; i < timePoints.size(); i++) {
        timeArray.push_back(time(timePoints[i]));
    }
    sort (timeArray.begin(), timeArray.end());
    int minTime = INT_MAX;
    for (int i = 0; i < timeArray.size()-1; i++) {
        minTime = min(minTime, (timeArray[i+1] - timeArray[i]));
    }
    int lastDiff = (timeArray[0]+1440) - timeArray[timePoints.size()-1];
    minTime = min (minTime, lastDiff);
    return minTime;
}

//Find all Palindromic Substrings:
int countSubstrings(string s) {
    int count = 0;
    for (int i = 0; i < s.length(); i++) {
        int m = i, n = i;
        while (m >= 0 && n <= s.length()-1 && s[m] == s[n]) {
            count++; 
            m--; n++;
        }
        m = i, n = i+1;
        while (m >= 0 && n <= s.length()-1 && s[m] == s[n]) {
            count++;
            m--; n++;
        }
    }
    return count;
}

//Arrange array of numbers such that they give the largest number:
string largestNumber(vector<int>& nums) {
    vector<string> res;
    for (int i = 0; i < nums.size(); i++) {
        res.push_back(to_string(nums[i]));
    }
    sort(res.begin(), res.end(), [](string& s1, string& s2) {return s1+s2>s2+s1;});
    string ans = "";
    for (auto i : res) {
        ans += i;
    }
    while (ans[0] == '0' && ans.length() != 1) ans.erase(0,1);
    return ans;
}

//Sort string based on an order string :
string customSortString(string order, string s) {
    sort(s.begin(), s.end(), [&](char a, char b) { return order.find(a) < order.find(b);});
    return s;
}

//verify alien dictionary
bool areTwoSorted (string a, string b, string order) {
    int len = a.length() > b.length() ? b.length() : a.length();
    for (int i = 0; i < len; i++) {
        if (order.find(a[i]) > order.find(b[i])) {
            return false;
        } else if (order.find(a[i]) < order.find(b[i])) {
            return true;
        } else {
            continue;
        }
    }
    if (b.length() < a.length()) {
        return false;
    }
    return true;
}
bool isAlienSorted(vector<string>& words, string order) {
    for (int i = 0; i < words.size()-1; i++) {
        if (!areTwoSorted(words[i], words[i+1], order)) {
            return false;
        }
    }
    return true;
}

// longest word in dictionary through deleting : 
bool isPresent (string bigger, string smaller) {
    if (smaller.length() > bigger.length()) {
        return false;
    }
    int i = 0, j = 0;
    while (i < bigger.length() && j < smaller.length()) {
        if (bigger[i] == smaller[j]) {
            j++;
        }
        i++;
    }
    return (j == smaller.length());
}
string findLongestWord(string s, vector<string>& dictionary) {
    string res = "";
    for (auto str : dictionary) {
        if (isPresent (s, str)) {
            if (str.size() > res.size() || (str.size() == res.size() && str < res))
                res = str;
        }
    }
    return res;
}

//Longest Common Prefix 
string longestCommonPrefix(vector<string>& strs) {
    string res = ""; int count = 0;
    int minLen = strs[0].length();
    for (auto i : strs) {
        minLen = i.length() > minLen ? minLen : i.length();
    }
    cout << minLen;
    for (int i = 0; i < minLen; i++) {
        for (int j = 1; j < strs.size(); j++) {
            if (strs[j][i] != strs[j-1][i]) {
                return res;
            }
        }
        res += strs[0][i];
    }
    return res;
}

// Isomorphic Strings :
bool isIsomorphic(string s, string t) {
    if (s.length() != t.length()) return true;
    unordered_map <char, char> mapS;
    unordered_map <char, char> mapT;
    for (int i = 0; i < s.length(); i++) {
        if (mapS.find(s[i]) != mapS.end() && mapS[s[i]] != t[i]) {
            return false;
        }
        if (mapT.find(t[i]) != mapT.end() && mapT[t[i]] != s[i]) {
            return false;
        }
        mapS[s[i]] = t[i];
        mapT[t[i]] = s[i];
    }
    return true;
}

//Reorganize String so that no same characters are adjacent (Approach using sort and vector of pairs): 
string reorganizeString(string s) {
    if (s.size() == 1) return s;
    string res = "";
    for (int i = 0; i < s.size(); i++) res += " ";
    unordered_map<char, int> map;
    vector<char> mapChar;
    vector<int> mapValue;
    for (auto i: s) map[i]++;
    vector<pair<char, int>> vecRes(map.begin(), map.end());
    sort(vecRes.begin(), vecRes.end(), [](pair<char, int>& p1, pair<char, int> p2) {
        return p1.second > p2.second;
    });
    for (auto i: vecRes) {
        mapChar.push_back(i.first);
        mapValue.push_back(i.second);
    }
    int count = 0, ind = 0, mapInd = 0;
    while (count < res.length()) {
        if (res[ind] == ' ') {
            if (mapValue[mapInd] == 0) {
                mapInd++;
            }
            mapValue[mapInd]--;
            res[ind] = mapChar[mapInd];
            ind = (ind+2)%s.length();
            count++;
        } else {
            ind++;
        }
    }
    for (int i = 1; i < res.length(); i++) {
        if (res[i] == res[i-1]) {
            return "";
        }
    }
    return res;
}

//Group Anagrams : 
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<vector<string>> res;
    unordered_map<string, vector<string>> map;
    for (auto i: strs) {
        string j = i;
        sort(j.begin(), j.end());
        map[j].push_back(i);
    }
    for (auto i: map) {
        res.push_back(i.second);
    }
    return res;
}

//Longest Palindromic Substring
string longestPalindrome(string s) {
    string res = ""; int longest = 0;
    for (int i = 0; i < s.length(); i++) {
        int st = i, end = i, curr = 0;
        while (st >= 0 && end < s.length() && s[st] == s[end]) {
            curr = (end-st+1);
            if (curr > longest) {
                res = s.substr(st, (end-st+1));
                longest = curr;
            }
            st--; end++;
        }
        st = i, end = i+1;
        while (st >= 0 && end < s.length() && s[st] == s[end]) {
            curr = (end-st+1);
            if (curr > longest) {
                res = s.substr(st, (end-st+1));
                longest = curr;
            }
            st--; end++;
        }
    }
    return res;
}

//Needle in Haystack Problem
int strStr(string haystack, string needle) {
    if (needle.length() > haystack.length()) {
        return -1;
    } else if (needle.length() == haystack.length()) {
        if (needle != haystack) return -1;
        else return 0;
    } else {
        int hIt = 0;
        while (hIt < haystack.length() - needle.length()+1) {
            if (haystack[hIt] == needle[0]) {
                if (haystack.substr(hIt, needle.length()) == needle) {
                    return hIt;
                }
            }
            hIt++;
        }
        return -1;
    }
}

//String to Integer : 
int myAtoi(string s) {
    //return atoi(s.c_str());
    int st = 0, sign = 1;
    long long res = 0;
    while (s[st] == ' ') {
        st++;
    }
    if (s[st] == '-') {
        sign = -1; st++;
    } else if (s[st] == '+') st++;
    while (isdigit(s[st])) {
        res = (res*10) + (s[st]-'0'); st++;
        long long signedRes = res*sign;
        if (sign == -1) {
        if (signedRes <= INT_MIN) return INT_MIN;
        } else {
        if (signedRes >= INT_MAX) return INT_MAX;
        }
    }
    return res*sign;
}

//String Compression : 
int compress(vector<char>& chars) {
    int strInd = 0,  temp = 1, prev = chars[0];
    for (int i = 1; i < chars.size(); i++) {
        if (chars[i] == prev) {
            temp++;
        } else {
            chars[strInd++] = prev;
            if (temp > 1) {
                int num = temp, st = strInd;
                while (temp > 0) {
                    chars[strInd++] = temp%10 + '0';
                    temp /= 10;
                }
                reverse(chars.begin() + st, chars.begin()+ strInd);
                temp = 1;
            }
            prev = chars[i];
        }
    }
    chars[strInd++] = prev;
    if (temp > 1) {
        int num = temp, st = strInd;
        while (temp > 0) {
            chars[strInd++] = temp%10 + '0';
            temp /= 10;
        }
        reverse(chars.begin() + st, chars.begin()+ strInd);
    }
    return strInd;
}

//Integer to Roman
string intToRoman(int num) {
    vector<int> values{1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    vector<string> symbols{"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    string res = "";
    for (int i = 0; i < values.size(); i++) {
        while (num >= values[i]) {
            num -= values[i];
            res += symbols[i];
        }
    }
    return res;
}

//Zigzag pattern conversion:
string convert(string s, int numRows) {
    if (numRows == 1) return s;
    vector<string> res;
    string resString = "";
    for (int i = 0; i < numRows; i++) {
        string res1 = "";
        res.push_back(res1);
    }
    bool dec = true;
    int sIt = 0, row = 0;
    while (sIt < s.length()) {
        res[row] += s[sIt++];
        if (row == 0) dec = true;
        if (row == res.size()-1) dec = false;
        row = dec ? row+1 : row-1;
    }
    for (auto arr: res) {
        resString += arr;
    }
    return resString;
}

//Multiply 2 number strings : 
string add (string num1, string num2) {
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    int len = (num1.size() > num2.size()) ? num2.size() : num1.size();
    int k = 0, carry = 0; string ans = "";
    for (k = 0; k < len; k++) {
        int sum = (num1[k]-'0') + (num2[k]-'0') + carry;
        ans.push_back((sum%10)+'0');
        carry = sum/10;
    }
    while (k < num1.size()) {
        int sum = (num1[k++]-'0') + carry;
        ans.push_back((sum%10)+'0');
        carry = sum/10;
    }
    while (k < num2.size()) {
        int sum = (num2[k++]-'0') + carry;
        ans.push_back((sum%10)+'0');
        carry = sum/10;
    }
    while (carry > 0) {
        ans.push_back((carry%10)+'0');
        carry /= 10;
    }
    reverse (ans.begin(), ans.end()); return ans;
}
string multiply(string num1, string num2) {
    if (num1 == "0" || num2 == "0") return "0";
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    string a1, a2;
    if (num1.size() > num2.size()) {
        a1 = num2; a2 = num1;
    } else {
        a2 = num2; a1 = num1;
    }
    string rem = "0"; int zeroCount = 0;
    for (int i = 0; i < a1.size(); i++) {
        string s = ""; int carry = 0;
        for (int j = 0; j < a2.size(); j++) {
            int sum = ((a1[i]-'0')*(a2[j]-'0')) + carry;
            s += (sum%10)+'0';
            carry = sum/10;
        }
        while (carry > 0) {
            s.push_back((carry%10)+'0');
            carry /= 10;
        }
        reverse(s.begin(), s.end());
        string zeroes(zeroCount++, '0');
        s += zeroes;
        rem = add(rem, s);
    }
    return rem;
}

//Find Anagrams in String:
vector<int> findAnagrams(string s, string p) {
    if (s.size() < p.size()) return {};
    vector<int> ans;
    vector<int> freq (26, 0);
    vector<int> window (26, 0);
    for (int i = 0; i < p.size(); i++) {
        freq[p[i]-'a']++;
        window[s[i]-'a']++;
    }
    if (freq == window) ans.push_back(0);
    for (int i = p.size(); i < s.size(); i++) {
        window[s[i-p.size()]-'a']--;
        window[s[i]-'a']++;

        if (window == freq) ans.push_back(i-p.size()+1);
    }
    return ans;
}

// Minimum Substring Window : 
string smallestWindow (string s, string p)
{
    // Your code here
    if (p.size() > s.size()) return "-1";
    unordered_map<char, int> sMap;
    unordered_map<char, int> pMap;
    
    int sCount = 0, pCount = 0;
    int i = 0, j = 0;
    
    for (int k = 0; k < p.size(); k++) {
        if (pMap.find(p[k]) == pMap.end()) pMap[p[k]] = 1;
        else pMap[p[k]]++;
    }
    
    pCount = pMap.size();
    int ansLen = INT_MAX, start = -1;
    
    while (j < s.size()) {
        if (sMap.find(s[j]) == sMap.end()) sMap[s[j]] = 1;
        else sMap[s[j]]++;
        
        if (pMap.find(s[j]) != pMap.end() && pMap[s[j]] == sMap[s[j]]) {
            sCount++;
        }
        
        while (pCount == sCount) {
            if (ansLen > (j-i+1)) {
                ansLen = (j-i+1);
                start = i;
            }
            
            if (pMap.find(s[i]) != pMap.end() && sMap[s[i]] == pMap[s[i]]) {
                sCount--;
            }
            
            sMap[s[i]]--;
            i++;
        }
        j++;
    }
    
    return (ansLen == INT_MAX) ? "-1" : s.substr (start, ansLen);
}

// Basic Calculator 2 : (VVVV IMP!) :
string trim (string s) {
    int i = 0;
    string ans;
    while (i < s.size()) {
        if (s[i] != ' ') ans += s[i];
        i++;
    }
    return ans;
}
int calculate(string s) {
    s = trim (s);
    int ans = 0;
    int curr = 0;
    char op = '+';
    stack<int> st;
    
    for (int i = 0; i < s.size(); i++) {
        if (isdigit (s[i])) {
            curr = curr*10 + (s[i]-'0');
        }
        if (!isdigit (s[i]) || i == s.size()-1) {
            if (op == '+') {
                st.push(curr);
            } else if (op == '-') {
                st.push(-curr);
            } else if (op == '*') {
                curr = st.top()*curr; st.pop();
                st.push(curr);
            } else {
                curr = st.top()/curr; st.pop();
                st.push(curr);
            }
            op = s[i];
            curr = 0;
        }
    }
    
    while (!st.empty()) {
        ans += st.top();
        st.pop();
    }
    
    return ans;
}