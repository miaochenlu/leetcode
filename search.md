# DFS

如下图迷宫，要走出这个迷宫，可以选择的一种方法是：

以当前所在位置为起点，沿着一条路走，当碰到岔道口时，选择其中一个岔道前进。如果选择的岔路前方是一条死路，就退回到这个岔道口，选择另一条岔路。

**深度优先搜索时一种枚举所有完整路径以遍历所有情况的搜索方法**

<img src="/Users/jones/Library/Application Support/typora-user-images/image-20200313204850036.png" alt="image-20200313204850036" style="zoom:50%;" />、

DFS和入栈出栈的过程很相似，因此可以用栈来实现

从DFS的角度来看秋季Fibonacci数列的过程

$$F(0)=0, F(1)=1,F(n)=F(n-1)+F(n-2)\;n\geq2$$

每当F(n)非为F(n-1)和F(n-2)时，就可以把F(n)看作迷宫的岔道口，他可以到达两个新的关键点F(n-1)和F(n-2)。而之后计算F(n-1)时，又可以把F(n-1)当作在岔道口F(n)之下的岔道口。F(0),F(1)就是死胡同

因此递归也可以很好的实现深度优先搜索





例子：

有n件物品，每件物品的重量为w[i],价值为c[i]。现在需要选出若干件物品放入一个容量为V的背包中，使得在选入背包的物品重量不超过容量V的前提下，让背包中物品的价值之和最大，求最大价值$(1\leq n\leq 20)$

```cpp
const int maxn = 30;
int c, V, maxValue = 0;
int w[maxn], c[maxn];

void DFS(int index, int sumW, int sumC) {
  if(index == n) { //已经完成对n件物品的选择
    if(sumW <= V && sumC > maxValue) {
      maxValue = sumC;
    }
    return;
  }
  DFS(index + 1, sumW, sumC);
  DFS(index + 1, sumW + w[index], sumC + c[index]);
}
```

改进

```cpp
void DFS(int index, int sumW, int sumC) {
  if(index == n) return;
  DFS(index + 1, sumW, sumC);
  
  if(sumW + w[index] <= V) {
		if(sumC + c[index] > maxValue) {
      maxValue = sumC + c[index];
    }
    DFS(index + 1, sumW + w[index], sumC + c[index]);
  }
}
```



例子：

给定N个整数(有负数)，从中选择k个数，使得这k个数之和恰好等于一个给定的整数x; 如果有多种方案，选择她们中元素平方和最大的一个。

```cpp
int n, k, x, maxSumSqu = -1, A[maxn];
vector<int> temp, ans;	//	temp存放临时方案，ans存放平方和最大的方案

void DFS(int index, int nowK, int sum, int sumSqu) {
  if(nowK == k && sum == x) {
    if(sumSqu > maxSumSqu) {
      maxSumSqu = sumSqu;
      ans = temp;
    }
    return;
  }
  if(index == n || nowK > k || sum > x) return;
  temp.push_back(A[index]);
  DFS(index + 1, nowK + 1, sum + A[index], sumSqu + A[index] * A[index]);
  temp.pop_back();
  DFS(index + 1, nowK, sum, sumSqu);
}
```



# 广度优先搜索(BFS)

<img src="/Users/jones/Library/Application Support/typora-user-images/image-20200314141428486.png" alt="image-20200314141428486" style="zoom:50%;" />



BFS一般用队列实现

```cpp
void BFS(int s) {
  queue<int> q;
  q.push(s);
  while(!q.empty()) {
    取出队首元素top;
    访问队首元素top;
    将队首元素出队;
    将top的下一层结点中未曾入队的结点全部入对，并设置为已入队;
  }
}
```



例子：

<img src="/Users/jones/Library/Application Support/typora-user-images/image-20200314142622170.png" alt="image-20200314142622170" style="zoom:50%;" />

```cpp
#include<cstdio>
#include<queue>
using namespace std;
const int maxn = 100;
struct node {
  int x, y;
}Node;

int n, m;
int matrix[maxn][maxn];	//01矩阵
bool inq[maxn][maxn] = {false}; //记录位置(x,y)是否入过队
int X[4] = {0, 0, 1, -1};
int Y[4] = {1, -1, 0, 0};

bool judge(int x, int y) {
  //越界返回false
  if(x >= n || x < 0 || y >= m || y < 0) return false;
  //当前位置为0，或(x,y)入过队，返回false
  if(matrix[x][y] == 0 || inq[x][y] == true) return false;
  return false;
}

void BFS(int x, int y) {
  queue<node> Q;
  Node.x = x, Node.y = y;
  Q.push(Node);
  inq[x][y] = true;
  while(!Q.empty()) {
    node top = Q.front();
    Q.pop();
    for(int i = 0; i < 4; i++) {
      int newX = top.x + X[i];
      int newY = top.y + Y[i];
      if(judge(newX, newY)) {
        Node.x = newX, Node.y = newY;
        Q.push(Node);
        inq[newX][newY] = true;
      }
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for(int x = 0; x < n; x++) {
    for(int y = 0; y < m; y++) {
      scanf("%d", &matrix[x][y]);
    }
  }
  
  int ans = 0;
  for(int x = 0; x < n; x++) {
    for(int y = 0; y < m; y++) {
      if(matrix[x][y] == 1 && inq[x][y] == false) {
        ans++;
        BFS(x, y);
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}
```



```cpp
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int maxn = 100;
struct node {
  int x, y;
  int step;
}S, T, Node;

int n, m;
char maze[maxn][maxn];
bool inq[maxn][maxn] = {false};
int X[4] = {0, 0, 1, -1};
int Y[4] = {1, -1, 0, 0};

bool test(int x, int y) {
  if(x >= n || x < 0 || y >= m || y < 0) return false;
  if(maze[x][y] == '*') return false;
  if(inq[x][y] == true) return false;
  return true;
}

int BFS() {
  queue<node> q;
  q.push(S);
  while(!q.empty()) {
    node top = q.front();
    q.pop();
    if(top.x == T.x && top.y == T.y) {
      return top.step;
    }
    for(int i = 0; i < 4; i++) {
      int newX = top.x + X[i];
      int newY = top.y + Y[i];
      if(test(newX, newY)) {
        Node.x = newX, Node.y = newY;
        Node.step = top.step + 1;
        q.push(Node);
        inq[newX][newY] = true;
      }
    }
  }
  return -1;
}
```







```cpp
#include<cstdio>
#include<cstring>
#include<queue>
const int maxn = 100;
struct node {
  int x, y;
  int step;
} Node, S, T;


char maze[maxn][maxn];		//record the map
bool inq[maxn][maxn];			//record have inqueue or not
int X[4] = {0, 0, 1, -1};
int Y[4] = {1, -1, 0, 0};

int n, m;

bool test(int x, int y) {
  if(x < 0 || x >= n || y < 0 || y >= m)
    return false;
  if(maze[x][y] == '*') return false;
  if(inq[x][y] == true) return false;
  return true;
}

int BFS() {
  queue<Node> q;
  q.push(S);
  
  while(q.size()) {
    node tmp = q.front(); q.pop();
    if(tmp.x == T.x && tmp.y == T.y) {
      return tmp.step;
    }
    
    for(int i = 0; i < 4; i++) {
	    int NewX = tmp.x + X[i];
      int NewY = tmp.y + Y[i];
      if(test(NewX, NewY)) {
        Node.x = NewX;
        Node.y = NewY;
        Node.step = tmp.step + 1;
        q.push(Node);
        inq[NewX][NewY] = true;
      }
		}
  }
}

int main() {
  scanf("%d %d", n, m);
  for(int i = 0; i < n; i++) {
    getchar();
    for(int j = 0; j < m; j++) {
      maze[i][j] = getchar();
    }
    maze[i][m + 1] = 0;
  }
  scanf("%d%d%d%d", &S.x, &S.y, &T.x, &T.y);
  S.step = 0;
  printf("%d\n", BFS());
  return 0;
}
```

