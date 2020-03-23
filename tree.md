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





