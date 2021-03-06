# 字符串专题

# 1. 字符串读取

#### 1. scanf()

```cpp
char s[20];
scanf("%s", s);
printf("%s\n", s);
```

#### 2. getchar()

```cpp
#include<cstdio>

int main() {
    char c;
    while(( c = getchar())  != '\n') {
        printf("%c", c);
    }
}
```

#### 3. getline()

```
官方说明：
（1）    
istream＆getline（istream＆is，string＆str，char delim）;
istream＆getline（istream && is，string＆str，char delim）;
（2）    
istream＆getline（istream＆is，string＆str）;
istream＆getline（istream && is，string＆str）;
```

从流中获取行字符串
从is中提取字符并将它们存储到str中，直到找到分隔字符delim（或换行符，（2）中默认为'\ n'）。

is：

istream object from which characters are extracted.

str：

string object where the extracted line is stored.The contents in the string before the call (if any) are discarded and replaced by the extracted line.

例如：

第一行输入一个n，代表接下来输入n行字符串（每行字符串可以包含空格）

```
3
aa aa
bbb
ccc
```

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<string> vec;
    int n;
    cin >> n;
    cin.get();//由于输入n之后回车，使用这句回车符号吃掉，否则下面的getline()获取的第一个字符串为'\n'

    while(n--) {
        string s;
        getline(cin, s); //默认为回车符，若以其他符号为分隔符，改为getline(cin, s, ',')，例如逗号
        vec.push_back(s);       
    }
    cout<< "result: " <<endl;
    for(int i=0; i<vec.size(); ++i) {
        cout << vec.at(i) << endl;
    }
    return 0;
}
```



# 2.  字符串hash进阶

字符串hash将一个字符串S映射为一个整数，使得该整数可以尽可能唯一地代表字符串S.

一般的方法是，对只有大写字母的字符串，将字符串当作二十六进制的数，然后将其转换为十进制。str[i]表示字符串的i号位，index函数将A~Z转换为0~25。H[i]表示字符串的前i个字符的hash值

$$H[i]=H[i-1]\times 26+index(str[i])$$

但是在这个转换方式中，虽然字符串与整数一一对应，但是当字符串长度比较长时，产生的整数会非常大，没办法用一般的数据类型保存。

因此，只能舍弃一些唯一性，将产生的结果对一个整数mod取模

$$H[i]=(H[i-1]\times 26+index(str[i])) \%mod$$

但是这样可能会有多个字符串对hash值相同，导致冲突。

幸运的是，在实践中发现，在int数据范围内，如果把进制数设置为一个$10^7$级别的素数p(例如10000019), 同时把mod设置为一个$10^9$级别的素数(例如1000000007), 那么冲突的概率将会变得非常小，很难产生冲突

$$H[i]=(H[i-1])\times p+index(str[i]))\% mod$$



```cpp
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

const int MOD = 1e9 + 7;
const int P = 1e7 + 19;
vector<int> ans;

long long hashFunc(string str) {
    long long H = 0;
    for(int i = 0; i < str.length(); i++) {
        H = (H * P + str[i] - 'a') % MOD;
    }
    return H;
}

int main() {
    string str;
    while(getline(cin, str), str != "#") {
        long long id = hashFunc(str);
        ans.push_back(id);
    }
    
    sort(ans.begin(), ans.end());
    int count = 0;
    for(int i = 0; i < ans.size(); i++) {
        if(i == 0 || ans[i] != ans[i - 1]) {
            count++;
        }
    }
    cout << count << endl;
}
```

考虑求解字符串的子串的hash值，也就是求解H[i...j]。为了方便，暂时去掉求解H[i]时对mod的取模操作，散列函数如下所示

$$H[i]=H[i-1]\times p+index(str[i])$$

从进制转换的角度考虑, H[i...j]实际上等于把str[i...j]从p进制转换为十进制的结果, 也就是说

$$H[i...j]=index(str[i])\times p^{j-i}+index(str[i+1])\times p^{j-i-1}+index(str[j])\times p^0$$

然后尝试通过H[j]的散列函数来推导出H[i...j]

$$\begin{aligned}H[j]&=H[j-1]\times p+index(str[j])\\ &=(H[j-2]\times p+index(str[j-1]))\times p+index(str[j])\\&=H[j-2]\times p^2+index(str[j-1])\times p+index(str[j])\\ &=\cdots\\&=H[i-1]\times p^{j-i+1}+index(str[i])\times p^{j-i}+\cdots+index(str[j])\times p^0 \\&=H[i-1]\times p^{j-i+1}+H[i...j] \end{aligned}$$



$$H[i...j]=H[j]-H[i-1]\times p^{j-i+1}$$

因此子串str[i...j]的hash值H[i...j], 加上原来的取模操作就可以得到

$$H[i...j]=(H[j]-H[i-1]\times p^{j-i+1})\% mod$$

因为括号内部可能小于0，因此为了使结果非负，需要先对结果取模，然后加上mod后再次取模，以得到正确的结果

$$H[i...j]=((H[j]-H[i-1]\times p^{j-i+1})\%mod+mod)\%mod$$



<br>

**这里还有点问题**

接下来来看一个问题：输入两个长度均不超过1000的字符串，求他们的最长公共子串的长度。

例如字符串"ILoveYou"与"YouDontLoveMe"的最长公共子串为"Love", 因此输出4

解决这个问题，可以先分别对两个字符串的每个子串求出hash值(同时记录对应的长度)，然后找出两堆子串对应的hash值中相等的那些，就可以找到最大长度

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MOD = 10e9 + 7;
const LL P = 10e7 + 19;
const LL MAXN = 1010;
LL powP[MAXN], H1[MAXN] = {0}, H2[MAXN] = {0};
vector<pair<int, int>> pr1, pr2;

void init(int len) {
    powP[0] = 1;
    for(int i = 1; i <= len; i++) {
        powP[i] = (powP[i - 1] * P) % MOD;
    }
}
//计算字符串str的hash值
void calH(LL H[], string& str) {
    H[0] = str[0];
    for(int i = 1; i < str.length(); i++) {
        H[i] = (H[i - 1] * p + str[i]) % MOD;
    }
}

int calSingleSubH(LL H[], int i, int j) {
    if(i == 0) return H[j];
    return ((H[j] - H[i - 1] * powP[j - i + 1]) % MOD + MOD) % MOD;
}
//计算所有子串的hash值，并将<子串hash值, 子串长度>存入pr
void calSubH(LL H[], int len, vector<pair<int, int>>&pr) {
    for(int i = 0; i < len; i++) {
        for(int j = i; j < len; j++) {
            int hasValue = calSingleSubH(H, i, j);
            pr.push_back(make_pair(hashValue, j - i + 1));
        }
    }
}

//查找pr1和pr2中相同的hash值，维护
int getMax() {
    int ans = 0;
    for(int i = 0; i < pr1.size(); i++) {
        for(int j = 0; j < pr2.size(); j++) {
            if(pr[i].first == pr2[j].first) {
                ans = max(ans, pr1[i].second)
            }
        }
    }
    return ans;
}

int main() {
    string str1, str2;
    getline(cin, str1);
    getline(cin, str2);
    init(max(str1.length(), str2.length()));
    calH(H1, str1);
    calH(H2, str2);
    calSubH(H1, str1.length(), pr1);
    calSubH(H2, str2.length(), pr2);
    printf("ans = %d\n", getMax());
    return 0;
}
```

寻找最长回文子串

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MOD = 10e9 + 7;
const LL P = 10e7 + 19;
const LL MAXN = 200010;

LL powP[MAXN], H1[MAXN], H2[MAXN];

void init() {
    powP[0] = 1;
    for(int i = 1; i < MAXN; i++) {
        powP[i] = (powP[i - 1] * P) % MOD;
    }
}

void calH(LL H[], string& str) {
    H[0] = str[0];
	for(int i = 1; i < str.length(); i++) {
        H[i] = (H[i - 1] * P + str[i]) % MOD;
    }
}

void calSingleH(LL H[], int i, int j) {
    if(i == 0) return H[j];
    return ((H[j] - H[i] * powP[j - i + 1]) % MOD + MOD) % MOD;
}

int binarySearch(int l, int r, int len, int i, int isEven) {
    while(l < r) {
        int mid = (l + r) / 2;
        int H1L = i - mid + isEven, H1R = i;
        int H2L = len - 1 - (i + mid), H2R = len - 1 - (i + isEven);
        int hashL = calSingleSubH(H1, H1L, H1R);
        int hashR = calSingleSubH(H1, H2L, H2R);
        if(hashL != hashR) r = mid;
        else l = mid + 1;
        
    }
    return l - 1;
}

int main() {
    init();
    string str;
    getline(cin, str);
    calH(H1, str);
    reverse(str.begin(), str.end());
    calH(H2, str);
    int ans = 0;
    
    
    //奇回文
    for(int i = 0; i < str.length(); i++) {
        int maxLen = min(i, (int)str.length() - 1 + i) + 1;
        int k = binarySearch(0, maxLen, str.length(), i, 0);
        ans = max(ans, k * 2 + 1);
    }
    
    for(int i = 0; i < str.length(); i++) {
        int maxLen = min(i + 1, (int)str.length() - 1 - i) + 1;
        int k = binarySearch(0, maxLen, str.length(), i, 1);
        ans = max(ans, k * 2);
    }
    printf("%d\n", ans);
}
```



### KMP算法

**next数组**

假设有一个字符串`s` (下标从0开始)， 那么他以i号位作为结尾的子串就是`s[0,...,i]`。

对于这个子串来说，长度为k+1的前缀和后缀分别是`s[0,...,k]`, `s[i-k,...,i]`。

定义int型数组next, 其中`next[i]`表示使子串`s[0,...,i]`的前缀`s[0,...,k]`等于后缀`s[i-k,...,i]`的最大的k (前缀后缀可以部分重叠，但是不能是`s[0,...,i]`本身)。如果找不到相等的前后缀，就令`next[i] = -1`

`next[i]`就是子串`s[0,...,i]`的最长相等前后缀的前缀最后一位的下标。



递推法求解next数组

```cpp
void getNext(char s[], int len) {
    int j = -1;
    next[0] = -1;
    
    for(int i = 1; i < len; i++) {
        while(j != -1 && s[i] != s[j + 1]) {
            j = next[j];
        }
        if(s[i] == s[j + 1]) {
            j++;
        }
        next[i] = j;
    }
}
```



**KMP算法**

```cpp
bool KMP(char text[], char pattern[]) {
    int n = strlen(text), m = strlen(pattern); //字符串长度
    getNext(pattern, m); //计算pattern的next数组
    int j = -1;
    for(int i = 0; i < n; i++) {
        while(j != -1 && text[i] != pattern[j + 1]) {
            j = next[j];
        }
        if(text[i] == pattern[j + 1]) {
            j++;
        }
        if(j == m - 1) {
            return true;
        }
    }
    return false;
}
```



统计 pattern出现次数的KMP算法如下

```cpp
int KMP(char text[], char pattern[]) {
    int n = strlen(text), m = strlen(pattern);
    getNext(pattern, m);
    int ans = 0; //表示成功匹配次数
    int j = -1;
    
    for(int i = 0; i < n; i++) {
        while(j != -1 && text[i] != pattern[j + 1]) {
            j = next[j];
        }
        if(text[i] == pattern[j + 1]) {
            j++;
        }
        if(j == m - 1) {
            ans++;			//成功匹配次数+1
            j = next[j];	//让j回退到next[j]继续匹配
        }
    }
    return ans;	//返回成功匹配次数
}
```



这块还不是很懂。

```cpp
void getNextval(char s[], int len) {
    int j = -1;
    nextval[0] = -1;
    
    for(int i = 1; i < len; i++) {
        while(j != -1 && s[i] != s[j + 1]) {
            j = nextval[j];
        }
        if(s[i] == s[j + 1]) {
            j++;
        }
        if(j == -1 || s[i + 1] != s[j + 1]) {
            nextval[i] = j;
        } else {
            nextval[i] = nextval[j];
        }
    }
}
```



