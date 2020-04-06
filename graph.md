# 图算法专题

# 1. 图的存储

### A. 邻接矩阵

<img src="img/image-20200401134050254.png" alt="image-20200401134050254" style="zoom:50%;" />

设图G(V,E)的顶点标号为0,1,...,N-1, 那么可以令二维数组G\[N][N]的两维分别表示图的顶点标号。

* G\[i][j]=1, 说明顶点i和顶点j之间有边
* G\[i][j]=0, 说明顶点i和顶点j之间不存在边

这个二维数组G\[][]被称为邻接矩阵。如果存在边权，可以令G\[i][j]存放边权，对不存在的边可以设边权为0，-1或者是一个很大的数。

注意：

虽然邻接矩阵比较好写，但是由于需要开一个二维数组，如果顶点数目太大，便可能会超过题目限制的内存。因此邻接矩阵只适用于顶点数目不太大(一般不超过1000)的题目



### B. 邻接表

设图G(V,E)的顶点编号为0,1,...,N-1, 每个顶点都可能有若干条出边，如果吧同一个顶点的所有出边放在一个列表中，那么N个顶点就会有N个列表（没有出边，则对应空表）。这N个列表被称为图G的邻接表，记为Adj[N], 其中Adj[i]存放顶点i的所有出边组成的列表，这样Adj[0], Adj[1], ..., Adj[N-1]就分别都是一个列表。

可以通过链表来实现

<img src="img/image-20200401140201419.png" alt="image-20200401140201419" style="zoom:50%;" />

可以用vector来实现

如果邻接表只存放每条边的终点编号，而不存放边权，则vector中的元素类型可以直接定义为int型：

```cpp
vector<int> Adj[N];
```

如果想添加一条从1号顶点到达3号顶点的有向边，只需要在Ajd[1]中添加终点编号3即可。。

```cpp
Adj[1].push_back(3);
```

<br>

如果需要同时存放终点编号和边权，可以建立结构体Node, 用来存放每条边的终点编号和边权

```cpp
struct Node {
  int v;	//边的终点编号
  int w;	//边权
};
```

这样vector邻接表中的元素类型就是Node型的

```cpp
vector<Node> Adj[N];
```

如果想要添加从1号到达3号顶点的有向边，边权为4，就可以定义一个Node型的临时变量temp

```cpp
Node temp;
temp.v = 3;
temp.w = 4;
Adj[1].push_back(tmp);
```

当然，更快的做法是定义结构体Node的构造函数

```cpp
struct Node {
  int v, w;
  Node(int _v, int _w): v(_v), w(_w) {}
}
```

这样就能不定义临时变量来实现加边操作

```cpp
Adj[1].push_back(Node(3, 4));
```



# 2. 图的遍历

### A. DFS遍历图

DFS的具体实现：

* 连通分量

在无向图中，如果两个顶点之间可以互相到达，那么就称这两个顶点连通。如果图G(V,E)的任意两个顶点都连通，则称图G为连通图；否则，称图G为非连通图，且称其中的极大连通子图为连通分量。

* 强连通分量

在有向图中，如果两个顶点可以各自通过一条有向路径到达另一个顶点，就称这两个顶点强连通。如果图G(V,E)的任意两个顶点都强连通，则称图G为强连通图；否则， 称图G为非强连通图，且称其中的极大强连通子图为强连通分量。

<img src="/Users/jones/Library/Application Support/typora-user-images/image-20200401145227860.png" alt="image-20200401145227860" style="zoom:50%;" />

如果想要遍历整个图，就需要对所有连通快分别进行遍历。所以DFS遍历图的基本思路就是将经过的顶点设置为已访问，在下次递归碰到这个顶点时就不再去处理，直到整个图的顶点都被标记为已访问。

伪代码版本

```cpp
DFS(u) {//访问顶点u
  vis[u] = true;	//顶点u已被访问
  for(从u出发能到达的所有顶点v)	//枚举从u出发可以到达的所有顶点v
    if(vis[v] == false)//如果v没有被访问过
      DFS(v);	//递归访问v
}
DFSTrave(G) {	//遍历图G
  for(G的所有顶点u)
    if(vis[u] == false)
      DFS[u];
}
```

<br>

```cpp
const int MAXV = 1000; //最大顶点数
const int INF = 10000000; //设INF为一个很大的数
```

邻接矩阵版

```cpp
int n, G[MAXV][MAXV];
bool vis[MAXV] = {false};

void DFS(int u, int depth) {
  vis[u] = true;
  for(int v = 0; v < n; v++) {
    if(vis[v] == false && G[u][v] != INF) {
      DFS(v, depth + 1);
    }
  }
}

void DFSTrave() {
  for(int u = 0; u < n; u++) {
    if(vis[u] == false) {
      DFS(u, 1);
    }
  }
}
```



邻接表版

```cpp
vector<int> Adj[MAXV];
int n;
bool vis[MAXV] = {false};

void DFS(int u, int depth) {
  vis[u] = true;
  for(int i = 0; i < Adj[u].size(); i++) {
    DFS(v, depth + 1);
  }
}

void DFSTrave() {
  for(int u = 0; u < n; u++) {
    if(vis[u] == false) {
      DFS(u, 1);
    }
  }
}
```

Example

1034 Head of a Gang (30分)

One way that the police finds the head of a gang is to check people's phone calls. If there is a phone call between *A* and *B*, we say that *A* and *B* is related. The weight of a relation is defined to be the total time length of all the phone calls made between the two persons. A "Gang" is a cluster of more than 2 persons who are related to each other with total relation weight being greater than a given threshold *K*. In each gang, the one with maximum total weight is the head. Now given a list of phone calls, you are supposed to find the gangs and the heads.

Input Specification:

Each input file contains one test case. For each case, the first line contains two positive numbers *N*and *K* (both less than or equal to 1000), the number of phone calls and the weight threthold, respectively. Then *N* lines follow, each in the following format:

```
Name1 Name2 Time
```

where `Name1` and `Name2` are the names of people at the two ends of the call, and `Time` is the length of the call. A name is a string of three capital letters chosen from `A`-`Z`. A time length is a positive integer which is no more than 1000 minutes.

Output Specification:

For each test case, first print in a line the total number of gangs. Then for each gang, print in a line the name of the head and the total number of the members. It is guaranteed that the head is unique for each gang. The output must be sorted according to the alphabetical order of the names of the heads.

Sample Input 1:

```in
8 59
AAA BBB 10
BBB AAA 20
AAA CCC 40
DDD EEE 5
EEE DDD 70
FFF GGG 30
GGG HHH 20
HHH FFF 10
```

Sample Output 1:

```out
2
AAA 3
GGG 3
```

Sample Input 2:

```in
8 70
AAA BBB 10
BBB AAA 20
AAA CCC 40
DDD EEE 5
EEE DDD 70
FFF GGG 30
GGG HHH 20
HHH FFF 10
```

Sample Output 2:

```out
0
```

```cpp
#include<iostream>
#include<string>
#include<map>
using namespace std;

const int maxn = 2010;
const int INF = 10000000;

map<int, string> intToString;
map<string, int> stringToInt;
map<string, int> Gang;

int G[maxn][maxn] = {0};
int weight[maxn] = {0};
int n, k, numPerson = 0;
bool vis[maxn] = {false};


void DFS(int nowVisit, int& head, int& numMember, int& totValue) {
    numMember++;
    vis[nowVisit] = true;
    if(weight[nowVisit] > weight[head]) {
        head = nowVisit;
    }
    for(int i = 0; i < numPerson; i++) {
        if(G[nowVisit][i] > 0) {
            totValue += G[nowVisit][i];
            G[nowVisit][i] = G[i][nowVisit] = 0;
            if(vis[i] == false) {
                DFS(i, head, numMember, totValue);
            }
        }
    }
}
void DFSTrave() {
    for(int i = 0; i < numPerson; i++) {
        if(vis[i] == false) {
            int head = i, numMember = 0, totValue = 0;
            DFS(i, head, numMember, totValue);
            if(numMember > 2 && totValue > k) {
                Gang[intToString[head]] = numMember;
            }
        }
    }
}

int change(string str) {
    if(stringToInt.find(str) != stringToInt.end()) {
        return stringToInt[str];
    } else {
        stringToInt[str] = numPerson;
        intToString[numPerson] = str;
        return numPerson++;
    }
}

int main() {
    int w;
    string str1, str2;
    cin >> n >> k;

    for(int i = 0; i < n; i++) {
        cin >> str1 >> str2 >> w;
        int id1 = change(str1);
        int id2 = change(str2);
        weight[id1] += w;
        weight[id2] += w;
        G[id1][id2] += w;
        G[id2][id1] += w;
    }

    DFSTrave();
    cout << Gang.size() << endl;
    map<string, int>::iterator it;
    for(it = Gang.begin(); it != Gang.end(); it++) {
        cout << it->first << " " << it->second << endl;
    }
    return 0;
}
```



### B.BFS遍历图

使用BFS遍历图的基本思想是建立一个队列，并把初始顶点加入队列，此后每次都取出队首顶点进行访问，并把从该顶点出发可以到达的未曾加入过队列(而不是而访问)的顶点全部加入队列，直到队列为空。

```cpp
BFS(u) {
  queue q; //定义队列q
  将u入队;
  inq[u] = true; //设置u已被加入过队列
  while(q非空) {
    取出q的队首元素u进行访问;
    for(从u出发可达的所有顶点v) {
      if(inq[v] == false) {
        将v入队;
        inq[v] = true;	//设置v已被加入过队列
      }
    }
  }
}
```

#### 邻接矩阵实现

```cpp
int n, G[MAXV][MAXV];//n为顶点树
bool inq[MAXV] = {false};//若顶点i曾入过队列，则inq[i]=true

void BFS(int u) { //遍历u所在的连通块
  queue<int> q;
  q.push(u);
  inq[u] = true;
  while(!q.empty()) {
    int u = q.front();
    q.pop();
    for(int v = 0; v < n; v++) {
      if(inq[v] == false && G[u][v] != INF) {
        q.push(v);
        inq[v] = true;
      }
    }
  }
}
void BFSTrave() {
  for(int u = 0; u < n; u++) {
    if(inq[u] == false) {
      BFS(u);
    }
  }
}
```

#### 邻接表实现

```cpp
vector<int> Adj[MAXV];
int n;
bool inq[MAXV] = {false};

void BFS(int u) {
  queue<int> q;
  q.push(u);
  inq[u] = true;
  while(!q.empty()) {
    int u = q.front();
    q.pop();
    for(int i = 0; i < Adj[u].size(); i++) {
      int v = Adj[u][i];
      if(inq[v] == false) {
        q.push(v);
        inq[v] = true;
      }
    }
  }
}

void BFSTrave() {
  for(int u = 0; u < n; u++) {
    if(inq[u] == false) {
      BFS(q);
		}
  }
}
```

<br>

```cpp
struct Node {
  int v;
  int layer;
};
```

```cpp
vector<Node> Adj[N];
```

```cpp
void BFS(int s) {
  queue<Node> q;
  Node start;
  start.v = s;
  start.layer = 0;
  q.push(start);
  inq[start.v] = true;
  while(!q.empty()) {
    Node topNode = q.front();
    q.pop();
    int u = topNode.v;
    for(int i = 0; i < Adj[u].size(); i++) {
      Node next = Adj[u][i];
      next.layer = topNode.layer + 1;
      if(inq[next.v] == false) {
        q.push(next);
        inq[next.v] = true;
      }
    }
  }
}
```



<br>

# 最短路径

### A. Dijkstra算法

Dijkstra算法用来解决单源最短路径问题, 即给定图G(V,E)和起点s, 求从起点s到达其他顶点的最短距离

设置集合S存放已被访问的顶点，然后执行n次下面的两个步骤(n为顶点个数)

1. 每次从集合V-S(即没有被访问过的顶点)中选择与起点s的最短距离最小的一个顶点u, 访问并加入集合S
2. 令顶点u为中介点，优化起点s与从u能到达的顶点v之间的最短距离

在具体实现时

1. 集合S可以用一个bool数组vis[]来实现，当vis[i]==true时表示顶点$V_i$已经被访问，当vis[i]==false时表示顶点$V_i$未被访问
2. 令int数组d[]表示起点s到达顶点$V_i$的最短距离，初始时除了起点s的d[s]赋为0，其余顶点都初始化为一个很大的数,可以使用$10^9$, 也可以用0x3fffffff, 但是不要用0x7ffffffff, 因为这样两个数相加会超过int的表示范围

伪代码

```cpp
Dijkstra(G, d[], s) {
  初始化;
  for(循环n次) {
    u = 使d[u]最小的还未被访问的顶点的编号;
    记u已被访问;
    for(从u出发能到达的所有顶点v) {
      if(v未被访问&&以u为中介使s到顶点v的最短距离d[v]更优) {
        优化d[v];
      }
    }
  }
}
```

<br>

```cpp
const int MAXV = 1000;
const int INF = 10000000;
```

#### 邻接矩阵实现

```cpp
int n, G[MAXV][MAXV];
int d[MAXV];
bool vis[MAXV] = {false};

void Dijkstra(int s) {
  fill(d, d + MAXV, INF); //fill函数将整个d数组初始化为INF
  d[s] = 0;
  for(int i = 0; i < n; i++) {
    int u = -1, MIN = INF;
    //从未访问的顶点中选择一个到s的距离最小的顶点u
    for(int j = 0; j < n; j++) {
      if(vis[j] == false && d[j] < MIN) {
        u = j;
        MIN = d[j];
      }
    }
    if(u == -1) return;
    vis[u] = true;
    //更新从u能到达的顶点的最短距离
    for(int v = 0; v < n; v++) {
      if(vis[v] == false && G[u][v] != INF && d[u] + G[u][v] < d[v])
        d[v] = d[u] + G[u][v];
    }
  }
}
```

#### 邻接表实现

```cpp
struct Node {
  int v;
  int dis;
};
vector<Node> Adj[MAXN];
int n;
int d[MAXV];
bool vis[MAXV] = {false};

void Dijkstra(int s) {
  fill(d, d + MAXV, INF);
  d[s] = 0;
  for(int i = 0; i < n; i++) {
    int u = -1; MIN = INF;
    for(int j = 0; j < Adj[i].size(); j++) {
      if(vis[j] == false && d[j] < MIN) {
        u = j;
        MIN = d[j];
      }
    }
    if(u == -1) return;
    vis[u] = true;
    
    for(int j = 0; j < Adj[u].size(); j++) {
      int nodeID = Adj[u][j].v;
      if(vis[nodeID] == false && d[u] + Adj[u][j].dis < d[nodeID]) {
        d[nodeID] = d[u] + Adj[u][j].dis;
      }
    }
  }
}
```

复杂度分析:

主要是外层循环$O(V)$与内层循环(寻找最小的d[u]需要$O(V)$, 枚举v需要$O(adj[u].size())$)。对于整个程序来说，枚举v的次数总共为$O(\sum_{u=0}^{n-1}adj[u].size)=O(E)$, 因此总复杂度为$O(V^2+E)$

寻找最小d[u]的过程可以优化，使用最小堆，复杂度可以降为$O(VlogV+E)$

Dijkstra算法只能应对所有边权都是非负数的情况，如果边权出现负数，Dijkstra算法可能会出错，最好使用SPFA算法

<br>

#### 求解最短路径的写法

在Dijkstra算法中有一段

```cpp
if(v未被访问 && 以u为中介点可以使起点s到顶点v的最短距离d[v]更优) {
  优化d[v];
}
```

我们设置一个数组pre[], pre[v]记录从起点s到顶点v的最短路径上v的前一个顶点(前驱节点)

```cpp
if(v未被访问 && 以u为中介点可以使起点s到顶点v的最短距离d[v]更优) {
  优化d[v];
  令v的前驱为u;
}
```

<br>

```cpp
int n, G[MAXV][MAXV];
int d[MAXV];
int pre[MAXV];
bool vis[MAXV] = {false};

void Dijkstra(int s) {
  fill(d, d + MAXV, INF);
  for(int i = 0; i < n; i++) pre[i] = i;
  d[s] = 0;
  for(int i = 0; i < n; i++) {
    int u = -1; int MIN = INF;
    for(int j = 0; j < n; j++) {
      if(vis[j] == false && d[j] < MIN) {
        u = j;
        MIN = d[j];
      }
    }
    
    if(u == -1) return;
    vis[u] = true;
    
    for(int v = 0; v < n; v++) {
      if(vis[v] == false && G[u][v] != INF && d[u] + G[u][v] < d[v]) {
        d[v] = d[u] + G[u][v];
        path[v] = u;
      }
    }
  }
}
```

<br>

如果要得到整一条路径

```cpp
void DFS(int s, int v) {
  if(v == s) {
    printf("%d\n", s);
    return;
  }
  DFS(s, pre[v]);
  printf("%d\n", v);
}
```

<br>

当然，有时候最短距离最小的路径不止一条。碰到这种有两条以上可以达到最短距离的路径，题目会给出第二个标尺(第一标尺是距离)，要求在所在所有最短路径中选择第二标尺最优的一条路径。第二标尺常见的是以下三种出题方法或其组合：

1. 给每条边再增加一个边权(比如花费)，然后要求在最短路径有多条时要求路径上的花费之和最小
2. 给每个点增加一个点权(比如每个城市能收集到的物资)，然后在最短路径有多条时要求路径上的点权之和最大
3. 直接问有多少条最短路径

针对第一种新增边权。以新增的边权代表花费为例，用cost\[u][v]表示u-->v的花费(题目给出)， 并增加一个数组c[], 令从起点到达顶点u的最少花费为c[u], 初始化时只有c[s]为0， 其余c[u]均为INF, 这样就可以在d[u]+G\[u][v]<d[v]时更新d[v]和c[v], 而当d[u]+G\[u][v]=d[v]且c[u]+cost\[u][v]<c[v]时更新c[v]

```cpp
for(int v = 0; v < n; v++) {
  if(vis[v] == false && G[u][v] != INF) {
    if(d[u] + G[u][v] < d[v]) {
      d[v] = d[u] + G[u][v];
      c[v] = c[u] + cost[u][v];
		} else if(d[u] + G[u][v] == d[v] && c[u] + cost[u][v] < c[v]) {
      c[v] = c[u] + cost[u][v];
    }
  }
}
```

针对第二种情况新增点权。以新增的点权代表城市中能收集到的物资为例，用weight[u]表示盛水u中的物资数目(由题目输入)，并增加一个数组w[], 令从起点到达顶点u可以收集到的最大物资为w[u], 初始化时只有w[s]为weight[s], 其余w[u]均为0。 这样就可以在d[u]+G\[u][v]<d[v]时更新d[v]和w[v]。 而当d[u]+G\[u][v]==d[v]且w[u]+weight[v] > w[v]时更新w[v]

```cpp
for(int v = 0; v < n; v++) {
  if(vis[v] == false && G[u][v] != INF) {
    if(d[u] + G[u][v] < d[v]) {
      d[v] = d[u] + G[u][v];
      w[v] = w[u] + weight[v];
    } else if(d[u] + G[u][v] == d[v] && w[u] + weight[v] > w[v]) {
      w[v] = w[u] + weight[v];
    }
  }
}
```

针对求解最短路径条数，只需新增一个数组num[], 令从起点s到达顶点u的最短路径条数为num[u], 初始化时只有num[s]为1，其余num[u]均为0，这样就可以在d[u]+G\[u][v]<d[v]时更新d[v], 并且让num[v]继承num[u]; 当d[u]+G\[u][v]==d[v]时将num[u]加到num[v]上

```cpp
for(int v = 0; v < n; v++) {
  if(vis[v] == false && G[u][v] != INF) {
    if(d[u] + G[u][v] < d[v]) {
      d[v] = d[u] + G[u][v];
      num[v] = num[u];
    } else if(d[i] + G[u][v] == d[v]) {
      num[v] += num[u];
    }
  }
}
```



#### Example

A1003 Emergency (25分)

As an emergency rescue team leader of a city, you are given a special map of your country. The map shows several scattered cities connected by some roads. Amount of rescue teams in each city and the length of each road between any pair of cities are marked on the map. When there is an emergency call to you from some other city, your job is to lead your men to the place as quickly as possible, and at the mean time, call up as many hands on the way as possible.

Input Specification:

Each input file contains one test case. For each test case, the first line contains 4 positive integers: *N*(≤500) - the number of cities (and the cities are numbered from 0 to *N*−1), *M* - the number of roads, *C*1 and *C*2 - the cities that you are currently in and that you must save, respectively. The next line contains *N* integers, where the *i*-th integer is the number of rescue teams in the *i*-th city. Then *M* lines follow, each describes a road with three integers *c*1, *c*2 and *L*, which are the pair of cities connected by a road and the length of that road, respectively. It is guaranteed that there exists at least one path from *C*1 to *C*2.

Output Specification:

For each test case, print in one line two numbers: the number of different shortest paths between *C*1and *C*2, and the maximum amount of rescue teams you can possibly gather. All the numbers in a line must be separated by exactly one space, and there is no extra space allowed at the end of a line.

Sample Input:

```in
5 6 0 2
1 2 1 5 3
0 1 1
0 2 2
0 3 1
1 2 1
2 4 1
3 4 1 
```

Sample Output:

```out
2 4
```





```cpp
#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;

const int MAXV = 510;
const int INF = 0x3fffffff;
int n, m, s, rescueNum, G[MAXV][MAXV];
int weight[MAXV], w[MAXV];
int d[MAXV];
bool vis[MAXV] = {false};
int num[MAXV];

void Dijkstra(int s) {
    fill(d, d + MAXV, INF);
    d[s] = 0;
    num[s] = 1;
    w[s] = weight[s];

    for(int i = 0; i < n; i++) {
        int u = -1, MIN = INF;
        for(int j = 0; j < n; j++) {
            if(vis[j] == false && d[j] < MIN) {
                u = j;
                MIN = d[j];
            }
        }

        if(u == -1) return;
        vis[u] = true;
        for(int v = 0; v < n; v++) {
            if(vis[v] == false && G[u][v] != INF) {
                if(d[u] + G[u][v] < d[v]) {
                    d[v] = d[u] + G[u][v];
                    w[v] = w[u] + weight[v];
                    num[v] = num[u];
                } else if(d[u] + G[u][v] == d[v]) {
                    num[v] += num[u];
                    if(w[u] + weight[v] > w[v]) {
                        w[v] = w[u] + weight[v];
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d%d%d%d", &n, &m, &s, &rescueNum);
    for(int i = 0; i < n; i++) {
        scanf("%d", &weight[i]);
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            G[i][j] = INF;
    }

    for(int i = 0; i < m; i++) {
        int u, v, len;
        scanf("%d%d%d", &u, &v, &len);
        G[u][v] = G[v][u] = len;
    }
    Dijkstra(s);
    printf("%d %d", num[rescueNum], w[rescueNum]);

}
```



