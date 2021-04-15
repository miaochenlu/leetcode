# 1. vector的常见用法详解

```cpp
vector<int> vi;
for(int i = 1; i <= 5; i++) {
  vi.push_back(i);
}

for(vector<int>::iterator it = vi.begin(); it != vi.end(); it++) {
  printf("%d ", *it);
}
```

* `push_back(x)`:在vector后面添加一个元素x,时间复杂度为O(1)
* `pop_back()`: 删除vector的尾元素，时间复杂度为O(1)
* `size()`:获得vector中元素的个数，时间复杂度为O(1)
* `clear()`: 用来清空vector中的所有元素，时间复杂度为O(n)
* `insert(it, x)`: 向vector的任意迭代器it处插入一个元素x

* `erase()`
  * `erase(it)`：删除迭代器为it处的元素
  * `erase(first, last)`：删除 [first, last)内的所有元素

# 2. set的常见用法详解

set是一个内部自动有序且不含重复元素的容器

* `insert(x)`： 将x插入set容器中，并且自动递增排序和去重，时间复杂度是O(logN)
* `find(value)`: 返回set中对应值为value的容器，时间复杂度为O(logN)
* `erase()`
  * `erase(it)`: it为所需要删除元素的迭代器，时间复杂度为O(1), 可以结合find()函数使用
  * `erase(value)`: value为所需要删除元素的值，时间复杂度为O(logN)
  * `erase(first, last)`: 删除[first, last)区间内的所有元素
* `size()`
* `clear()`: 清空set中的所有元素



# 3. string的用法详解

* `operator+=`: 拼接字符串
* `compare operator == != <= ...`: 比较字符串字典序
* `length() / size()`: 返回string的长度，也就是存放的字符数
* `insert()`
  * `insert(pos, string)`: 在pos号位置插入字符串string
  * `insert(it, it2, it3)`: 字符串[it2, it3)插入在it的位置上
* `erase()`
  * `erase(it)`
  * `erase(first, last)`
* `clear()`: 时间复杂度为O(1)
* `substr(pos, len)`: 返回从pos号位开始，长度为len的子串

* `find()`
  * `find(str2)`:当str2是str的子串时，返回其在str中第一次出现的位置；如果str2不是str的子串，那么返回`string::npos`
  * `find(str2, pos)`: 从str的pos号位开始匹配str2, 返回值与上面相同
* `string::npos`: 一个常数，本身的值为-1, 也是18446744073709551615。
* `replace()`
  * `replace(pos, len, str2)`: 把str从pos号位开始，长度为len的子串替换成str2
  * replace(it1, it2, str2): 把str的迭代器[it1, it2)番位的子串替换成str2



### 1060 Are They Equal (25分)

If a machine can save only 3 significant digits, the float numbers 12300 and 12358.9 are considered equal since they are both saved as 0.123×105 with simple chopping. Now given the number of significant digits on a machine and two float numbers, you are supposed to tell if they are treated equal in that machine.

### Input Specification:

Each input file contains one test case which gives three numbers *N*, *A* and *B*, where *N* (<100) is the number of significant digits, and *A* and *B* are the two float numbers to be compared. Each float number is non-negative, no greater than 10100, and that its total digit number is less than 100.

### Output Specification:

For each test case, print in a line `YES` if the two numbers are treated equal, and then the number in the standard form `0.d[1]...d[N]*10^k` (`d[1]`>0 unless the number is 0); or `NO` if they are not treated equal, and then the two numbers in their standard form. All the terms must be separated by a space, with no extra space at the end of a line.

Note: Simple chopping is assumed without rounding.

### Sample Input 1:

```in
3 12300 12358.9
```

### Sample Output 1:

```out
YES 0.123*10^5
```

### Sample Input 2:

```in
3 120 128 
```

### Sample Output 2:

```out
NO 0.120*10^3 0.128*10^3
```



```cpp
#include<iostream>
#include<string>
using namespace std;
int n;

string deal(string s, int& e) {
    int k = 0;
    while(s.length() > 0 && s[0] == '0') {
        s.erase(s.begin());
    }
    if(s[0] == '.') {
        s.erase(s.begin());
        while(s.length() > 0 && s[0] == '0') {
            s.erase(s.begin());
            e--;
        }
    } else {
        while(k < s.length() && s[k] != '.') {
            k++;
            e++;
        }
        if(k < s.length()) {
            s.erase(s.begin() + k);
        }
    }
    if(s.length() == 0) e = 0;

    int num = 0;
    k = 0;
    string res; 
    while(num < n) {
        if(k < s.length()) res += s[k++];
        else res += '0';
        num++;
    }
    return res;
}

int main() {
    string s1, s2, s3, s4;
    cin >> n >> s1 >> s2;
    int e1 = 0, e2 = 0;
    s3 = deal(s1, e1);
    s4 = deal(s2, e2);

    if(s3 == s4 && e1 == e2) {
        cout << "YES 0." << s3 << "*10^" << e1 << endl;
    } else {
        cout << "NO 0." << s3 << "*10^" << e1 << " 0." << s4 << "*10^" << e2 << endl;
    }
}
```



# 4. map的常用用法详解

```cpp
map<typename1, typename2> mp;
```



map的访问

```cpp
map<char, int> mp;
//通过下标访问
mp['m'] = 20;
mp['r'] = 30;
//通过迭代器访问
for(map<char, int>::iterator it = mp.begin();  it != mp.end(); it++) {
  printf("%c %d\n", it->first, it->second);
}
```



* `find(key)`： 返回键为key的映射的迭代器，复杂度为O(logN)
* `erase()`
  * `erase(it)`:
  * `erase(key)`
  * `erase(first, last)`

* `size()`
* `clear()`



# 5. queue的常见用法详解

```cpp
queue<typename> name;
```

* `front()`: 访问队首元素
* `back()`: 队尾元素
* `pop()`: 令队首元素出队
* `empty()`： 检测queue是否为空
* `size()`： queue内元素个数



当需要实现广度优先搜索时，可以使用queue。

在使用`front()`和`pop()`函数之前，必须用`empty()`函数判断队列是否为空



# 6. priority queue的常见用法详解

底层通过堆来实现。在优先队列中国呢，队首元素时当前队列中优先级最高的那一个

* `push(x)`:将x入队
* `top()`： 访问队首元素
* `pop()`： 令队首元素出队
* `empty()`: 检测优先队列是否为空
* `size()`



## 6.1 优先级的设置

### A. 基本数据类型的优先级设置:int, char, double

```cpp
//默认大的优先级高
priority_queue<int> q;
//vector<int>填写的事用来承载底层数据结构堆堆容器
//less<int>是对第一个参数的比较类。less<int>表示数字大的优先级越大，而greater<int>表示数字小的优先级越大
priority_queue<int, vector<int>, less<int> >q;
```

### B. 结构体的优先级设置

```cpp
struct fruit {//重载运算符
  string name;
  int price;
  friend bool operator < (fruit f1, fruit f2) {
    return f1.price < f2.price;
  }
}
priority_queue<fruit> q;//价格高的水果优先级高
```

```cpp
struct fruit {
  string name;
  int price;
}

struct cmp {
  bool operator()(fruit f1, fruit f2) {
    return f1.price < f2.price;
  }
}
priority_queue<fruit, vector<fruit>, cmp> q;
```



# 7. stack

```cpp
stack<typename> name;
```

* `push(x)`
* `top()`
* `pop()`
* `empty()`
* `size()`
* `clear()`



# 8. pair

```cpp
pair<string, int> p;
p.first = "haha"; p.second = 5;

p = make_pair("xixi", 55);

p = pair<string, int>("heihei", 555);
```



## pair的比较

先比较first, 再比较second



## pair的常见用途

* 用来代替二元结构体及其构造函数
* 作为map的键值对来进行插入

```cpp
map<string, int> mp;
mp.insert(make_pair("heihei", 5));
mp.insert(pair<string, int>("haha", 10));
```



# 9. algorithm下的常用函数

## 9.1 max(), min(), abs()

abs(x)的x必须是整数，如果是浮点数要用fabs

## 9.2 swap()

swap(x, y)用来交换x,y的值

## 9.3 reverse()

reverse(it, it2)可以将数组指针在[it, it2)之间的元素或容器的迭代器在[it, it2)范围内的元素进行反转

## 9.4 next_permutation()

给出一个序列在全排列中的下一个序列

```cpp
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    int a[10] = {1, 2, 3};
    do {
        cout << a[0] << a[1] << a[2] << endl;
    }while(next_permutation(a, a + 3));
}
```

```
123
132
213
231
312
321
```



## 9.5 fill

fill()可以把数组或容器的某一段区间赋为某个相同的值，和memset不同，这里的福祉可以是数组类型对应范围中的任意值

```cpp
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
    int a[5] = {1, 2, 3, 4, 5};
    fill(a, a + 5, 233);
    for(int i = 0; i < 5; i++) {
        cout << a[i] << endl;
    }
}
```

```
233
233
233
233
233
```



## 9.6 sort

`sort(首元素地址，尾元素地址的下一个地址，比较函数)`



### 结构体的排序

```cpp
struct node{
  int x, y;
}ssd[10];
bool cmp(node a, node b) {
  if(a.x != b.x) return a.x > b.x;//x不相等时按x从大到小排序
  else return a.y < b.y;//x相等时按y从小到大排序
}
sort(ssd, ssd + 3, cmp);
```

### 容器的排序

```cpp
bool cmp(int a, int b) {
  return a > b;
}
vector<int> vi;
sort(vi.begin() , vi.end(), cmp);

```



## 9.7 lower_bound() and upper_bound()

```cpp
lower_bound(first, last, val);
```

寻找在数组或容器的[first, last)范围内第一个值大于等于val的元素的位置，如果是数组，则返回该位置的指针；如果是容器，则返回该位置的迭代器