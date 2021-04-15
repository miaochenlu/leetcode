# 1. 二叉树的存储结构与基本操作

## A. 二叉树的存储结构

```cpp
struct node {
  typename data;
  node* left;
  node* right;
};
```

由于二叉树建树前根节点不存在，因此其一般地址设为NULL

```cpp
node* root = NULL;
```

如果需要新建节点

```cpp
node* newNode(int v) {
  node* Node = new node;
  Node->data = v;
  Node->left = Node->right = NULL;
  return Node;
}
```





## B. 二叉树节点的插入

```cpp
void insert(node* &root, int x) {
  if(root == NULL) {
    root = newNode(x);
    return;
  }
  if(x < root->val) {
    insert(root->left, x);
  } else {
    insert(root->right, x);
  }
}
```

根节点指针root使用了引用&。因此，在函数中修改root会直接修改原变量。

一般来说，如果函数中需要新建节点，即对二叉树的结构做出修改，就需要加引用；如果只是修改当前已有节点的内容，或者仅仅是遍历树，就不需要加引用。

在新建节点后，务必使新节点的左右指针域为NULL，表示这个新节点暂时没有左右子树。

## C. 二叉树的创建

二叉树的创建其实就是二叉树节点的插入过程，而插入过程所需要的节点数据域一般会由题目给出，因此常用的写法是：

> 把需要插入的数据存储在数组中，然后再将它们使用insert函数一个个插入二叉树中，并最终返回根节点的指针root。
>
> 更方便的写法是直接在建立二叉树的过程中边输入数据边插入节点

```cpp
node* Create(int data[], int n) {
  Node* root = NULL;
  for(int i = 0; i < n; i++) {
    insert(root, data[i]);
  }
  return root;
}
```



# 2. 二叉树的遍历

## A. 先序遍历

```cpp
void preorder(node* root) {
  if(root == NULL)
    return;
  printf("%d\n", root->data);
  preorder(root->left);
  preorder(root->right);
}
```

## B. 中序遍历

```cpp
void inorder(node* root) {
  if(root->NULL)
    return;
  preorder(root->left);
  printf("%d\n", root->data);
  preorder(root->right);
}
```

## C. 后序遍历

```cpp
void postorder(node* root) {
  if(root->NULL)
    return;
  postorder(root->left);
  postorder(root->right);
  printf("%d\n", root->data);
}
```



## D. 层序遍历

```cpp
void layerorder(node* root) {
  queue<node*> q;
  q.push(root);
  while(q.size()) {
    node* top = q.front(); q.pop();
    printf("%d\n", top->val);
    if(top->left) q.push(top->left);
    if(top->right) q.push(top->right);
  }
}
```



# 3. 一类重要问题

给定一棵二叉树的先序遍历序列和中序遍历序列，重建这棵二叉树

```cpp
node* Create(int preL, int preR, int inL, int inR) {
  if(preL > preR)
    return NULL;

  node* root = new node;
  root->data = pre[preL];
  
  int k = 0;
  for(k = inL; k <= inR; k++) {
    //在中序遍历中找到in[k]=pre[preL]的节点
    if(in[k] == pre[preL])
      break;
  }
  //左子树的节点个数
  int numLeft = k - inL;
  
  root->left = Create(preL + 1, preL + numLeft, inL, k - 1);
  root->right = Create(preL + numLeft + 1, k + 1, inR);
  return root;
}
```



example

1020 Tree Traversals (25分)

Suppose that all the keys in a binary tree are distinct positive integers. Given the postorder and inorder traversal sequences, you are supposed to output the level order traversal sequence of the corresponding binary tree.

Input Specification:

Each input file contains one test case. For each case, the first line gives a positive integer *N* (≤30), the total number of nodes in the binary tree. The second line gives the postorder sequence and the third line gives the inorder sequence. All the numbers in a line are separated by a space.

Output Specification:

For each test case, print in one line the level order traversal sequence of the corresponding binary tree. All the numbers in a line must be separated by exactly one space, and there must be no extra space at the end of the line.

Sample Input:

```in
7
2 3 1 5 7 6 4
1 2 3 4 5 6 7   
```

Sample Output:

```out
4 1 6 3 5 7 2
```

```cpp
#include<cstdio>
#include<queue>
using namespace std;
const int maxn = 50;
int in[maxn];
int post[maxn];
int n;
struct node {
  int data;
  node* left;
  node* right;
};

node* Create(int postL, int postR, int inL, int inR) {
  if(postL > postR)
    return NULL;
  node* root = new node;
  root->data = post[postR];
  int k = 0;
  for(k = inL; k <= inR; k++) {
    if(in[k] == post[postR])
      break;
  }
  int numLeft = k - inL;
  root->left = Create(postL, postL + numLeft - 1, inL, k - 1);
  root->right = Create(postL + numLeft, postR - 1, k + 1, inR);
  return root;
}

void levelorder(node* root) {
  queue<node*> q;
  q.push(root);
  int printCount = 0;
  while(q.size()) {
    node* tmp = q.front(); q.pop();
    printCount++;
		if(printCount != n)
	    printf("%d ", tmp->data);
    else printf("%d", tmp->data);
    if(tmp->left) q.push(tmp->left);
    if(tmp->right) q.push(tmp->right);
  }
}
int main() {
  scanf("%d", &n);
  for(int i = 0; i < n; i++) scanf("%d", &post[i]);
  for(int i = 0; i < n; i++) scanf("%d", &in[i]);
  node* root = Create(0, n - 1, 0, n - 1);
  levelorder(root);
}
```

# 3. 树的遍历

### A. 树的静态写法

这里讨论的树是指一般意义上的树，即子节点个数不限且子节点没有先后顺序的树，而不是二叉树。

```cpp
struct node {
  typename data;		//数据域
  int child[maxn];	//指针域，存放所有子节点的下标
} Node[maxn];				//节点数组，maxn为节点上限个数
```

在上面的定义中，由于无法预知子节点个数，因此child数组的长度只能开到最大，而这对一些节点个数较多的题目来说是不可接受的，因此，这里可以使用STL中的vector

```cpp
struct node {
  typename data;
  vector child;
} Node[maxn];
```

与二叉树的静态实现类似，当需要新建一个节点时，就按顺序才能够数组中取出一个下标即可

```cpp
int index = 0;
int newNode(int v) {
  Node[index].data = v;				//数据域为v
  Node[index].child.clear();	//清空子节点
  return index++;							//返回节点下标，并令index自增
}
```



### B. 树的先根遍历

```cpp
void PreOrder(int root) {
  printf("%d ", Node[root].data);//访问当前节点
  for(int i = 0; i < Node[root].child.size(); i++) {
    PreOrder(Node[root].child[i]);//递归访问节点root的所有子节点
  }
}
```

### C. 树的层序遍历

```cpp
void LayerOrder(int root) {
  queue<int> q;
  q.push(root);
  while(q.size()) {
    int top = q.front(); q.pop();
    printf("%d ", Node[top].data);
    for(int i = 0; i < Node[top].child.size(); i++) 
      q.push(Node[top].child[i]);
	}
}
```

如果要对节点的层号进行求解，只需要在结构体node的定义中增加变量来记录节点的层号

```cpp
struct node {
  int layer;//记录层号
  int data;
  vector<int> child;
}
```

```cpp
void LayerOrder(int root) {
  queue<int> q;
  q.push(root);
  Node[root].layer = 0;
  while(q.size()) {
    int top = q.front(); q.pop();
    printf("%d ", Node[top].data);
    for(int i = 0; i < Node[top].child.size(); i++) {
      int child = Node[top].child[i];
      Node[child].layer = Node[front].layer + 1;
      q.push(child);
    }
  }
}
```



### D. 从树的遍历看DFS与BFS

DFS-->先序遍历

碰到一些可以用DFS做的题目，不妨把一些状态作为树的节点，然后问题就会转换为直观的对树进行先序遍历的问题。如果要得到树的某些信息，也可以借用DFS以深度作为第一关键词来对节点进行遍历，以获得所需的结果。

BFS-->层序遍历

#### 1053 Path of Equal Weight (30分)

Given a non-empty tree with root *R*, and with weight *Wi* assigned to each tree node *Ti*. The **weight of a path from *R* to *L*** is defined to be the sum of the weights of all the nodes along the path from *R* to any leaf node *L*.

Now given any weighted tree, you are supposed to find all the paths with their weights equal to a given number. For example, let's consider the tree showed in the following figure: for each node, the upper number is the node ID which is a two-digit number, and the lower number is the weight of that node. Suppose that the given number is 24, then there exists 4 different paths which have the same given weight: {10 5 2 7}, {10 4 10}, {10 3 3 6 2} and {10 3 3 6 2}, which correspond to the red edges in the figure.

<img src="img/212.png" alt="img" style="zoom:50%;" />

Input Specification:

Each input file contains one test case. Each case starts with a line containing 0<*N*≤100, the number of nodes in a tree, *M* (<*N*), the number of non-leaf nodes, and 0<*S*<230, the given weight number. The next line contains *N* positive numbers where *W**i* (<1000) corresponds to the tree node *T**i*. Then *M* lines follow, each in the format:

```
ID K ID[1] ID[2] ... ID[K]
```

where `ID` is a two-digit number representing a given non-leaf node, `K` is the number of its children, followed by a sequence of two-digit `ID`'s of its children. For the sake of simplicity, let us fix the root ID to be `00`.

Output Specification:

For each test case, print all the paths with weight S in **non-increasing** order. Each path occupies a line with printed weights from the root to the leaf in order. All the numbers must be separated by a space with no extra space at the end of the line.

Note: sequence {*A*1,*A*2,⋯,*A**n*} is said to be **greater than** sequence {*B*1,*B*2,⋯,*B**m*}if there exists 1≤*k*<*m**i**n*{*n*,*m*} such that *A**i*=*B**i* for *i*=1,⋯,*k*, and *Ak*+1>*B*k+1.

Sample Input:

```in
20 9 24
10 2 4 3 5 10 2 18 9 7 2 2 1 3 12 1 8 6 2 2
00 4 01 02 03 04
02 1 05
04 2 06 07
03 3 11 12 13
06 1 09
07 2 08 10
16 1 15
13 3 14 16 17
17 2 18 19
```

Sample Output:

```out
10 5 2 7
10 4 10
10 3 3 6 2
10 3 3 6 2
```

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
const int maxn = 100000;
struct node {
    int weight;
    vector<int> child;
} Node[maxn];
int N, M, S;

bool cmp(int a, int b) {
    return Node[a].weight > Node[b].weight;
}
int res[maxn];
void DFS(int root, int numNode, int sum) {
    if(sum > S) return;
    if(sum == S) {
        if(Node[root].child.size()) return;
        int j = 0;
        for(; j < numNode - 1; j++) {
            printf("%d ", Node[res[j]].weight);
        }
        printf("%d\n", Node[res[j]].weight);
        return;
    }
    for(int i = 0; i < Node[root].child.size(); i++) {
        int child = Node[root].child[i];
        res[numNode] = child;
        DFS(child, numNode + 1, sum + Node[child].weight);
    }
}
int main() {
    scanf("%d%d%d", &N, &M, &S);
    for(int i = 0; i < N; i++) {
        scanf("%d", &Node[i].weight);
    }

    for(int i = 0; i < M; i++) {
        int id;
        int k;
        scanf("%d", &id);
        scanf("%d", &k);
        for(int j = 0; j < k; j++) {
            int childId;
            scanf("%d", &childId);
            Node[id].child.push_back(childId);
        }
        sort(Node[id].child.begin(), Node[id].child.end(), cmp);
    }
    res[0] = 0;
    DFS(0, 1, Node[0].weight);

}

```



# 4. 二叉查找树(BST)

### A. 查找操作

```cpp
void search(node* root, int x) {
  if(root == NULL) {
    printf("search failed\n");
    return;
  }
  if(x == root->data) {
    printf("%d\n", root->data);
  } else if(x < root->data) {
    search(root->left, x);
  } else {
    search(root->right, x);
  }
}
```

### B. 插入操作

```cpp
//insert要在二叉树中插入一个数据域为x的新节点(注意参数root要加引用&)
void insert(node* &root, int x) {
  if(root == NULL) {
    root = newNode(x);
    return;
  }
  if(x == root->data) {
    return;
  } else if(x < root->data) {
    insert(root->left, x);
  } else {
    insert(root->right, x);
  }
}
```

### C. 二叉查找树的建立

```cpp
node* Create(int data[], int n) {
  node* root = NULL;
  for(int i = 0; i < n; i++) {
    insert(root, data[i]);
  }
  return root;
}
```

### D. 二叉查找树的删除

```cpp
node* findMax(node* root) {
  while(root->right != NULL)
    root = root->right;
  return root;
}

node* findMin(node* root) {
  while(root->left != NULL)
    root = root->left;
  return root;
}
```

```cpp
void deleteNode(node* &root, int x) {
  if(root == NULL)
    return;
  if(root->data == x) {
    if(root->left == NULL && root->right == NULL) {
      root = NULL;
      return;
    } else if(root->left) {
      node* pre = findMax(root->left);
      root->data = pre->data;
      deleteNode(root->left, pre->data);
    } else {
      node* next = findMin(root->right);
      root->data = next->data;
      deleteNode(root->right, next->data);
    }
  } else if(root->data > x) {
    deleteNode(root->left, x);
  } else {
    deleteNode(root->right, x);
  }
}
```







#### 1043 Is It a Binary Search Tree (25分)

A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:

- The left subtree of a node contains only nodes with keys less than the node's key.
- The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
- Both the left and right subtrees must also be binary search trees.

If we swap the left and right subtrees of every node, then the resulting tree is called the **Mirror Image** of a BST.

Now given a sequence of integer keys, you are supposed to tell if it is the preorder traversal sequence of a BST or the mirror image of a BST.

Input Specification:

Each input file contains one test case. For each case, the first line contains a positive integer *N* (≤1000). Then *N*integer keys are given in the next line. All the numbers in a line are separated by a space.

Output Specification:

For each test case, first print in a line `YES` if the sequence is the preorder traversal sequence of a BST or the mirror image of a BST, or `NO` if not. Then if the answer is `YES`, print in the next line the postorder traversal sequence of that tree. All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.

Sample Input 1:

```in
7
8 6 5 7 10 8 11
```

Sample Output 1:

```out
YES
5 7 6 8 11 10 8
```

Sample Input 2:

```in
7
8 10 11 8 6 7 5 
```

Sample Output 2:

```out
YES
11 8 10 7 5 6 8
```

Sample Input 3:

```in
7
8 6 8 5 10 9 11
```

Sample Output 3:

```out
NO
```

```cpp
#include<cstdio>
#include<vector>
using namespace std;

struct node {
    int data;
    node* left;
    node* right;
};

int n;
vector<int> original;

void insert(node* &root, int x) {
    if(root == NULL) {
        root = new node;
        root->data = x;
        root->left = root->right = NULL;
        return;
    } else if(root->data > x) {
        insert(root->left, x);
    } else {
        insert(root->right, x);
    }
}
vector<int> pre, preMirror;
vector<int> post, postMirror;
void preOrder(node* root) {
    if(root == NULL) return;
    pre.push_back(root->data);
    if(root->left) preOrder(root->left);
    if(root->right) preOrder(root->right);
}
void preOrderMirror(node* root) {
    if(root == NULL) return;
    preMirror.push_back(root->data);
    if(root->right) preOrderMirror(root->right);
    if(root->left) preOrderMirror(root->left);
}
void postOrder(node* root) {
    if(root == NULL) return;
    if(root->left) postOrder(root->left);
    if(root->right) postOrder(root->right);
    post.push_back(root->data);
}
void postOrderMirror(node* root) {
    if(root == NULL) return;
    if(root->right) postOrderMirror(root->right);
    if(root->left) postOrderMirror(root->left);
    postMirror.push_back(root->data);
}
int main() {
    scanf("%d", &n);
    node* root = NULL;
    for(int i = 0; i < n; i++) {
        int data;
        scanf("%d", &data);
        original.push_back(data);
        insert(root, data);
    }
    preOrder(root);
    preOrderMirror(root);
    postOrder(root);
    postOrderMirror(root);
    // printf("size: %d\n", pre.size());
    // for(int i = 0; i < pre.size(); i++) {
    //     printf("%d %d\n", pre[i], original[i]);
    // }
    if(original == pre) {
        printf("YES\n");
        for(int i = 0; i < post.size(); i++) {
            printf("%d", post[i]);
            if(i < post.size() - 1) printf(" ");
        }
    } else if(original == preMirror) {
        printf("YES\n");
        for(int i = 0; i < postMirror.size(); i++) {
            printf("%d", postMirror[i]);
            if(i < post.size() - 1) printf(" ");
        }
    } else {
        printf("NO\n");
    }

}
```

