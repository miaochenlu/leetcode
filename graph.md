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



