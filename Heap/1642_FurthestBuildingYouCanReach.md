# 1642. Furthest Building You Can Reach

You are given an integer array `heights` representing the heights of buildings, some `bricks`, and some `ladders`.

You start your journey from building `0` and move to the next building by possibly using bricks or ladders.

While moving from building `i` to building `i+1` (**0-indexed**),

- If the current building's height is **greater than or equal** to the next building's height, you do **not** need a ladder or bricks.
- If the current building's height is **less than** the next building's height, you can either use **one ladder** or `(h[i+1] - h[i])` **bricks**.

*Return the furthest building index (0-indexed) you can reach if you use the given ladders and bricks optimally.*

 

**Example 1:**

![img](../img/4.gif)



```
Input: heights = [4,2,7,6,9,14,12], bricks = 5, ladders = 1
Output: 4
Explanation: Starting at building 0, you can follow these steps:
- Go to building 1 without using ladders nor bricks since 4 >= 2.
- Go to building 2 using 5 bricks. You must use either bricks or ladders because 2 < 7.
- Go to building 3 without using ladders nor bricks since 7 >= 6.
- Go to building 4 using your only ladder. You must use either bricks or ladders because 6 < 9.
It is impossible to go beyond building 4 because you do not have any more bricks or ladders.
```

**Example 2:**

```
Input: heights = [4,12,2,7,3,18,20,3,19], bricks = 10, ladders = 2
Output: 7
```

**Example 3:**

```
Input: heights = [14,3,19,3], bricks = 17, ladders = 0
Output: 3
```

 

**Constraints:**

- `1 <= heights.length <= 105`
- `1 <= heights[i] <= 106`
- `0 <= bricks <= 109`
- `0 <= ladders <= heights.length`

```
Input: heights = [4,2,7,6,9,14,12], bricks = 5, ladders = 1
Output: 4
Explanation: Starting at building 0, you can follow these steps:
- Go to building 1 without using ladders nor bricks since 4 >= 2.
- Go to building 2 using 5 bricks. You must use either bricks or ladders because 2 < 7.
- Go to building 3 without using ladders nor bricks since 7 >= 6.
- Go to building 4 using your only ladder. You must use either bricks or ladders because 6 < 9.
It is impossible to go beyond building 4 because you do not have any more bricks or ladders.
```

**Example 2:**

```
Input: heights = [4,12,2,7,3,18,20,3,19], bricks = 10, ladders = 2
Output: 7
```

**Example 3:**

```
Input: heights = [14,3,19,3], bricks = 17, ladders = 0
Output: 3
```

 

**Constraints:**

- `1 <= heights.length <= 105`
- `1 <= heights[i] <= 106`
- `0 <= bricks <= 109`
- `0 <= ladders <= heights.length`





## Naive Solution--TLE

想到了用dfs来做，但是明显是会超时的

```cpp
class Solution {
public:
    
    void dfs(vector<int>& heights, int buildingID, int& maxID, int rmbricks, int rmladders) {   
        if(buildingID - 1 > maxID) maxID = buildingID - 1;
        if(buildingID  == heights.size()) return;
        if(heights[buildingID - 1] >= heights[buildingID]) dfs(heights, buildingID + 1, maxID, rmbricks, rmladders);
        else {
            if(rmbricks - (heights[buildingID] - heights[buildingID - 1]) < 0 && rmladders <= 0)
                return;
            if(rmbricks - (heights[buildingID] - heights[buildingID - 1]) >= 0)
                dfs(heights, buildingID + 1, maxID, rmbricks - (heights[buildingID] - heights[buildingID - 1]), rmladders);
            if(rmladders > 0)
                dfs(heights, buildingID + 1, maxID, rmbricks, rmladders - 1);
        }
    }
    
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        int maxID = 0;
        dfs(heights, 1, maxID, bricks, ladders);
        return maxID;
    }
};
```



## Solution

Heap `heap` store k height difference that we need to use ladders.
Each move, if the height difference `d > 0`,
we push `d` into the priority queue `pq`.
If the size of queue exceed `ladders`,
it means we have to use bricks for one move.
Then we pop out the smallest difference, and reduce `bricks`.
If `bricks < 0`, we can't make this move, then we return current index `i`.
If we can reach the last building, we return `A.length - 1`.



Time `O(NlogK)`
Space `O(K)`

```cpp
class Solution {
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        priority_queue<int> pq;
        for(int i = 0; i < heights.size() - 1; i++) {
            int d = heights[i + 1] - heights[i];
            if(d > 0) {
                pq.push(-d);
                
                if(pq.size() > ladders) {
                    bricks += pq.top();
                    pq.pop();
                }
                
                if(bricks < 0) return i;
            }
        }
        return heights.size() - 1;
    }
};
```



## 附

<a href="https://blog.csdn.net/lym940928/article/details/89635690?utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-1.control&dist_request_id=1332048.20389.16195070051370563&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-1.control">priority queue</a>

