# 19. Remove Nth Node From End of List

Given the `head` of a linked list, remove the `nth` node from the end of the list and return its head.

**Follow up:** Could you do this in one pass?

 

**Example 1:**

![img](C:\Users\Dell 7080\Desktop\all\leetcode\img\remove_ex1.jpg)

```
Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]
```

**Example 2:**

```
Input: head = [1], n = 1
Output: []
```

**Example 3:**

```
Input: head = [1,2], n = 1
Output: [1]
```

 

**Constraints:**

- The number of nodes in the list is `sz`.
- `1 <= sz <= 30`
- `0 <= Node.val <= 100`
- `1 <= n <= sz`



# Solution

用fast指针先找到从头往后数的第n个位置

然后一个slow指针从头往后

当fast到了末尾后，slow就是倒数第n个位置



这里要注意头结点被删除的情况，所以要增加一个dummy head

![Remove the nth element from a list](C:\Users\Dell 7080\Desktop\all\leetcode\img\19_Remove_nth_node_from_end_of_listB.png)

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode;
        dummy->next = head;
        
        ListNode* first = dummy;
        ListNode* second = dummy;
        
        for(int i = 1; i <= n + 1; i++)  
            first = first->next;
        while(first) {
            first = first->next;
            second = second->next;
        }
        second->next = second->next->next;
        return dummy->next;    
    }
};
```

