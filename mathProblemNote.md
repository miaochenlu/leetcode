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











