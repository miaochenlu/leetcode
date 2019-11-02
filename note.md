```cpp
int n, P[maxn], hashTable[maxn] = {false};

void generateP(int index) {
  if(index == n + 1) {
    for(int i = 1; i < index; i++) 
      printf("%d ", i);
    printf("\n");
    return;
	}
  for(int x = 1; x <= n; i++) {
    if(hashTable[x] == false) {
      P[index] = x;
      hashTable[x] = true;
      generateP(index + 1);
      hashTable[x] = false;
    }
  }
}
```



# 4. 贪心

## 4.1 简单贪心



1020 月饼 (25 分)

月饼是中国人在中秋佳节时吃的一种传统食品，不同地区有许多不同风味的月饼。现给定所有种类月饼的库存量、总售价、以及市场的最大需求量，请你计算可以获得的最大收益是多少。

注意：销售时允许取出一部分库存。样例给出的情形是这样的：假如我们有 3 种月饼，其库存量分别为 18、15、10 万吨，总售价分别为 75、72、45 亿元。如果市场的最大需求量只有 20 万吨，那么我们最大收益策略应该是卖出全部 15 万吨第 2 种月饼、以及 5 万吨第 3 种月饼，获得 72 + 45/2 = 94.5（亿元）。

#### 输入格式：

每个输入包含一个测试用例。每个测试用例先给出一个不超过 1000 的正整数 *N* 表示月饼的种类数、以及不超过 500（以万吨为单位）的正整数 *D* 表示市场最大需求量。随后一行给出 *N* 个正数表示每种月饼的库存量（以万吨为单位）；最后一行给出 *N* 个正数表示每种月饼的总售价（以亿元为单位）。数字间以空格分隔。

#### 输出格式：

对每组测试用例，在一行中输出最大收益，以亿元为单位并精确到小数点后 2 位。

#### 输入样例：

```in
3 20
18 15 10
75 72 45
```

#### 输出样例：

```out
94.50
```



思路就是挑选单位重量价格最高的

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int N;
double D;

struct P{
    double totPrice;
    double weight;
    double perPrice;
} product[2000];

bool cmp(struct P a, struct P b) {
    return a.perPrice > b.perPrice;
}
int main() {
    cin >> N >> D;
    for(int i = 0; i < N; i++) {
        cin >> product[i].weight;
    }
    for(int i = 0; i < N; i++) {
        cin >> product[i].totPrice;
        product[i].perPrice = product[i].totPrice * 1.0 / product[i].weight;
    }

    double earn = 0;
    sort(product, product + N, cmp);
    
    int i = 0;
    while(D > 0 && i < N) {
        double purchaseweight = min(D, product[i].weight);
        D -= purchaseweight;
        earn += purchaseweight * product[i].perPrice;
        i++;
    }
    printf("%.2f", earn);
}
```



### 1023 组个最小数 (20 分)

给定数字 0-9 各若干个。你可以以任意顺序排列这些数字，但必须全部使用。目标是使得最后得到的数尽可能小（注意 0 不能做首位）。例如：给定两个 0，两个 1，三个 5，一个 8，我们得到的最小的数就是 10015558。

现给定数字，请编写程序输出能够组成的最小的数。

#### 输入格式：

输入在一行中给出 10 个非负整数，顺序表示我们拥有数字 0、数字 1、……数字 9 的个数。整数间用一个空格分隔。10 个数字的总个数不超过 50，且至少拥有 1 个非 0 的数字。

#### 输出格式：

在一行中输出能够组成的最小的数。

#### 输入样例：

```in
2 2 0 0 0 3 0 0 1 0
```

#### 输出样例：

```out
10015558
```



我的思路：

读入的字符序列是一个有序的序列，将第一个0与第一个不为0的位置进行调换

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int number[60];
int main() {
    int i = 0; int j = 0;
    int number_i = 0;
    for(i = 0; i < 10; i++) {
        cin >> number_i;
        while(number_i > 0) {
            number[j++] = i;
            number_i--;
        }
    }
    int s = 0;
    if(number[0] == 0) {
        while(1) {
            if(number[s] > 0) {
                number[0] = number[s];
                number[s] = 0;
                break;
            } 
            else s++;
        }
    }
    for(int i = 0; i < j; i++) {
        cout << number[i];
    }
    cout << endl;
}
```

思路二：我觉得更好

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int number[11];
int main() {
    int firstNotZero = -1;
    for(int i = 0; i < 10; i++) {
        cin >> number[i];
    }

    for(int i = 1; i < 10; i++) {
        if(number[i] > 0) {
            cout << i;
            number[i]--;
            break;
        }
    }
    for(int i = 0; i < 10; i++) {
        while(number[i] > 0) {
            cout << i;
            number[i]--;
        }
    }
    cout << endl;
}
```



## 4.2 区间贪心

从结束往开始选，总是选择符合条件的开始时间最晚的

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 110;
struct Interval {
  int x, y; //开区间左右端点
}I[maxn];

bool cmp(Interval a, Interval b) {
  if(a.x != b.x) return a.x > b.x; //按区间座端点从大到小排序
  else return a.y < b.y;//按右端点从小到大排序
}

int main() {
  int n;
  while(scanf("%d", &n), n != 0) {
    for(int i = 0; i < n; i++) {
      scanf("%d%d", &I[i].x, &I[i].y);
    }
    sort(I, I + n; cmp);
    
    int ans = 1, lastX = I[0].x;
    for(int i = 1; i < n; i++) {
      if(I[i].y <= lastX) {
        lastX = I[i].x;
        ans++;
      }
    }
  }
}
```

对应leetcode训练





# 5. 二分

```cpp
int binarySearch(int A[], int left, int right, int x) {
  int mid;
  while(left <= right) {	//如果left>right没法形成区间
    mid = (left + right) / 2;
    if(A[mid] == x) return mid;
    else if(A[mid] < x) {
      right = mid - 1;	// [left, mid - 1]
		} else {
      left = mid + 1;		// [mid + 1, right]
    }
  }
  return -1;
}
```

有一些要注意的地方

`mid = (left + right) / 2`中的`left + right`可能会超过int而溢出，可以使用`mid = left + (right - left) / 2`来代替



接下来我们会解决的问题是： 求出序列中第一个$\geq x$的元素的位置L以及第一个大于x的元素的位置R，这样x在序列中的存在区间就是[L, R)

先找第一个>=x的元素的位置

```cpp
int lower_bound(int A[], int left, int right, int x) {
  int mid;
  while(left < right) { 			//注意这里没有=
    mid = (left + right) / 2;
    if(A[mid] >= x) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  return left;
}
```

再找出序列中第一个大于x的元素的位置

```cpp
int upper_bound(int A[], int left, int right, int x) {
  int mid;
  while(left < right) {
    mid = (left + right) / 2;
    if(A[mid] > x) {
      right = mid;
    } else {//A[mid] <= x
      left = mid + 1;
    }
  }
  return left;
}
```





寻找有序序列中第一个满足某条件的元素的位置的模板

左闭右闭区间[left, right]

```cpp
int solve(int left, int right) {
  int mid;
  while(left < right) {
    mid = (left + right) / 2;
    if(条件成立) {//条件成立，第一个满足条件的位置<=mid
      right = mid;		//查找[left, mid]
    } else {//条件不成立，第一个满足条件的位置>mid
      left = mid + 1;	//查找[mid + 1, right]
    }
  }
  return left
}
```

左开右闭区间(left, right]

```cpp
int solve(int left, int right) {
  int mid;
  while(left + 1 < right) {
    if(条件成立) {
      right = mid;
    } else {
      left = mid;
    }
  }
  return right;
}
```

例题：

[744. Find Smallest Letter Greater Than Target](greedy/744.md)

