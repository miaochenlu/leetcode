# 696. Count Binary Substrings

Give a string `s`, count the number of non-empty (contiguous) substrings that have the same number of 0's and 1's, and all the 0's and all the 1's in these substrings are grouped consecutively.

Substrings that occur multiple times are counted the number of times they occur.

**Example 1:**

```
Input: "00110011"
Output: 6
Explanation: There are 6 substrings that have equal number of consecutive 1's and 0's: "0011", "01", "1100", "10", "0011", and "01".
Notice that some of these substrings repeat and are counted the number of times they occur.
Also, "00110011" is not a valid substring because all the 0's (and 1's) are not grouped together.
```



**Example 2:**

```
Input: "10101"
Output: 4
Explanation: There are 4 substrings: "10", "01", "10", "01" that have equal number of consecutive 1's and 0's.
```



**Note:**

`s.length` will be between 1 and 50,000.

`s` will only consist of "0" or "1" characters.



# Solution

<a href="https://leetcode.com/problems/count-binary-substrings/discuss/1172569/Short-and-Easy-w-Explanation-and-Comments-or-Keeping-Consecutive-0s-and-1s-Count-or-Beats-100"> reference Solution</a>



✔️ ***Solution - I (Maintain Count of current & previous consecutive characters & Add minimum)***

The problem can be solved by observing the examples carefully -

```
1. 0011
In this string, consecutive count of binary characters are [2, 2]. We can form a total of 2 substrings.

2. 00011
In this string, consecutive count of binary characters are [3, 2]. Still, we can only form 2 substrings.

3. 000111
Here, consecutive count of binary characters are as - [3,3]. Now, we can form 3 substrings.

4. 00011100
Consecutive count of binary characters are - [3,3,2]. We can form 3 substrings with the first 2 groups of zeros and ones. 
Then we can form 2 substrings with the latter 2 groups. So, a total of 5 substrings.

5. 00011100111
Consecutive count - [3,3,2,3]. Substrings formed - 3 + 2 + 2 = 7
```

We can observe from the above examples that our final count will only depend on the consecutive counts of binary characters. **With each two groups of consecutive characters, the number of substrings that can be formed will be minimum of count among the two groups**.



Now, although we could maintain all the groupings and their counts and then count the number of substrings, we actually don't even need to maintain the consecutive counts in all of the string. We can **just store the current consecutive count and previous consecutive count** and count the substrings on the fly.



1. **`s[i] == s[i - 1]`** : When current character is equal to previous - just increment the current consecutive count.
2. **`s[i] != s[i - 1]`** :Whenever current character is not equal to previous - We know that we atleast have group of 2 different characters having `consecutiveCount >= 1`. The number of substrings that can be formed from these would be equal to minimum of *`currentConsecutiveCount`* & *`prevConsecutiveCount`*.
   So just add that amount to `ans`. Now *`prevConsecutiveCount`* will become equal to *`currentConsecutiveCount`* and reset the *`currentConsecutiveCount`* to 1.



```cpp
class Solution {
public:
    int countBinarySubstrings(string s) {
        int n = s.size();
        int cur = 1, pre = 0;
        int ans = 0;
        for(int i = 1; i < n; i++) {
            if(s[i] == s[i - 1])
                cur++;
            else {
                ans += min(cur, pre);
                pre = cur;
                cur = 1;
            }
        }
        ans += min(cur, pre);
        return ans;
    }
};
```

