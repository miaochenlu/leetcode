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

