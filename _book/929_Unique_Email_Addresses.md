# 929. Unique Email Addresses
Every email consists of a local name and a domain name, separated by the @ sign.  

For example, in alice@leetcode.com, alice is the local name, and leetcode.com is the domain name.  

Besides lowercase letters, these emails may contain '.'s or '+'s.  

If you add periods ('.') between some characters in the local name part of an email address, mail sent there will be forwarded to the same address without dots in the local name.  For example, "alice.z@leetcode.com" and "alicez@leetcode.com" forward to the same email address.  (Note that this rule does not apply for domain names.)  

If you add a plus ('+') in the local name, everything after the first plus sign will be ignored. This allows certain emails to be filtered, for example m.y+name@email.com will be forwarded to my@email.com.  (Again, this rule does not apply for domain names.)  

It is possible to use both of these rules at the same time.  

Given a list of emails, we send one email to each address in the list.  How many different addresses actually receive mails?   

 

Example 1:  

Input: ["test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"]
Output: 2  
Explanation: "testemail@leetcode.com" and "testemail@lee.tcode.com" actually receive mails
 

Note:  

1 <= emails[i].length <= 100  
1 <= emails.length <= 100  
Each emails[i] contains exactly one '@' character.  

for reference:  
https://leetcode.com/problems/unique-email-addresses/
  
Accepted	12 ms	9.1 MB
```c
int numUniqueEmails(char** emails, int emailsSize) {
    char totemail[100][100] = {0};
    char email[100] = {0};
    int res = 0;
    int k = 0;
    int j = 0;
    int legal = 1;
    int flag = 0;
    for(int i = 0; i < emailsSize; i++) {
        k = 0;
        j = 0;
        legal = 1;
        while(emails[i][j] != '@') {
            if(emails[i][j] == '+') legal = 0;
            else if(legal && emails[i][j] != '.')
                email[k++] = emails[i][j];
            j++;
        }
        while(emails[i][j]) {
            email[k++] = emails[i][j];
            j++;
        }
        
        email[k] = '\0';
        flag = 0;
        for(int s = 0; s < res && !flag; s++)
            if(strcmp(email, totemail[s]) == 0) {
                flag = 1;
                break;
            }

        if(flag == 0)
            strcpy(totemail[res++],email);
    }
    return res;
}
```

思路：
* 对给定的字符串，得到一个处理过'@','+'的字符串email
    * 处理'@'前
    * 处理'@'后
* 比较email和之前得到的那些字符串
    * 有相同 break
    * 不相同 拷贝进新字符串组，res+1

