# 120. Triangle

Given a `triangle` array, return *the minimum path sum from top to bottom*.

For each step, you may move to an adjacent number of the row below. More formally, if you are on index `i` on the current row, you may move to either index `i` or index `i + 1` on the next row.

 

**Example 1:**

```
Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
Output: 11
Explanation: The triangle looks like:
   2
  3 4
 6 5 7
4 1 8 3
The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).
```

**Example 2:**

```
Input: triangle = [[-10]]
Output: -10
```

 

**Constraints:**

- `1 <= triangle.length <= 200`
- `triangle[0].length == 1`
- `triangle[i].length == triangle[i - 1].length + 1`
- `-104 <= triangle[i][j] <= 104`

 

**Follow up:** Could you do this using only `O(n)` extra space, where `n` is the total number of rows in the triangle?



## Solution1

我一开始想到的就是dfs.

很遗憾，超时了，此路不通

```cpp
class Solution {
public:
    
    int minsum = 0x3fffffff;
    
    void dfs(vector<vector<int>>& triangle, int level, int pos, int sum) {
        if(level == triangle.size()) {
            if(sum < minsum) minsum = sum;
            return ;
        }
        dfs(triangle, level + 1, pos, sum + triangle[level][pos]);
        dfs(triangle, level + 1, pos + 1, sum + triangle[level][pos]);
    }
    
    int minimumTotal(vector<vector<int>>& triangle) {
        dfs(triangle, 0, 0, 0);
        return minsum;
    }
};
```



## Solution2

dp

注意要从下往上dp

```cpp
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        
        for(int i = n - 2; i >= 0; i--) {
            for(int j = 0; j <= i; j++) {
                triangle[i][j] += min(triangle[i + 1][j], triangle[i + 1][j + 1]);
            }
        }
        return triangle[0][0];
    }
};
```

