# 804. Unique Morse Code Words
International Morse Code defines a standard encoding where each letter is mapped to a series of dots and dashes, as follows: "a" maps to ".-", "b" maps to "-...", "c" maps to "-.-.", and so on.  

For convenience, the full table for the 26 letters of the English alphabet is given below:  

[".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."]  
Now, given a list of words, each word can be written as a concatenation of the Morse code of each letter. For example, "cba" can be written as "-.-..--...", (which is the concatenation "-.-." + "-..." + ".-"). We'll call such a concatenation, the transformation of a word.  

Return the number of different transformations among all words we have.  

Example:  
Input: words = ["gin", "zen", "gig", "msg"]  
Output: 2  
Explanation:   
The transformation of each word is:  
"gin" -> "--...-."  
"zen" -> "--...-."  
"gig" -> "--...--."  
"msg" -> "--...--."  

There are 2 different transformations, "--...-." and "--...--.".  
Note:  

The length of words will be at most 100.  
Each words[i] will have length in range [1, 12].  
words[i] will only consist of lowercase letters.  

Accepted	4 ms	7.4 MB
```c
int uniqueMorseRepresentations(char** words, int wordsSize) {
    char trans[100][60];
    int res = 0;
    char morse[27][6] = 
    {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
    char tmp[70];
    for(int i = 0; i < wordsSize; i++) {
        int k = 0;
        int j = 0;
        while(words[i][j]) {
            for(int t = 0; morse[words[i][j] - 'a'][t]; t++)
                tmp[k++] = morse[words[i][j] - 'a'][t];
            j++;
        }
        tmp[k] = 0;
        int sameflag = 0;
        for(int s = 0; s < res; s++)
            if(strcmp(tmp, trans[s]) == 0) {
                sameflag = 1;
                break;
            }
        if(!sameflag) 
            strcpy(trans[res++], tmp);
    }
    return res;
}
```

解题思路非常类似于929. Unique Email Addresses
* 对于给定的字符串，得到它的morse code
* 与前面的Morse code比较
    * 有相同 不做操作
    * 无相同 新字符串加一