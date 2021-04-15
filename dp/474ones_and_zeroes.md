You are given an array of binary strings `strs` and two integers `m` and `n`.

Return *the size of the largest subset of `strs` such that there are **at most*** `m` `0`*'s and* `n` `1`*'s in the subset*.

A set `x` is a **subset** of a set `y` if all elements of `x` are also elements of `y`.

 

**Example 1:**

```
Input: strs = ["10","0001","111001","1","0"], m = 5, n = 3
Output: 4
Explanation: The largest subset with at most 5 0's and 3 1's is {"10", "0001", "1", "0"}, so the answer is 4.
Other valid but smaller subsets include {"0001", "1"} and {"10", "1", "0"}.
{"111001"} is an invalid subset because it contains 4 1's, greater than the maximum of 3.
```

**Example 2:**

```
Input: strs = ["10","0","1"], m = 1, n = 1
Output: 2
Explanation: The largest subset is {"0", "1"}, so the answer is 2.
```

 

**Constraints:**

- `1 <= strs.length <= 600`
- `1 <= strs[i].length <= 100`
- `strs[i]` consists only of digits `'0'` and `'1'`.
- `1 <= m, n <= 100`





## Solution1

一个二维背包问题

```cpp
class Solution {
public:
    pair<int, int> count(string str) {
        int one = 0, zero = 0;
        for(int i = 0; i < str.size(); i++) {
            if(str[i] == '0') zero++;
            else if(str[i] == '1') one++;
        }
        pair<int, int> p; p.first = zero; p.second = one;
        return p;
    }
    int findMaxForm(vector<string>& strs, int m, int n) {
        int dp[601][110][110];
        vector<pair<int, int>> bitnumber;
        
        for(auto str : strs)
            bitnumber.push_back(count(str));
        
        for(int j = 0; j <= m; j++)
            for(int k = 0; k <= n; k++)
                dp[0][j][k] = 0;
        
        for(int i = 0; i < strs.size(); i++)
            dp[i][0][0] = 0;    
        
        for(int i = 1; i <= strs.size(); i++) {
            for(int j = 0; j <= m; j++) {
                for(int k = 0; k <= n; k++) {                   
                    if(j - bitnumber[i - 1].first >= 0 && k - bitnumber[i - 1].second >= 0) {
                        dp[i][j][k] = max(dp[i - 1][j][k], dp[i - 1][j - bitnumber[i - 1].first][k - bitnumber[i - 1].second] + 1);                       
                    } else {
                        dp[i][j][k] = dp[i - 1][j][k];
                    }
                }
            }
        }
        return dp[strs.size()][m][n];
        
    }
};
```



## Solution2: 状态压缩

```cpp
class Solution {
public:
    pair<int, int> count(string str) {
        int one = 0, zero = 0;
        for(int i = 0; i < str.size(); i++) {
            if(str[i] == '0') zero++;
            else if(str[i] == '1') one++;
        }
        return make_pair(zero, one);
    }
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        vector<pair<int, int>> bitnumber;
        
        for(auto str : strs) 
            bitnumber.push_back(count(str));
        
        for(int i = 1; i <= strs.size(); i++)
            for(int j = m; j >= bitnumber[i - 1].first; j--)
                for(int k = n; k >= bitnumber[i - 1].second; k--) 
                    dp[j][k] = max(dp[j][k], dp[j - bitnumber[i - 1].first][k - bitnumber[i - 1].second] + 1);                  

        return dp[m][n];
    }
};
```

要注意这里j, k是反向遍历的，正向遍历会出现重复计数的情况。

为什么反向遍历是可以的呢?

因为本来就是正向反向都可以。固定了i, j,k正向还是反向道理是一样的。但是正向会重复计数。


