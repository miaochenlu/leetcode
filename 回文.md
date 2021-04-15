# 1. Palindrome Linked List

Given the `head` of a singly linked list, return `true` if it is a palindrome.

 

**Example 1:**

![img](C:\Users\Dell 7080\Desktop\all\leetcode\img\pal1linked-list.jpg)

```
Input: head = [1,2,2,1]
Output: true
```

**Example 2:**

![img](C:\Users\Dell 7080\Desktop\all\leetcode\img\pal2linked-list.jpg)

```
Input: head = [1,2]
Output: false
```

 

**Constraints:**

- The number of nodes in the list is in the range `[1, 105]`.
- `0 <= Node.val <= 9`

 

**Follow up:** Could you do it in `O(n)` time and `O(1)` space?



## Solution

处理数组中的回文问题时，我们一般利用双指针，从两端指向中间，或者从中间指向两端。

然而，在单向链表中，我们做不到向前遍历。

解决方法是：反转一半的链表，然后一个指向从未反转的开头，一个指向反转的开头，比较指针指向的元素是否相同。



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
    bool isPalindrome(ListNode* head) {
//fast, slow指针找到链表中点        
        ListNode* fast = head, *slow = head;
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        if(fast) slow = slow->next;
        
        slow = reverse(slow);
        
        ListNode* front = head;
        while(slow) {
            if(front->val != slow->val) return false;
            slow = slow->next;
            front = front->next;
        }
        return true;
        
    }
    
    ListNode* reverse(ListNode* head) {
        ListNode* cur = head, *pre = NULL;
        
        while(cur) {
            ListNode* next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    }
};
```



# 2. 最长回文子序列











# 3. 回文序列的数量