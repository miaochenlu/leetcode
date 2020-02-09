# 1.简单数学

#### 1019 数字黑洞 (20 分)

给定任一个各位数字不完全相同的 4 位正整数，如果我们先把 4 个数字按非递增排序，再按非递减排序，然后用第 1 个数字减第 2 个数字，将得到一个新的数字。一直重复这样做，我们很快会停在有“数字黑洞”之称的 `6174`，这个神奇的数字也叫 Kaprekar 常数。

例如，我们从`6767`开始，将得到

```
7766 - 6677 = 1089
9810 - 0189 = 9621
9621 - 1269 = 8352
8532 - 2358 = 6174
7641 - 1467 = 6174
... ...
```

现给定任意 4 位正整数，请编写程序演示到达黑洞的过程。

#### 输入格式：

输入给出一个 (0,104) 区间内的正整数 *N*。

#### 输出格式：

如果 *N* 的 4 位数字全相等，则在一行内输出 `N - N = 0000`；否则将计算的每一步在一行内输出，直到 `6174` 作为差出现，输出格式见样例。注意每个数字按 `4` 位数格式输出。

#### 输入样例 1：

```in
6767
```

#### 输出样例 1：

```out
7766 - 6677 = 1089
9810 - 0189 = 9621
9621 - 1269 = 8352
8532 - 2358 = 6174
```

#### 输入样例 2：

```in
2222
```

#### 输出样例 2：

```out
2222 - 2222 = 0000
```



```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int A[5];

void num2Array(int num) {
    for(int i = 0; i < 4; i++) {
        A[i] = num % 10;
        num /= 10;
    }
}

int array2Num() {
    int res = 0;
    for(int i = 0; i < 4; i++) {
        res = res * 10 + A[i];
    }
    return res;
}
bool compare(int A, int B) {
    return A > B;
}
int main() {
    int num;
    cin >> num;
    while(1) {
        num2Array(num);
        sort(A, A + 4);
        int minNum = array2Num();
        sort(A, A + 4, compare);
        int maxNum = array2Num();
        num = maxNum - minNum;
        printf("%04d - %04d = %04d\n", maxNum, minNum, num);
        if(num == 0 || num == 6174) break;
    }
}
```



# 2. 最大公约数与最小公倍数

### 2.1 最大公约数

定理：

设a, b为正整数，则$gcd(a,b)=gcd(b, a\%b )$

证明：

设$a=kb+r$,其中k是商，b是余数

则有$r=a-kb$

设d为a和b的一个公约数

那么由$r=a-kb$, d也是r的一个约束

因此d是b和r的一个公约数

又由$r=a\%b$, 则d为b和$a\%b$的一个公约数

因此d既是a和b的公约数，也是b和$a\%b$的公约数

因为d的任意性，a和b的公约数都是b和$a\%b$的公约数

同理可证b和$a\%b$的公约数都是a和b的公约数

证毕！



如果$a<b$,定理的结果是gcd(a,b)变成gcd(b, a)

如果$a>b$, 那么通过这个定理可以将数据规模变小

```cpp
int gcd(int a, int b) {
  if(b == 0) return a;
  else return gcd(b, a % b);
}
```

```cpp
int gcd(int a, int b) {
  return !b ? a : gcd(b, a % b);
}
```



## 2.2 最小公倍数

a,b的最小公倍数=a*b/gcd(a,b)

因为a*b在计算时有可能溢出

所以恰当的写法是$lcm(a,b)=a/gcd(a,b)*b$





# 3. 分数的四则运算

## 3.1 分数的表示和化简

### 表示

```cpp
struct Fraction {
  int up, down;
}
```

### 化简

```cpp
Fraction reduction(Fraction result) {
  if(result.down < 0) {
    result.up = -result.up;
    result.down = -result.down;
  }
  if(result.up == 0) {
    result.down = 1;
  } else {
    int d = gcd(abs(result.up), abs(result.down));
    result.up /= d;
    result.down /= d;
  }
  return result;
}
```



## 3.2 分数的四则运算

```cpp
Fraction add(Fraction f1, Fraction f2){
  Fraction result;
  result.up = f1.up * f2.down + f2.up * f1.down;
  result.down = f1.down * f2.down;
  return reduction(result);
}
```



```cpp
Fraction minu(Fraction f1, Fraction f2){
  Fraction result;
  result.up = f1.up * f2.down - f1.down * f2.up;
  result.down = f1.down * f2.down;
  return reduction(result);
}
```



```cpp
Fraction multi(Fraction f1, Fraction f2) {
  Fraction result;
  result.up = f1.up * f2.up;
  result.down = f1.down * f2.down;
  return reduction(result);
}
```



```cpp
Fraction divide(Fraction f1, Fraction f2) {
  Fraction result;
  result.up = f1.up * f2.down;
  result.down = f1.down * f2.up;
  return reduction(result);
}
```



练习题

### Problem A: 分数矩阵

#### Description	

我们定义如下矩阵：

```
1/1 1/2 1/3
1/2 1/1 1/2
1/3 1/2 1/1
```

矩阵对角线上的元素始终是1/1，对角线两边分数的分母逐个递增。
请求出这个矩阵的总和。

#### Input	

输入包含多组测试数据。每行给定整数N（N<50000），表示矩阵为N*N。当N=0时，输入结束。	

#### Output	

输出答案，结果保留2位小数。	

#### Sample Input

```
1
2
3
4
0
```

#### Sample Output

```
1.00
3.00
5.67
8.83
```

solution:

思路是

右上角矩阵和左下角矩阵的和是一样的，然后再加上对角线上的数

```cpp
#include<iostream>
#include<cstdio>
using namespace std;

int main() {
    int n;
    double result = 0;

    cin >> n;
    while(n) {
        double tmp = 0;
        result = 0;
        for(int i = 1; i < n; i++) {
            tmp = tmp + 1.0 / (i + 1);
            result += tmp;
        }
        result = result * 2 + n;
        printf("%.2f\n", result);
        cin >> n;
    }
}
```



# 4. 素数

## 4.1 素数的判断

```cpp
bool isPrime(int n) {
	if(n <= 1) return false;
  int sqr = (int)sqrt(1.0 * n);
  for(int i = 2; i <= sqr; i++) {
    if(n % i == 0) return false;
  }
  return true;
}
```

有更简单的写法

```cpp
bool isPrime(int n) {
  if(n <= 1) return false;
  for(long long i = 2; i * i <= n; i++) { //long long避溢出
    if(n % i == 0) return false;
  }
  return true;
}
```



## 4.2 素数表的获取

  素数筛, 复杂度$O(nloglogn)$

```cpp
#include<cstdio>
const int maxn = 101;
int prime[maxn], pNum = 0;//prime数组放所有素数，pNum为素数个数
bool p[maxn] = {0};
void Find_Prime() {
  for(int i = 2; i < maxn; i++) {
    if(p[i] == false) {
      prime[pNum++] = i;
      //把素数的倍数全部删掉
      for(int j = i + i; j < maxn; j += i) {
        p[j] = true;
      }
    }
  }
}
int main() {
  Find_Prime();
  for(int i = 0; i < pNum; i++) {
    printf("%d ", prime[i]);
  }
  return 0;
}
```



# 5. 质因子分解

### PAT 1059 Prime Factors (25分)

Given any positive integer *N*, you are supposed to find all of its prime factors, and write them in the format $N = p_1^{k_1}\times p_2^{k_2}\times\cdots\times p_m^{k_m}$

### Input Specification:

Each input file contains one test case which gives a positive integer *N* in the range of **long int**.

### Output Specification:

Factor *N* in the format *N* `=` *p*1`^`*k*1`*`*p*2`^`*k*2`*`…`*`*pm*`^`*km*, where *pi*'s are prime factors of *N* in increasing order, and the exponent *ki* is the number of *pi* -- hence when there is only one *pi*, *ki* is 1 and must **NOT** be printed out.

### Sample Input:

```in
97532468
```

### Sample Output:

```out
97532468=2^2*11*17*101*1291
```



```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
using namespace std;
struct factor {
    int x, cnt;
} fac[1000];

const int maxn = 100000;
int prime[maxn];
int pNum;
int flag[maxn];

void Find_Prime(int n) {
    for(int i = 2; i < n; i++) {
        if(flag[i] == 0) {
            prime[pNum++] = i;
            for(int j = i + i; j < n; j += i) {
                flag[j] = 1;
            }
        }
    }
}
int main() {
    long n;
    cin >> n;
		cout << n << "=";
    if(n == 1) {
        cout << 1;
        return 0;
    }
    Find_Prime(sqrt(1.0 * n));
    int num = 0;
    for(int i = 0; i < pNum; i++) {
        if(n % prime[i] == 0) {
            fac[num].x = prime[i];
            fac[num].cnt = 0;
            while(n % prime[i] == 0) {
                fac[num].cnt++;
                n /= prime[i];
            }
            num++;
        }
    }
    if(n != 1) {
        fac[num].x = n;
        fac[num++].cnt = 1;
    }

    for(int i = 0; i < num - 1; i++) {
        cout << fac[i].x;
        if(fac[i].cnt != 1) cout << "^" << fac[i].cnt;
        cout << "*";
    }
    cout << fac[num - 1].x;
    if(fac[num - 1].cnt != 1) cout << "^" << fac[num - 1].cnt;    
}
```









































