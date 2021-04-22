# 32. Longest Valid Parentheses

- [x] 2020.04.22 Review



Given a string containing just the characters `'('` and `')'`, find the length of the longest valid (well-formed) parentheses substring.

**Example 1:**

```
Input: s = "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()".
```

**Example 2:**

```
Input: s = ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()".
```

**Example 3:**

```
Input: s = ""
Output: 0
```

 

**Constraints:**

- `0 <= s.length <= 3 * 104`
- `s[i]` is `'('`, or `')'`.



## Solution1

Using stack

有点巧妙。我一开始stack里面放的是character, 这里放的是Index

https://leetcode.com/problems/longest-valid-parentheses/solution/

```cpp
class Solution {
public:
    int longestValidParentheses(string s) {
        vector<int> st;
        st.push_back(-1);
        int maxAns = 0;
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == '(') st.push_back(i);
            else {
                st.pop_back();
                if(st.empty()) 
                    st.push_back(i);
                else 
                    maxAns = max(maxAns, i - st.back());
            }
        }
        return maxAns;
    }
};
```

