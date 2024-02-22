// Replace Words Leetcode : 
class TrieNode {
public:
    char data; TrieNode* children[26]; bool isTerminal;
    TrieNode (char c) {
        data = c; isTerminal = false;
        for (int i = 0; i < 26; i++) children[i] = nullptr;
    }
};

void insertIntoTrie (TrieNode* root, string word) {
    if (word.size() == 0) { root->isTerminal = true; return; }
    if (!root->children[word[0]-'a']) {
        root->children[word[0]-'a'] = new TrieNode (word[0]);
    }
    TrieNode* child = root->children[word[0]-'a'];
    insertIntoTrie (child, word.substr(1));
}

string search (TrieNode* root, string word) {
    string str = "";
    for (auto c: word) {
        TrieNode* child = root->children[c-'a'];
        if (!child) break;
        str += c;
        if (child->isTerminal) return str;
        root = child;
    }
    return word;
}

class Solution {
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        vector<string> arr; string str = "";
        TrieNode* root = new TrieNode('-');
        for (auto c: sentence) {
            if (c == ' ') {
                arr.push_back(str); str = "";
            } else str += c;
        }
        arr.push_back(str);
        for (auto str: dictionary) insertIntoTrie (root, str);
        str = "";
        for (auto s: arr) {
            str += search (root, s); str += ' ';
        }
        str.pop_back();
        return str;
    }
};

// Palindrome Pairs Leetcode (VVVVV IMPORTANT!!) : 
class TrieNode {
public: 
    char data; TrieNode* children[26]; int index; vector<int> palindromicIndexes;
    TrieNode (char c) {
        data = c; 
        for (int i = 0; i < 26; i++) children[i] = nullptr;
        index = -1;
    }
};

class Solution {
public:
    bool isPal (string word, int st, int end) {
        while (st < end) {
            if (word[st++] != word[end--]) return false;
        }
        return true;
    }
    void insertIntoTrie (TrieNode* root, string word, int index) {
        for (int j = word.size()-1; j >= 0; j--) {
            if (!root->children[word[j]-'a']) {
                root->children[word[j]-'a'] = new TrieNode (word[j]);
            }
            if (isPal (word, 0, j)) {
                root->palindromicIndexes.push_back(index);
            }
            root = root->children[word[j]-'a'];
        }
        root->index = index;
        root->palindromicIndexes.push_back(index);
    }
    void search (TrieNode* root, string word, vector<vector<int>>& res, int index) {
        for (int j = 0; j < word.size(); j++) {
            if (root->index >= 0 && root->index != index && isPal (word, j, word.size()-1)) res.push_back ({index, root->index});
            root = root->children[word[j]-'a'];
            if (!root) return;
        }
        for (auto i : root->palindromicIndexes) {
            if (i == index) continue;
            res.push_back ({index, i});
        }
    }
    vector<vector<int>> palindromePairs(vector<string>& words) {
        TrieNode* root = new TrieNode ('-');
        vector<vector<int>> res;
        for (int i = 0; i < words.size(); i++) {
            insertIntoTrie (root, words[i], i);
        }
        for (int i = 0; i < words.size(); i++) {
            search (root, words[i], res, i);
        }
        return res;
    }
};

// Get AutoComplete Strings from a Search String out of the dictionary array of strings provided : 
void complete (TrieNode* root, vector<string>& res, string addition) {
  if (!root) return;
  if (root->isTerminal) {
    res.push_back(addition);
  }
  for (int i = 0; i < 26; i++) {
    if (root->children[i]) {
      addition += root->children[i]->data;
      complete (root->children[i], res, addition);
      addition.pop_back();
    }
  }
}

void autoComplete (TrieNode* root, string str, vector<string>& res, string addition) {
  if (str.size() == 0) {
    complete (root, res, addition);
    return;
  }
  TrieNode* child = root->children[str[0]-'a'];
  if (!child) return;
  addition += str[0];
  autoComplete (child, str.substr(1), res, addition);
}

vector<string> getAutoCompleted (vector<string> arr, string search) {
  TrieNode* root = new TrieNode ('-');
  for (auto i : arr) insertIntoTrie (root, i);
  vector<string> res; string str = "";
  autoComplete (root, search, res, str); 
  return res;
} 

// Search Suggestions System : 
class Node {
public: 
    char c; 
    vector<Node*> children; 
    bool isTerminal;
    
    Node (char c1) {
        c = c1;
        children = vector<Node*> (26, nullptr);
        isTerminal = false;
    }
};

class Trie {
public: 
    vector<Node*> starts = vector<Node*> (26, nullptr);
    
    void insertWords (vector<string>& products) {
        for (auto s : products) {
            Node* startNode = starts[s[0]-'a'];
            if (startNode == nullptr) {
                startNode = new Node (s[0]);
                starts[s[0]-'a'] = startNode;
            }
            
            for (int i = 1; i < s.size(); i++) {
                if (!startNode->children[s[i]-'a']) {
                   startNode->children[s[i]-'a']  = new Node (s[i]);
                }
                Node* child = startNode->children[s[i]-'a'];
                startNode = child;
            }
            
            startNode->isTerminal = true;
        }
    }
    
    void recSol (vector<string>& ans, Node* startFrom, string& search, int& k) {
        if (k == 0 || startFrom == nullptr) return;
        if (startFrom->isTerminal) {
            ans.push_back(search);
            k--;
        }
        
        for (int i = 0; i < 26; i++) {
            if (startFrom->children[i] != nullptr) {
                Node* curr = startFrom->children[i];
                search += curr->c;
                recSol (ans, curr, search, k);
                search.pop_back();
            }
        }
    }
    
    vector<string> suggestions (string search) {
        int i = 1;
        Node* startFrom = starts[search[0]-'a'];
        
        while (i < search.size() && startFrom != nullptr) {
            startFrom = startFrom->children[search[i]-'a'];
            i++;
        }
        
        vector<string> ans;
        int k = 3;
        
        recSol (ans, startFrom, search, k);
        return ans;
    }
    
    
};

class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        Trie* trie = new Trie();
        trie->insertWords (products);
        
        vector<vector<string>> ans;
        string str = "";
        for (int i = 0; i < searchWord.size(); i++) {
            str += searchWord[i];
            ans.push_back(trie->suggestions(str));
        }
        
        return ans;
    }
};