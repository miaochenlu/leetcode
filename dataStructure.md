# 链表

## 1. 创建链表

```cpp
#include<cstdio>
#include<cstdlib>

struct node {
    int data;
    node* next;
};

node* create(int Array[]) {
    node* p, *pre, *head;
    head = new node;
    head->next = NULL;
    pre = head;
    
    for(int i = 0; i < 5; i++) {
        p = new node;
        p->data = Array[i];
        p->next = NULL;
        pre->next = p;
        pre = p;
    }
    return head;
}

int main() {
    int Array[5] = {5, 3, 6, 1, 2};
    node* L = create(Array);
    L = L->next;
    while(L != NULL) {
        printf("%d", L->data);
        L = L->next;
    }
}
```

## 2. 查找元素

```cpp
int search(node* head, int x) {
    int count = 0;
    node* p = head->next;
    whwile(p != NULL) {
        if(p->data == x) {
            count++;
        }
        p = p->next;
    }
    return count;
}
```



## 3. 插入元素

```cpp
void insert(node* head, int pos, int x) {
    node* p = head;
    for(int i = 0; i < pos - 1; i++) {
        p = p->next;
    }
    node* q = new node;
    q->data = x;
    q->next = p->next;
    p->next = q;
}
```

## 4. 删除元素

```cpp
void del(node* head, int x) {
    node* p = head->next;
    node* pre = head;
    while(p != NULL) {
        if(p->data == x) {
            pre->next = p->next;
            delete p;
            p = pre->next;
        } else {
            pre = p;
            p = p->next;
        }
    }
}
```



## 静态链表的使用

* 定义静态链表

```cpp
struct Node {
  int address;		//节点地址
  typename data;	//数据域
  int next;			//指针域
  XXX;				//节点的某个性质，不同题目会有不同的设置, 如flag
} node[100010];
```

* 在程序的开始，对静态链表进行***初始化***。一般需要对定义中的XXX进行初始化，将其定义为正常情况下达不到的数字

```cpp
for(int i = 0; i < maxn; i++) {
  node[i].XXX = 0;
}
```

* 题目一般会给出一条链表的首节点的地址，我们可以依据这个地址来遍历得到整条链表。需要注意的是，这一步同时需要对节点的性质XXX进行标记，并且对有效节点的个数进行计数的时候，例如对节点是否在链表上这个性质来说，我们遍历链表时，就可以把XXX置为1

```cpp
int p = begin, count = 0;
while(p != -1) {
  XXX = 1;
  count++;
  p = node[p]->next;
}
```

* 使用静态链表时，是直接采用hash的方式，这就会使得数组下标不连续，而很多时候题目给出的节点并不都是有效节点。为了能够可控地访问有效节点，一般都需要用对数组进行排序以把有效节点移到数组左端

```cpp
bool cmp(Node a, Node b) {
  if(a.XXX == -1 || b.XXX == -1) {
    //至少一个节点是无效节点，就把它放到数组后面
    return a.XXX > b.XXX
  } else {
    //第二级排序
  }
}
```

* 经历了上述步骤后，链表中的有效节点就都在数组左端了，且已经按照节点的性质进行了排序。接下来就要看题目在排序之后具体要求做什么了

