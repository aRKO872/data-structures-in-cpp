#include <iostream>
#include <utility>
#include <vector>
using namespace std;

pair<int, int> maxMin (int arr[][5], int n) {
  int min = INT_MAX;
  int max = INT_MIN;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (min > arr[i][j]) {
        min = arr[i][j];
      }
      if (max < arr[i][j]) {
        max = arr[i][j];
      }
    }
  }
  pair<int, int> ans = make_pair(max, min);
  return ans;
}

pair<int, int> getColWithGreatSum(int arr[][5], int n) {
  int sum = INT_MIN;
  int ansIndex = -1;
  pair<int, int> ans;
  for (int i = 0; i < n; i++) {
    int rowSum = 0;
    for (int j = 0; j < n; j++) {
      rowSum += arr[i][j];
    }
    if (rowSum > sum) {
      sum = rowSum;
      ansIndex = i;
    }
  }
  ans = make_pair(sum, ansIndex);
  return ans;
}

vector<vector<int>> transpose(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    vector<vector<int>> transposed(m, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }
    return transposed;
}

vector<int> spiralOrder(vector<vector<int>>& matrix) {
    int up = 0, right = matrix[0].size()-1, down = matrix.size()-1, left = 0, dec = 0;
    vector<int> ans;
    while (up <= down && left <= right) {
        if (dec == 0) {
            for (int i = left; i <= right; i++) {
                ans.push_back(matrix[up][i]);
            }
            up++;
        } else if (dec == 1) {
            for (int i = up; i <= down; i++) {
                ans.push_back(matrix[i][right]);
            }
            right--;
        } else if (dec == 2) {
            for (int i = right; i >= left; i--) {
                ans.push_back(matrix[down][i]);
            }
            down--;
        } else {
            for (int i = down; i >= up; i--) {
                ans.push_back(matrix[i][left]);
            }
            left++;
        }
        dec++;
        dec = dec%4;
    }
    return ans;
}

vector<int> wavePrint(vector<vector<int>> arr, int nRows, int mCols)
{
    //Write your code here
    vector<int> ans;
    int above = 0;
    while (above < mCols) {
        if (above % 2 == 0) {
            for (int i = 0; i < nRows; i++) {
                ans.push_back(arr[i][above]);
            }
        } else {
            for (int i = nRows-1; i >= 0; i--) {
                ans.push_back(arr[i][above]);
            }
        }
        above++;
    }
    return ans;
}

vector<int> findMaxRow(vector<vector<int>> mat, int N) {
    //code here
    int i = 0, j = N-1, row = 0, count = 0;
    while (i < N && j >= 0) {
        if (mat[i][j] == 1) {
            row = i;
            count++;
            j--;
        } else {
            i++;
        }
    }
    return {row, count};
}

int main () {
  vector<vector<int> > arr = {
    { 1, 2, 3, 4, 5 },
    { 5, 3, 1, 4, 2 },
    { 5, 6, 7, 8, 9 },
    { 0, 6, 3, 4, 12 },
    { 9, 7, 12, 4, 31 },
  };
  vector<int> ans = wavePrint(arr, 5, 5);
  cout << ans;
}

//check if sudoku is valid or not (Leetcode)
bool isValidEntry (vector<vector<char>>& board, int row, int col, int val) {
    for (int i = 0; i < board.size(); i++) {
        if (board[i][col] == val+'0' && i != row) return false;
        if (board[row][i] == val+'0' && i != col) return false;
        if (board[3*(row/3)+(i/3)][3*(col/3)+(i%3)] == val+'0' && (3*(row/3)+(i/3)) != row && (3*(col/3)+i%3) != col) return false;
    }
    return true;
}
bool isValidSudoku(vector<vector<char>>& board) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            if (board[i][j] != '.') {
                if (!isValidEntry(board, i, j, board[i][j]-'0')){ 
                    cout << i << " " << j;
                    return false;
                }
            }
        }
    }
    return true;
}