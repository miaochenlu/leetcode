## Map

```cpp
map<string, size_t> word_count;
string word;
while(cin >> word) 
  ++word_count[word];
for(const auto &w : word_count) {//const引用
  cout << w.first << " occurs " << w.second << ((w.second > 1) ? " times" : " time") << endl;
}
```



```cpp
map<string, size_t> word_count;
set<string> exclude = {"The", "But", "And", "Or", "An"
                      , "A", "the", "but", "and"}

string word;
while(cin >> word) {
  if(exclude.find(word) == exclude.end()) 
    ++word_count[word]; //说明没有在set中出现过
}

```

