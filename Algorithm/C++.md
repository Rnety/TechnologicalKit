## 字符串

### 1.**HJ1** **字符串最后一个单词的长度**

**描述**:

计算字符串最后一个单词的长度，单词以空格隔开，字符串长度小于5000。（注：字符串末尾不以空格为结尾）

**输入描述**：

输入一行，代表要计算的字符串，非空，长度小于5000。

**输出描述**：

输出一个整数，表示输入字符串最后一个单词的长度。

```c++
#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    string s;
    int pos(-1); 
    
    getline(cin, s);
    pos=s.find_last_of(' ');
    cout << s.length() - pos - 1 << endl;
}
```

### 2. **HJ2** **计算某字符出现次数**

**描述**

写出一个程序，接受一个由字母、数字和空格组成的字符串，和一个字符，然后输出输入字符串中该字符的出现次数。（不区分大小写字母）

数据范围：  1≤*n*≤1000 

**输入描述：**

第一行输入一个由字母、数字和空格组成的字符串，第二行输入一个字符。（保证该字符不为空格）

**输出描述：**

输出输入字符串中含有该字符的个数。（不区分大小写字母）

```c
#include <cctype>
#include <cstdio>
#include <iostream>
using namespace std;

int main() {
    string s;
    getline(cin, s);
    char a;
    a = getchar();
    int num(0);
    for (int i = 0; i < s.size(); i++) {
        if (islower(s[i])) s[i] = toupper(s[i]);
    }

    if (islower(a)) {
        a = toupper(a);
    }
    for (int i = 0; i < s.size(); i++) {
        if (a == s[i]) num++;
    }
    cout << num << endl;
    return 0;
}
```

### 3. **HJ4** **字符串分隔**

**描述**

输入一个字符串，请按长度为8拆分每个输入字符串并进行输出。

长度不是8整数倍的字符串请在后面补数字0，空字符串不处理。

**输入描述**：

连续输入字符串(每个字符串长度小于等于100)。

**输出描述**：

依次输出所有分割后的长度为8的新字符串。

```c++
#include <iostream>
using namespace std;

int main() {
    string s;
    getline(cin, s);
    
    while (s.length() % 8) s.push_back('0'); //长度不是8整数倍的字符串请在后面补数字0，只对最后一个不满足长度的字符串处理。
    if (s.length() == 0) return 0;
    for (int i = 0; i < s.size(); ++i) {
        cout << s[i]; //再分割
        if (i % 8 == 7) {
            cout << endl;
        }
    }
}
```



### 4. **HJ5** **进制转换**

**描述**

写出一个程序，接受一个十六进制的数，输出该数值的十进制表示。

数据范围：保证结果在 1≤*n*≤231−1 

**输入描述**：

输入一个十六进制的数值字符串。

**输出描述**：

输出该数值的十进制字符串。不同组的测试用例用\n隔开。

```c++
#include <cctype>
#include <iostream>
using namespace std;

int main() {
    string s;
    while (cin >> s) {
        int ans(0);
        for (int i = 2; i < s.length(); i++) { //16进制前两个字符是Ox或者ox
            if (isdigit(s[i])) {
                ans = ans * 16 + s[i] - '0'; //数字则0-9，ans*16代表左移一位(和二进制一样每左移一位*2，计组概念)
            } else {
                ans = ans * 16 + 10 + s[i] - 'A'; //字母则10-15，ans*16代表左移一位
            }
        }
        cout<<ans<<endl;
    }
}
```

>1、

### 5. **HJ10** **字符个数统计**

**描述**

编写一个函数，计算字符串中含有的不同字符的个数。字符在 ASCII 码范围内( 0~127 ，包括 0 和 127 )，换行表示结束符，不算在字符里。不在范围内的不作统计。多个相同的字符只计算一次

例如，对于字符串 abaca 而言，有 a、b、c 三种不同的字符，因此输出 3 。

数据范围：  1≤*n*≤500 

**输入描述**：

输入一行没有空格的字符串。

**输出描述**：

输出 输入字符串 中范围在(0~127，包括0和127)字符的种数。

```c
#include <iostream>
#include <map>
using namespace std;

int main() {
    string s;
    int ans(0);
    map<char, int> cnt;
   
    getline(cin, s); 
    for (auto c : s) {
        cnt[c]++;
    }
    cout << cnt.size() << endl;
}
```

### 6. **HJ11** **数字颠倒**/**字符串反转**

**描述**

输入一个整数/字符串，将这个整数以字符串的形式逆序输出

程序不考虑负数的情况，若数字含有0，则逆序形式也含有0，如输入为100，则输出为001

数据范围：  0≤*n*≤230−1 

**输入描述**：

输入一个int整数/string字符串

**输出描述**：

将这个整数以字符串的形式逆序输出

```c++
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    string s;
    getline(cin, s);
    reverse(s.begin(), s.end()); //reverser()、begin()、end()的应用
    cout << s << endl;
}
```

### 7. **HJ14** **字符串排序**

**描述**

给定 n 个字符串，请对 n 个字符串按照字典序排列。

数据范围： 1≤*n*≤1000 ，字符串长度满足  1≤len≤100 

**输入描述**：

输入第一行为一个正整数n(1≤n≤1000),下面n行为n个字符串(字符串长度≤100),字符串中只含有大小写字母。

**输出描述**：

数据输出n行，输出结果为按照字典序排列的字符串。

```c++
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    string str;
    vector<string> cur; //设立字符串数组

    while (cin >> n) {
        while (n--) {
            cin >> str;
            cur.push_back(str);
        }
        sort(cur.begin(), cur.end()); //逆转字符串数组，sort默认是字典
        for (auto x : cur) {
            cout << x << endl;
        }
    }
}
```

### 8. **HJ23** **删除字符串中出现次数最少的字符**

**描述**:

实现删除字符串中出现次数最少的字符，若出现次数最少的字符有多个，则把出现次数最少的字符都删除。输出删除这些单词后的字符串，字符串中其它字符保持原来的顺序。

数据范围：输入的字符串长度满足 1≤*n*≤20 ，保证输入的字符串中仅出现小写字母

**输入描述**：

字符串只包含小写英文字母, 不考虑非法输入，输入的字符串长度小于等于20个字节。

**输出描述**：

删除字符串中出现次数最少的字符后的字符串。

```c++
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

int main() {
    map<char, int> cnt;
    string s;
    cin >> s;
    for (auto c : s) cnt[c]++;
    int mn(s.length());
    for (auto x : cnt) {
        mn = min(mn, x.second);
    }
    for (auto c : s) {
        if (cnt[c] == mn)continue;
        cout << c;
    }
}

```

### 9. **HJ31** **单词倒排**

**描述**

对字符串中的所有单词进行倒排。

**说明**：

1、构成单词的字符只有26个大写或小写英文字母；

2、非构成单词的字符均视为单词间隔符；

3、要求倒排后的单词间隔符以一个空格表示；如果原字符串中相邻单词间有多个间隔符时，倒排转换后也只允许出现一个空格间隔符；

4、每个单词最长20个字母；

数据范围：字符串长度满足  1≤*n*≤10000 

**输入描述**：

输入一行，表示用来倒排的句子

**输出描述**：

输出句子的倒排结果

```c++
#include <cctype>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int main() {
    string s;
    vector<string> word;
    getline(cin, s);
    for (int i = 0; i < s.length(); i++) { //把非字母字符变为空格
        if (!isalpha(s[i]))
            s[i] = ' ';
    }
    stringstream input{s}; //初始化stringstream
    while (input >> s) { //分割
        word.push_back(s);
    }
    for (int i = word.size() - 1; i > 0; i--) {
        cout << word[i] << ' ';
    }
    cout << word[0];
}
```

> 总结：
>
> 1、使用`stringstream`类读入字符串，会自动忽略空白字符。常用于处理输入分割的问题，`getline`函数也可以，但是如本题中需要对输入的字符串进行处理后才进行分割的时候，需要使用到`stringstream`类。
>
> 2、多种类型的分割转化为一种类型的分割。

### 10. **HJ34** **图片整理**

**描述**:

Lily上课时使用字母数字图片教小朋友们学习英语单词，每次都需要把这些图片按照大小（ASCII码值从小到大）排列收好。请大家给Lily帮忙，通过代码解决。

Lily使用的图片使用字符"A"到"Z"、"a"到"z"、"0"到"9"表示。

数据范围：每组输入的字符串长度满足  1≤*n*≤1000 

**输入描述**：

一行，一个字符串，字符串中的每个字符表示一张Lily使用的图片。

**输出描述**：

Lily的所有图片按照从小到大的顺序输出

```c++
#include <iostream>
#include <string>
#include <algorithm>
using  namespace std;
 
int main(){
    string data;
    while(cin>>data)
    {
        sort(data.begin(),data.end());
        cout<<data<<endl;
    }   
    return 0;
}
```



### 11. **HJ21** **简单密码**（HJ29）

**描述**

现在有一种密码变换算法。

九键手机键盘上的数字与字母的对应： 1--1， abc--2, def--3, ghi--4, jkl--5, mno--6, pqrs--7, tuv--8 wxyz--9, 0--0，把密码中出现的小写字母都变成九键键盘对应的数字，如：a 变成 2，x 变成 9.

而密码中出现的大写字母则变成小写之后往后移一位，如：X ，先变成小写，再往后移一位，变成了 y ，例外：Z 往后移是 a 。

数字和其它的符号都不做变换。

数据范围： 输入的字符串长度满足 1≤*n*≤100 

**输入描述**：

输入一组密码，长度不超过100个字符。

**输出描述**：

输出密码变换后的字符串

```c++
#include <cctype>
#include <iostream>
using namespace std;

int main() {
    string str;
    string a{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"};
    string b{"22233344455566677778889999bcdefghijklmnopqrstuvwxyza0123456789"};

    cin >> str;
    for (int i = 0; i < str.size(); i++) {
        str[i] = b[a.find(str[i])];
    }
    cout << str << endl;
}
```

### 12. **HJ40** **统计字符**

**描述**

输入一行字符，分别统计出包含英文字母、空格、数字和其它字符的个数。

数据范围：输入的字符串长度满足 1≤*n*≤1000 

**输入描述**：

输入一行字符串，可以有空格

**输出描述**：

统计其中英文字符，空格字符，数字字符，其他字符的个数

```c++
#include <cctype>
#include <iostream>
using namespace std;

int main() {
    string s;
    getline(cin, s);
    int n(0), m(0), i(0), j(0);
    for (auto x : s) {
        if (isdigit(x)) {
            n++;
            continue;
        }
        if (isalpha(x)) {
            m++;
            continue;
        }
        if (x == ' ') {
            i++;
            continue;
        }
        j++;
    }
    cout << m << endl << i << endl << n << endl << j << endl;
}
```

### 13.**HJ106** **字符逆序**

**描述**

将一个字符串str的内容颠倒过来，并输出。

数据范围：1≤*l**e**n*(*s**t**r*)≤10000 

**输入描述**：

输入一个字符串，可以有空格

**输出描述**：

输出逆序的字符串

```c++
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    string s;
    getline(cin, s);
    reverse(s.begin(), s.end());
    cout << s;
}
```

### 14. **HJ102** **字符统计**

**描述**

输入一个只包含小写英文字母和数字的字符串，按照不同字符统计个数由多到少输出统计结果，如果统计的个数相同，则按照ASCII码由小到大排序输出。

数据范围：字符串长度满足  1≤`len(str)`≤1000 

**输入描述**：

一个只包含小写英文字母和数字的字符串。

**输出描述**：

一个字符串，为不同字母出现次数的降序表示。若出现次数相同，则按ASCII码的升序输出。

```c++
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;


int main() {
    string s;
    map<char, int> mp; //哈希表,索引为char，值为int
    while (cin >> s) {
        mp.clear();
        for (char c : s) {
            ++mp[c];
        }
    }
    vector<pair<char, int>> vec(mp.begin(), mp.end()); //迭代器
    stable_sort(vec.begin(), vec.end(), [](const pair<char, int>& a,
    const pair<char, int>& b) {
        return a.second > b.second;
    });
    for (auto iter = vec.begin(); iter < vec.end(); ++iter) {
        cout << iter->first;
    }
    cout << endl;
}
```

### 15. **HJ96** **表示数字**

**描述**

将一个字符串中所有的整数前后加上符号“*”，其他字符保持不变。连续的数字视为一个整数。

数据范围：字符串长度满足1≤*n*≤100 

**输入描述**：

输入一个字符串

**输出描述**：

字符中所有出现的数字前后加上符号“*”，其他字符保持不变

```c++
#include <cctype>
#include <iostream>
using namespace std;

int main() {
    string s;
    while (cin >> s)
        for (int i = 0; i < s.length(); i++) {
            if (isdigit(s[i])) {
                s.insert(i, "*");
                i++;
                while (isdigit(s[i])) {
                    i++;
                }
                s.insert(i, "*");
            }
        }
    cout << s << endl;
}
```

### 16. **HJ84** **统计大写字母个数**

**描述**

找出给定字符串中大写字符(即'A'-'Z')的个数。

数据范围：字符串长度：1≤∣*s*∣≤250 

字符串中可能包含空格或其他字符

**输入描述**：

对于每组样例，输入一行，代表待统计的字符串

**输出描述**：

输出一个整数，代表字符串中大写字母的个数

```c++
#include <cctype>
#include <iostream>
using namespace std;

int main() {
    string s;
    getline(cin, s);
    int num(0);
    for (auto x : s) {
        if (isalpha(x) && isupper(x)) {
            num++;
        }
    }
    cout<<num<<endl;
}
```

### 17. **HJ66** **配置文件恢复**

**描述**:

有6条配置命令，它们执行的结果分别是：

| **命  令**           | **执  行**      |
| -------------------- | --------------- |
| **reset**            | reset what      |
| **reset board**      | board fault     |
| **board add**        | where to add    |
| **board delete**     | no board at all |
| **reboot backplane** | impossible      |
| **backplane abort**  | install first   |
| ***he he***          | unknown command |

**注意：he he不是命令。**

为了简化输入，方便用户，以“最短唯一匹配原则”匹配（注：需从首字母开始进行匹配）：

1、若只输入一字串，则只匹配一个关键字的命令行。例如输入：r，根据该规则，匹配命令reset，执行结果为：reset what；输入：res，根据该规则，匹配命令reset，执行结果为：reset what；
2、若只输入一字串，但匹配命令有两个关键字，则匹配失败。例如输入：reb，可以找到命令reboot backpalne，但是该命令有两个关键词，所有匹配失败，执行结果为：unknown command

3、若输入两字串，则先匹配第一关键字，如果有匹配，继续匹配第二关键字，如果仍不唯一，匹配失败。

例如输入：r b，找到匹配命令reset board 和 reboot backplane，执行结果为：unknown command。

例如输入：b a，无法确定是命令**board add**还是**backplane abort**，匹配失败。

4、若输入两字串，则先匹配第一关键字，如果有匹配，继续匹配第二关键字，如果唯一，匹配成功。例如输入：bo a，确定是命令**board add**，匹配成功。
5、若输入两字串，第一关键字匹配成功，则匹配第二关键字，若无匹配，失败。例如输入：b addr，无法匹配到相应的命令，所以执行结果为：unknow command。
6、若匹配失败，打印“unknown command”

注意：有多组输入。

数据范围：数据组数： 1≤*t*≤800 ，字符串长度 1≤*s*≤20 

进阶：时间复杂度：O*(*n*) ，空间复杂度：O*(*n*) 

**输入描述**：

多行字符串，每行字符串一条命令

**输出描述**：

执行结果，每条命令输出一行





```c++
#include <algorithm>
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

int main() {
    string str; //要输入的字符串
    string single = "reset"; //单字符串命令
    vector<vector<string>> tp1 = {{"reset", "board", "board fault"},  //双字符串命令
                                  {"board", "add", "where to add"}, 
                                  {"board", "delete", "no board at all"},
                                  {"reboot", "backplane", "impossible"}, 
                                  {"backplane", "abort", "install first"}};

    while (getline(cin, str)) { //输入
        int n = count(str.begin(), str.end(),' '); //统计字符串中有多少个空格
        if (n == 0) { //只输入一字串
            if (single.find(str) == 0) { //与单字符串命令匹配返回出现该字符串的下标，为0才是首字母匹配
                cout << "reset what" << endl;
            } else {
                cout << "unknown command" << endl;
            }
        } else {
            int l = str.find(' '); //返回空格所在的下标
            string s1 = str.substr(0, l); //从0开始复制长度为l的字符串
            string s2 = str.substr(l + 1, str.length() - l - 1);//从l+1开始复制长度为str.length() - l - 1的字符串
            int count(0);
            string ans;
            for (int i = 0; i < 5; i++) {
                if (tp1[i][0].find(s1) == 0 && tp1[i][1].find(s2) == 0) {
                    count++;
                    ans = tp1[i][2];
                }

            }
            if (count == 1) {
                cout << ans << endl;
            } else {
                cout << "unknown command" << endl;
            }
        }

    }
return 0;
    }
```

### 18. **HJ26** **字符串排序**(中等)

**描述**:

编写一个程序，将输入字符串中的字符按如下规则排序。

规则 1 ：英文字母从 A 到 Z 排列，不区分大小写。

如，输入： `Type` 输出： `epTy`

规则 2 ：同一个英文字母的大小写同时存在时，按照输入顺序排列。

如，输入： `BabA` 输出： `aABb`

规则 3 ：非英文字母的其它字符保持原来的位置。



如，输入： `By?e` 输出： `Be?y`

数据范围：输入的字符串长度满足 1≤�≤1000 1≤*n*≤1000 



**输入描述**：

输入字符串

**输出描述**：

输出字符串

```c++
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sys/ucontext.h>
#include <vector>
using namespace std;

int main() {
    string str; //定义字符串

    while (getline(cin, str)) {
        vector<char> vec;
        vec.clear();
        int len = str.size(); //字符串长度
        for (int j = 0; j < 26; j++) { //按字典进行排序
            for (int i = 0; i < len; i++) {
                if (str[i] - 'A' == j || str[i] - 'a' == j) {
                    vec.push_back(str[i]);
                }
            }
        }

        for (int i = 0, k = 0; (i < len) && (k < vec.size()) ; i++) { //插入非字符
            if (isalpha(str[i])) {
                str[i] = vec[k++];
            }
        }
        cout << str;
    }

}

```

### 19. **HJ27** **查找兄弟单词**（中等）

**描述**

定义一个单词的“兄弟单词”为：交换该单词字母顺序（注：可以交换任意次），而不添加、删除、修改原有的字母就能生成的单词。

兄弟单词要求和原来的单词不同。例如： ab 和 ba 是兄弟单词。 ab 和 ab 则不是兄弟单词。

现在给定你 n 个单词，另外再给你一个单词 x ，让你寻找 x 的兄弟单词里，按字典序排列后的第 k 个单词是什么？

注意：字典中可能有重复单词。

数据范围：1≤*n*≤1000 ，输入的字符串长度满足  1≤`len(str)`≤10 

**输入描述**：

输入只有一行。 先输入字典中单词的个数n，再输入n个单词作为字典单词。 然后输入一个单词x 最后后输入一个整数k

**输出描述**：

第一行输出查找到x的兄弟单词的个数m 第二行输出查找到的按照字典顺序排序后的第k个兄弟单词，没有符合第k个的话则不用输出。

```c++
#include <asm-generic/errno.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    string str;
    vector<string> vstr; 
    vector<string> vbro; //设置两个vector而不是在一个vector中删除元素
    while (cin >> n) {
        vstr.clear();
        vbro.clear();
        while (n--) {
            cin >> str;
            vstr.push_back(str);
        }
        cin >> str >> m;
        string s1 = str;
        sort(s1.begin(), s1.end());

        vector<string>::iterator itr; // 相对于auto itr = vstr.begin() 更规范的写法
        for (itr = vstr.begin(); itr < vstr.end(); itr++) {
            if ((*itr).length() == str.length() && (*itr) != str) { //类似于指针的指向和实值表示
                string tmp = *itr;
                sort(tmp.begin(), tmp.end());
                if (tmp == s1) {
                    vbro.push_back(*itr);
                }
            }
        }
        sort(vbro.begin(), vbro.end());
        cout << vbro.size() << endl;
        if (vbro.size() >= m) {
            cout << vbro[m - 1];
        }
    }
}
```

### 20. **HJ29** **字符串加解密**(中等)

**描述**:

对输入的字符串进行加解密，并输出。

加密方法为：

当内容是英文字母时则用该英文字母的后一个字母替换，同时字母变换大小写,如字母a时则替换为B；字母Z时则替换为a；

当内容是数字时则把该数字加1，如0替换1，1替换2，9替换0；

其他字符不做变化。

解密方法为加密的逆过程。

数据范围：输入的两个字符串长度满足 1≤*n*≤1000 ，保证输入的字符串都是只由大小写字母或者数字组成

**输入描述**：

第一行输入一串要加密的密码
第二行输入一串加过密的密码

**输出描述**：

第一行输出加密后的字符
第二行输出解密后的字符

```c++
#include <cctype>
#include <iostream>
using namespace std;

int main() {
    string str1, str2;
    cin >> str1 >> str2;
    string a{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"};
    string b{"BCDEFGHIJKLMNOPQRSTUVWXYZAbcdefghijklmnopqrstuvwxyza1234567890"};
   for (int i=0;i<str1.size();i++) {
   str1[i]= b[a.find(str1[i])];
   }
    for (int i=0;i<str2.size();i++) {
   str2[i]= a[b.find(str2[i])];
   }
   cout<<str1<<endl<<str2;
}
```

### 21. **HJ92** **在字符串中找出连续最长的数字串**(中等)

**描述**：

输入一个字符串，返回其最长的数字子串，以及其长度。若有多个最长的数字子串，则将它们全部输出（按原字符串的相对位置）

本题含有多组样例输入。

数据范围：字符串长度  1≤*n*≤200 ， 保证每组输入都至少含有一个数字

**输入描述**：

输入一个字符串。1<=`len`(字符串)<=200

**输出描述**：

输出字符串中最长的数字字符串和它的长度，中间用逗号间隔。如果有相同长度的串，则要一块儿输出（中间不要输出空格）。

```c++
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    string str;
    vector<string> digitalstr;
    while (getline(cin, str)) {
        digitalstr.clear();
        int len(0);
        int maxlen(-1);
        int ans(-1);

        string tmp;
        for (auto c : str) {
            if (isdigit(c)) { 
                tmp.push_back(c); 
                len++; 
            } else {
                if (len) {
                    len = 0;
                    digitalstr.push_back(tmp);
                    tmp.clear();
                }
            }
        }
        if (len) {
            digitalstr.push_back(tmp);
            tmp.clear();
        }
        vector<string>:: iterator iter1, iter2;
        for (iter1 = digitalstr.begin(); iter1 < digitalstr.end(); ++iter1) {
            len = (*iter1).size();
            if (maxlen < len) {
                maxlen = len;
                tmp = *iter1;
            } else if (maxlen == len) {
                tmp = tmp + (*iter1);
            }
        }
        cout << tmp << ',' << maxlen << endl;

    }

}
```

### 22.**HJ17** **坐标移动**(中等)

**描述**：

开发一个坐标计算工具， A表示向左移动，D表示向右移动，W表示向上移动，S表示向下移动。从（0,0）点开始移动，从输入字符串里面读取一些坐标，并将最终输入结果输出到输出文件里面。

输入：

合法坐标为A(或者D或者W或者S) + 数字（两位以内）

坐标之间以;分隔。

非法坐标点需要进行丢弃。如AA10; A1A; $%$; YAD; 等。

下面是一个简单的例子 如：

A10;S20;W10;D30;X;A1A;B10A11;;A10;

处理过程：

起点（0,0）

\+  A10  = （-10,0）

\+  S20  = (-10,-20)

\+  W10 = (-10,-10)

\+  D30 = (20,-10)

\+  x  = 无效

\+  A1A  = 无效

\+  B10A11  = 无效

\+ 一个空 不影响

\+  A10 = (10,-10)

结果 （10， -10）

数据范围：每组输入的字符串长度满足 1≤*n*≤10000 ，坐标保证满足 − −231≤*x*,*y*≤231−1 ，且数字部分仅含正数

**输入描述**：

一行字符串

**输出描述**：

最终坐标，以逗号分隔

```c++
#include <cctype>
#include <iostream>
#include <map>
using namespace std;
bool Num(string str) {
    for (auto c : str) {
        if (isdigit(c)) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}
int main() {
    string s;
    pair<int, int> p(0, 0);
    while (getline(cin, s, ';')) { //使用getline以';'分割输入
        if (s.empty()) continue;
        string s1 = s.substr(1); //复制s下标为1到末尾的字符串到s1中
        if (Num(s1) && s1.size() <= 2) {
            switch (s[0]) {
                case 'A':
                    p.first -= stoi(s1); //把string转换为int
                    break;
                case 'D':
                    p.first += stoi(s1);
                    break;
                case 'W':
                    p.second += stoi(s1);
                    break;
                case 'S':
                    p.second -= stoi(s1);
                    break;
                default:
                    break;
            }
        }
    }
    cout << p.first << ',' << p.second;
}
```

>总结：
>
>1、使用`getline`函数以``;'`分割输入。
>
>2、`substr`函数的应用。
>
>3、`stoi(const *string)`是把`string`转换为`int`，或者用`atoi(const *char)`进行转化，但是由于`atoi`参数为`const *char`因此要使用`c_str()`函数，即假设有字符串`s`，则`stoi(s)`或者`atoi(s.c_str())`把`string`转换为`int`。
>
>4、`pair`容器的应用。

### 23. **HJ36** **字符串加密**(中等)

**描述**

有一种技巧可以对数据进行加密，它使用一个单词作为它的密匙。下面是它的工作原理：首先，选择一个单词作为密匙，如TRAILBLAZERS。如果单词中包含有重复的字母，只保留第1个，将所得结果作为新字母表开头，并将新建立的字母表中未出现的字母按照正常字母表顺序加入新字母表。如下所示：

A B C D E F G H I J K L M N O P Q R S T U V W X Y Z

T R A I L B Z E S C D F G H J K M N O P Q U V W X Y (实际需建立小写字母的字母表，此字母表仅为方便演示）

上面其他用字母表中剩余的字母填充完整。在对信息进行加密时，信息中的每个字母被固定于顶上那行，并用下面那行的对应字母一一取代原文的字母(字母字符的大小写状态应该保留)。因此，使用这个密匙， Attack AT DAWN (黎明时攻击)就会被加密为Tpptad TP ITVH。

请实现下述接口，通过指定的密匙和明文得到密文。

数据范围：保证输入的字符串中仅包含小写字母

**输入描述**：

先输入key和要加密的字符串

**输出描述**：

返回加密后的字符串

```c++
#include <cctype>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    string key, word;
    while (cin >> key >> word) {
        vector<char> cnt;
        vector<bool> flag(26, true);
        for (int i = 0; i < key.size(); i++) {
            key[i] = toupper(key[i]);
            if (flag[key[i] - 'A']) {
                flag[key[i] - 'A'] = false;
                cnt.push_back(key[i]);
            }
        }
        for (char c = 'A'; c <= 'Z'; c++) {
            if (flag[c - 'A']) {
                flag[c - 'A'] = false;
                cnt.push_back(c);
            }
        }
        string output;
        for (int i = 0; i < word.size(); i++) {
            if (islower(word[i])) {
                output += cnt[word[i] - 'a'] + 32;
            } else {
                output += cnt[word[i] - 'A'];
            }
        }
        cout << output << endl;
    }

}
```

> 总结：
>
> 1、把`key`转化为大写，再利用`vector<bool> flag(26, true)`定义26字符是否被使用，`key[i] - 'A'`转化`key`字符与26字母字符下标的对应关系。
>
> 2、再利用`vector<bool> flag(26, true)`定义26字符是否被使用后假如字母表。
>
> 3、加密`word`如果是小写则`word[i] - 'a'`转化为字母表中元素再加`32`还原为小写，否则`word[i] - 'A'`。





### 24.**HJ45** **名字的漂亮度**(中等)

**描述**

给出一个字符串，该字符串仅由小写字母组成，定义这个字符串的“漂亮度”是其所有字母“漂亮度”的总和。
每个字母都有一个“漂亮度”，范围在1到26之间。没有任何两个不同字母拥有相同的“漂亮度”。字母忽略大小写。

给出多个字符串，计算每个字符串最大可能的“漂亮度”。

本题含有多组数据。

数据范围：输入的名字长度满足 1≤*n*≤10000 



**输入描述**：

第一行一个整数N，接下来N行每行一个字符串

**输出描述**：

每个字符串可能的最大漂亮程度

```c++
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    while (n--) {
        string str;
        cin >> str;
        vector<int> cnt(26, 0);
        for (auto c : str) {
            if (isupper(c)) c = tolower(c);
            cnt[c - 'a']++;
        }
        sort(cnt.begin(), cnt.end(), greater<int>());
        int ans(0), m(26);
        for (auto c : cnt) {
            if (c) {
                ans += c * (m--);
            } else {
                break;
            }
        }
        cout << ans << endl;
    }
}
```

### 25. **HJ46** **截取字符串**

**描述**：

输入一个字符串和一个整数 k ，截取字符串的前k个字符并输出

数据范围：字符串长度满足 1≤*n*≤1000 ，1≤*k*≤*n* 

**输入描述**：

1.输入待截取的字符串

2.输入一个正整数k，代表截取的长度

**输出描述**：

截取后的字符串

```c++
#include <iostream>
#include <string>
using namespace std;

int main() {
    string str;
    int n;
    cin>>str>>n;
    str=str.substr(0,n);
    cout<<str<<endl;
}
```

### 26. **HJ57** **高精度整数加法**(中等)

**描述**

输入两个用字符串 str 表示的整数，求它们所表示的数之和。

数据范围：  1≤`len(str)`≤10000 

**输入描述**：

输入两个字符串。保证字符串只含有'0'~'9'字符

**输出描述**：

输出求和后的结果

```c++
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    string s1, s2;
    vector<int> cnt;
    cin>>s1>>s2;

    reverse(s1.begin(), s1.end());
    reverse(s2.begin(), s2.end());

    int temp(0);

    for (int i = 0, j = 0; i < s1.size() && j < s2.size(); i++,j++) {
        cnt.push_back((s1[i]-'0' + s2[j]-'0'+ temp) % 10);
        if (s1[i]-'0' + s2[j]-'0'+ temp >= 10) {
            temp = 1;
        } else {
            temp = 0;
        }
    }
    if (s1.size() > s2.size()) {
        for (int i = s2.size(); i < s1.size(); i++) {
            cnt.push_back((s1[i] -'0'+ temp) % 10);
            if (s1[i]-'0' + temp >= 10) {
                temp = 1;
            } else {
                temp = 0;
            }
        }
    } else {
        for (int i = s1.size(); i < s2.size(); i++) {
            cnt.push_back((s2[i]-'0' + temp) % 10);
            if (s2[i]-'0' + temp >= 10) {
                temp = 1;
            } else {
                temp = 0;
            }
        }
    }
    if(temp) cnt.push_back(1);
    reverse(cnt.begin(),cnt.end());
    for(auto c:cnt){
        cout<<c;
    }
}
```

>
>
>

### 27. **HJ59** **找出字符串中第一个只出现一次的字符**(中等)

**描述**

找出字符串中第一个只出现一次的字符

数据范围：输入的字符串长度满足 1≤�≤1000 1≤*n*≤1000 



**输入描述**：

输入一个非空字符串

**输出描述**：

输出第一个只出现一次的字符，如果不存在输出-1

```c++
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

int main() {
    string s;
    map<char, int> cnt;

    cin >> s;
    int min = s.size();
    int n;

    for (auto c : s) {
        cnt[c]++;
    }
    for (auto c : cnt) {
        if (c.second == 1) {
            n = s.find_first_of(c.first);
            if (n <= min) {
                min = n;
            }
        }
    }
    if (min == s.size()) {
        cout << -1;
    } else
    {
        cout << s[min];
    }
}
```

### 28. **HJ73** **计算日期到天数转换**

**描述**

根据输入的日期，计算是这一年的第几天。

保证年份为4位数且日期合法。

进阶：时间复杂度： *O*(*n*) ，空间复杂度： *O*(1) 

**输入描述**：

输入一行，每行空格分割，分别是年，月，日

**输出描述**：

输出是这一年的第几天

```c++
#include <iostream>
using namespace std;

int main() {
    int year, month, day;
    int data[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int sum(0);

    while (cin >> year >> month >> day) { 
        
        for(int i=0;i<month-1;i++){
            sum+=data[i];
        }
        if(((year%400==0) || (year%4==0&&year%100!=0)) && month>2)
            sum+=day+1;
            else{
                sum+=day;
            }
            cout<<sum<<endl;
    }
}
```

### 29. **HJ74** **参数解析**（中等）

**描述**:

在命令行输入如下命令：

xcopy /s c:\\ d:\\e，

各个参数如下：

参数1：命令字xcopy

参数2：字符串/s

参数3：字符串c:\\

参数4: 字符串d:\\e

请编写一个参数解析程序，实现将命令行各个参数解析出来。



解析规则：

1.参数分隔符为空格
2.对于用""包含起来的参数，如果中间有空格，不能解析为多个参数。比如在命令行输入xcopy /s "C:\\program files" "d:\"时，参数仍然是4个，第3个参数应该是字符串C:\\program files，而不是C:\\program，注意输出参数时，需要将""去掉，引号不存在嵌套情况。
3.参数不定长

4.输入由用例保证，不会出现不符合要求的输入

数据范围：字符串长度：1≤�≤1000 1≤*s*≤1000 

进阶：时间复杂度：*O*(*n*) ，空间复杂度：O*(*n) 

**输入描述**：

输入一行字符串，可以有空格

**输出描述**：

输出参数个数，分解后的参数，每个参数都独占一行

```c++
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    string str, tmp;
    int flag;
    vector<string> cnt;

    while (getline(cin, str, ' ')) {
        if (flag) {
            if (str.find('\"') == -1) {
                tmp += ' ' + str;
            } else {
                tmp += ' ' + str.substr(0, str.size() - 1);
                cnt.push_back(tmp);
                flag = 0;
                tmp.clear();
            }
        } else if (str[0] == '\"') {
            if (count(str.begin(), str.end(), '\"') != 1) {
                tmp += str.substr(1, str.size() - 2);
                cnt.push_back(tmp);
                flag = 0;
                tmp.clear();
            } else {
                flag = 1;
                tmp += str.substr(1, str.size() - 1);
            }
        } else {
            cnt.push_back(str);
        }
    }
    cout << cnt.size() << endl;
    for (int i=0; i<cnt.size()-1; i++) {
        cout<<cnt[i]<<endl;
    }
    tmp = cnt[cnt.size()-1];
    tmp = tmp.substr(0,tmp.size()-1);
    cout<<tmp;
}
```

> 总结：
>
> 1、在`getline(cin, str, ' ')`用法中，换行`\n`也会被读入到`str`当中，因此要额外处理最后一个元素。

### 30. **HJ81** **字符串字符匹配**

**描述**

判断短字符串S中的所有字符是否在长字符串T中全部出现。

请注意本题有多组样例输入。

数据范围: 1≤*l**e**n*(*S*),*l**e**n*(*T*)≤200 

进阶：时间复杂度：O*(*n*) ，空间复杂度：�(�) *O*(*n*) 

**输入描述**：

输入两个字符串。第一个为短字符串，第二个为长字符串。两个字符串均由小写字母组成。

**输出描述**：

如果短字符串的所有字符均在长字符串中出现过，则输出字符串"true"。否则输出字符串"false"。

```c++
#include <iostream>
using namespace std;

int main() {
    string a, b;
    char c;
    int ans(0);
    while (cin >> a >> b) { 
        for (int i = 0; i < a.size(); i++) {
            c = a[i];
            if (b.find(c) != -1) ans++;
        }
        if(ans==a.size()) cout<<"true";
        else cout<<"false";
    }
}
```

### 31. **HJ75** **公共子串计算**（中等）

**描述：**

给定两个只包含小写字母的字符串，计算两个字符串的最大公共子串的长度。

注：子串的定义指一个字符串删掉其部分前缀和后缀（也可以不删）后形成的字符串。

数据范围：字符串长度：1≤*s*≤150 

进阶：时间复杂度： *O*(*n*3) ，空间复杂度：O*(*n*) 

**输入描述**：

输入两个只包含小写字母的字符串

**输出描述**：

输出一个整数，代表最大公共子串的长度

```c++
#include <any>
#include <iostream>
using namespace std;

int main() {
    string a, b;
    while (cin >> a >> b) { 
        if (a.size() < b.size()) {
            swap(a, b);
        }
        for (int i = b.size(); i >= 0; i--) {
            for (int j = 0; j < b.size() - i + 1; j++) {
                string nw = b.substr(j, i);
                if (a.find(nw) != a.npos) {
                    cout << i << endl;
                    return 0;
                }
            }
        }
    }
    return 0;
}
```

### 32.**HJ87** **密码强度等级**

**描述:**

密码按如下规则进行计分，并根据不同的得分为密码进行安全等级划分。

一、密码长度:
5 分: 小于等于4 个字符
10 分: 5 到7 字符
25 分: 大于等于8 个字符

二、字母:
0 分: 没有字母
10 分: 密码里的字母全都是小（大）写字母
20 分: 密码里的字母符合”大小写混合“

三、数字:
0 分: 没有数字
10 分: 1 个数字
20 分: 大于1 个数字

四、符号:
0 分: 没有符号
10 分: 1 个符号
25 分: 大于1 个符号

五、奖励（只能选符合最多的那一种奖励）:
2 分: 字母和数字
3 分: 字母、数字和符号

5 分: 大小写字母、数字和符号

最后的评分标准:
\>= 90: 非常安全
\>= 80: 安全（Secure）
\>= 70: 非常强
\>= 60: 强（Strong）
\>= 50: 一般（Average）
\>= 25: 弱（Weak）
\>= 0: 非常弱（Very_Weak）

对应输出为：

VERY_SECURE
SECURE
VERY_STRONG
STRONG
AVERAGE
WEAK
VERY_WEAK

请根据输入的密码字符串，进行安全评定。

注：
字母：a-z, A-Z
数字：0-9
符号包含如下： (ASCII码表可以在UltraEdit的菜单view->ASCII Table查看)
!"#$%&'()*+,-./   (ASCII码：0x21~0x2F)
:;<=>?@       (ASCII码：0x3A~0x40)
[\]^_`       (ASCII码：0x5B~0x60)
{|}~        (ASCII码：0x7B~0x7E)

提示:
1 <= 字符串的长度<= 300

**输入描述**：

输入一个string的密码

**输出描述**：

输出密码等级

```c++
#include <cctype>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s;
    string str[] = {"VERY_SECURE",
                    "SECURE",
                    "VERY_STRONG",
                    "STRONG",
                    "AVERAGE",
                    "WEAK",
                    "VERY_WEAK"};
    while (cin >> s)
    {
        int score(0);
        if (s.size() >= 8)
            score += 25;
        else if (s.size() >= 5 && s.size() <= 7)
            score += 10;
        else
            score += 5;
        int upper(0), lower(0), num(0), els(0);
        for (auto c : s)
        {
            if (isalpha(c))
            {
                if (isupper(c))
                {
                    upper++;
                }
                if (islower(c))
                {
                    lower++;
                }
            }
            else if (isdigit(c))
            {
                num++;
            }
            else
            {
                els++;
            }
        }
        if (upper + lower)
        {
            if (upper == 0 || lower == 0)
            {
                score += 10;
            }
            else
            {
                score += 20;
            }
        }
        if (els)
        {
            if (els > 1)
            {
                score += 25;
            }
            else
            {
                score += 10;
            }
        }
        if (num)
        {
            if (num > 1)
            {
                score += 20;
            }
            else
            {
                score += 10;
            }
        }
        if (upper && lower && num && els)
        {
            score += 5;
        }
        else if (upper + lower && num && els)
        {
            score += 3;
        }
        else if (upper + lower && num)
        {
            score += 2;
        }

        if (score >= 90)
        {
            cout << str[0];
        }
        else if (score >= 80)
        {
            cout << str[1];
        }
        else if (score >= 70)
        {
            cout << str[2];
        }
        else if (score >= 60)
        {
            cout << str[3];
        }
        else if (score >= 50)
        {
            cout << str[4];
        }
        else if (score >= 25)
        {
            cout << str[5];
        }
        else if (score >= 0)
        {
            cout << str[6];
        }
    }
}

```

### 33. 

## 数组

### 1. **HJ9** **提取不重复的整数**

**描述**

输入一个 int 型整数，按照从右向左的阅读顺序，返回一个不含重复数字的新的整数。

保证输入的整数最后一位不是 0 。

数据范围：  1≤*n*≤108 

**输入描述**：

输入一个int型整数

**输出描述**：

按照从右向左的阅读顺序，返回一个不含重复数字的新的整数

```c++
#include <algorithm>
#include <iostream>
using namespace std;

bool vis[200];
int main() {
    string s;
    cin>>s;
    reverse(s.begin(),s.end());
    for(auto c:s){
        if(!vis[c]){
            vis[c]=1;
            cout<<c;
        }
    }
}
```

### 2. **HJ13** **句子逆序**

**描述**:

将一个英文语句以单词为单位逆序排放。例如“I am a boy”，逆序排放后为“boy a am I”

所有单词之间用一个空格隔开，语句中除了英文字母外，不再包含其他字符

数据范围：输入的字符串长度满足 1≤�≤1000 1≤*n*≤1000 

注意本题有多组输入

**输入描述**：

输入一个英文语句，每个单词用空格隔开。保证输入只包含空格和字母。

**输出描述**：

得到逆序的句子

```c++
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    string s;
    vector<string> cnt; //容器

    while (cin >> s) {
        cnt.push_back(s); //注入容器
    }

    reverse(cnt.begin(), cnt.end());
    for (int i = 0; i < cnt.size(); i++) {
        if (i) {
            cout << ' ';
        }
        cout << cnt[i];
    }
    return 0;
}
```

### 3. **HJ35** **蛇形矩阵**

**描述**：

蛇形矩阵是由1开始的自然数依次排列成的一个矩阵上三角形。

例如，当输入5时，应该输出的三角形为：

1 3 6 10 15

2 5 9 14

4 8 13

7 12

11

**输入描述**：

输入正整数N（N不大于100）

**输出描述**：

输出一个N行的蛇形矩阵。

```c++
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int m = 0;
    int a[100][100];

    for (int i = 0; i < n; i++) { //遍历x+y的值
        for (int j = 0; j <= i; j++) { //遍历x的值
            a[i - j][j] = ++m;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            cout << a[i][j];
            cout << ' ';
        }
        cout << endl;
    }
    return 0;
}
```

### 4.  **HJ58** **输入n个整数，输出其中最小的k个**

**描述**

输入n个整数，找出其中最小的k个整数并按升序输出

本题有多组输入样例

数据范围：1≤*n*≤1000 ，输入的整数满足 

**输入描述**：

第一行输入两个整数n和k
第二行输入一个整数数组

**输出描述**：

从小到大输出最小的k个整数，用空格分开。

```c++
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, k, j;
    cin >> n >> k;
    vector<int> cnt;
    for (int i = 0; i < n; i++) {
        cin >> j;
        cnt.push_back(j);
    }
    sort(cnt.begin(), cnt.end());
    j = k;
    for (auto x : cnt) {
        if (j) {
            cout << x << ' ';
            j--;
        }
    }
}
```

### 5. **HJ80** **整型数组合并**

**描述**

题目标题：

将两个整型数组按照升序合并，并且过滤掉重复数组元素。

输出时相邻两数之间没有空格。

**输入描述**：

输入说明，按下列顺序输入：
1 输入第一个数组的个数
2 输入第一个数组的数值
3 输入第二个数组的个数
4 输入第二个数组的数值

**输出描述**：

输出合并之后的数组

```c++
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> cnt;
int n, m;


int main() {
    while (cin >> n) {
        cnt.clear();
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            cnt.push_back(x);
        }
        cin >> m;
        for (int i = 1; i <= m; i++) {
            int x;
            cin >> x;
            cnt.push_back(x);
        }
        sort(cnt.begin(), cnt.end());
        /**
        1、erase(first,last)删除迭代器first,last之间的所有字符
        2、unique(first,last)对迭代器first,last之间的所有字符排序，把多余字符方针unique返回的后面
        **/
        cnt.erase(unique(cnt.begin(), cnt.end()), cnt.end());
        for (auto x : cnt) {
            cout << x;
        }
    }


```

### 6. **HJ97** **记负均正**I

**描述**

首先输入要输入的整数个数n，然后输入n个整数。输出为n个整数中负数的个数，和所有正整数的平均值，结果保留一位小数。

0即不是正整数，也不是负数，不计入计算。如果没有正数，则平均值为0。

**输入描述**：

首先输入一个正整数n，
然后输入n个整数。

**输出描述**：

输出负数的个数，和所有正整数的平均值。

```c++
#include <algorithm>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
vector<int> cnt;

int main() {
    int n;
    cnt.clear();
    while (cin >> n) {
        for (int i = 0; i < n; i++) {
            int m;
            cin >> m;
            cnt.push_back(m);
        }
    }
    sort(cnt.begin(), cnt.end());
    int  num1(0), num2(0);;
    double ans(0);
    for (auto x : cnt) {
        if (x < 0)  num1++;
        else if (x > 0) {
            ans = ans + x;
            num2++;
        }
    }
    if (num2)
        printf("%d %.1f\n", num1, ans / num2);
    else
        printf("%d 0.0\n", num1);
}

```

### 7. **HJ97** **记负均正**II

**描述**

输入 n 个整型数，统计其中的负数个数并求所有非负数的平均值，结果保留一位小数，如果没有非负数，则平均值为0

本题有多组输入数据，输入到文件末尾。

**输入描述**：

输入任意个整数，每行输入一个。

**输出描述**：

输出负数个数以及所有非负数的平均值

```c++
#include <algorithm>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

vector<int> cnt;

int main() {
    int n;
    cnt.clear();
    while (cin >> n) {
        cnt.push_back(n);

    }
    int  num1(0), num2(0);;
    double ans(0);
    for (auto x : cnt) {
        if (x < 0)  num1++;
        else if (x >= 0) {
            ans = ans + x;
            num2++;
        }
    }
    if (num2)
        printf("%d\n%.1f\n", num1, ans / num2);
    else
        printf("%d\n0.0\n", num1);
}

```

### 8. **HJ3** **明明的随机数**

**描述**

明明生成了*N*个1到500之间的随机整数。请你删去其中重复的数字，即相同的数字只保留一个，把其余相同的数去掉，然后再把这些数从小到大排序，按照排好的顺序输出。

**输入描述**：

第一行先输入随机整数的个数 N 。 接下来的 N 行每行输入一个整数，代表明明生成的随机数。 具体格式可以参考下面的"示例"。

**输出描述**：

输出多行，表示输入数据处理后的结果

```c++
#include <algorithm>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
vector<int> cnt;

int main() {
    int n;
    cnt.clear();
    while (cin >> n) {
        for (int i = 0; i < n; i++) {
            int m;
            cin >> m;
            cnt.push_back(m);
        }
        sort(cnt.begin(), cnt.end());
        cnt.erase(unique(cnt.begin(), cnt.end()), cnt.end());
        for (auto x : cnt) {
            cout << x << endl;
        }
    }
}
```

## 位运算

### 1. **HJ15** **求int型正整数在内存中存储时1的个数**

**描述：**

输入一个 int 型的正整数，计算出该 int 型数据在内存中存储时 1 的个数。

数据范围：保证在 32 位整型数字范围内

**输入描述**：

 输入一个整数（int类型）

**输出描述**：

 这个数转换成2进制后，输出1的个数

```c++
#include <iostream>
using namespace std;

int main() {
    int x;
    cin >> x;
    int ans(0);
    while (x) {
        ans += x&1; //利用正数补码在计算机存储特性与常数1进行与的位运算
        x >>= 1; //右移
    }
    cout << ans << endl;
}
```

### 2. **HJ62** **查找输入整数二进制中1的个数**

**描述**

输入一个正整数，计算它在二进制下的1的个数。

**注意多组输入输出！！！！！！**

数据范围：  1≤*n*≤231−1 

**输入描述**：

输入一个整数

**输出描述**：

计算整数二进制中1的个数

```c++
#include <iostream>
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        int num(0);
        while (n != 0) {
            if (n & 1 == 1) num++;
            n >>= 1;
        }
        cout << num << endl;
    }
}
```

### 3. **HJ33** **整数与IP地址间的转换**

**描述**

原理：ip地址的每段可以看成是一个0-255的整数，把每段拆分成一个二进制形式组合起来，然后把这个二进制数转变成
一个长整数。
举例：一个ip地址为10.0.3.193
每段数字       相对应的二进制数
10          00001010
0          00000000
3          00000011
193         11000001

组合起来即为：00001010 00000000 00000011 11000001,转换为10进制数就是：167773121，即该IP地址转换后的数字就是它了。

数据范围：保证输入的是合法的 IP 序列



**输入描述**：

输入 
1 输入IP地址
2 输入10进制型的IP地址

**输出描述**：

输出
1 输出转换成10进制的IP地址
2 输出转换后的IP地址

```c++
#include <bits/stdc++.h>
#include <cctype>

using namespace std;

int main() {
    long long  a, b, c, d;
    while (scanf("%lld.%lld.%lld.%lld", &a, &b, &c,
                 &d)!=EOF) { 
        long long num;
        cin >> num;
        cout << (a << 24) + (b << 16) + (c << 8) + d << endl;
        a = num >> 24;
        num = num - (a << 24); 
        b = num >> 16;
        num = num - (b << 16);
        c = num >> 8;
        d = num - (c << 8);
        
        cout << a << '.' << b << '.' << c << '.' <<d<< endl;
    }
    return 0;
}
```

### 4.**HJ86** **求最大连续bit数**

**描述**

求一个int类型数字对应的二进制数字中1的最大连续数，例如3的二进制为00000011，最大连续2个1

数据范围：数据组数：1≤*t*≤5 ，1≤*n*≤500000 

进阶：时间复杂度： *O*(*l**o**g**n*) ，空间复杂度：O*(1) 

**输入描述**：

输入一个int类型数字

**输出描述**：

输出转成二进制之后连续1的个数

```c++
#include <iostream>
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        int ans(0), num(0);
        while (n != 0) {
            if (n & 1 == 1) {
                num++;
            } else {
                if (num) {
                    ans = max(num, ans);
                    num = 0;
                }
            }
            n >>= 1;
        }
        ans = max(num, ans);
        cout << ans << endl;
    }
}
```



## 排序 

**描述**：

输入整型数组和排序标识，对其元素按照升序或降序进行排序

数据范围：1≤*n*≤1000 ，元素大小满足 0≤`val`≤100000 

**输入描述**：

第一行输入数组元素个数
第二行输入待排序的数组，每个数用空格隔开
第三行输入一个整数0或1。0代表升序排序，1代表降序排序

**输出描述**：

输出排好序的数字

良庆区与东大达到11号，办证服务中心二楼 205会议室 礼拜四 1.25 10点

```c++
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        vector<int> cnt;
        int m;
        while (n--) { //多组数据的输入
            cin >> m;
            cnt.push_back(m);
        }
        cin >> m;
        if (m == 0) {
            sort(cnt.begin(), cnt.end()); //排序，默认升序
        } else {
            sort(cnt.begin(), cnt.end(), greater<int>()); //排序，设置参数为降序

        }
        for (auto c : cnt) {
            cout << c << ' ';
        }
    }
}
```

## 哈希表

## 基础数学

**描述**

等差数列 2，5，8，11，14。。。。

（从 2 开始的 3 为公差的等差数列）

输出求等差数列前n项和

数据范围：1≤*n*≤1000 

**输入描述**：

输入一个正整数n。

**输出描述**：

输出一个相加后的整数。

```c++
#include <iostream>

using namespace std;

int main()
{
    int n;
    while(cin>>n)
    {
        int sum=2*n+3*(n-1)*n/2;
        cout<<sum<<endl;
    }
    return 0;
}
```

## 动态规划

### 1. **HJ103** `Redraiment`的走法

**描述**:

`Redraiment`是走梅花桩的高手。`Redraiment`可以选择任意一个起点，从前到后，但只能从低处往高处的桩子走。他希望走的步数最多，你能替`Redraiment`研究他最多走的步数吗？

数据范围：每组数据长度满足 1≤*n*≤200 ， 数据大小满足1≤`val`≤350 

**输入描述**：

数据共2行，第1行先输入数组的个数，第2行再输入梅花桩的高度

**输出描述**：

输出一个结果

```c++
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    while (cin >> n) { 
        int tmp;
        vector<int> cnt;
        for (int i; i < n; ++i) {
            cin >> tmp;
            cnt.push_back(tmp);
        }
        vector<int> dp(cnt.size(), 1); 
        int result(0);
        for (int i = 1; i < cnt.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (cnt[i] > cnt[j]) {
                    dp[i] = max(dp[i], dp[j] + 1); //不从j走或者j+1走到这
                }
            }
            if (dp[i] > result) {result = dp[i];}
        }
        cout<<result;
    }
}
```

> 总结：
>
> 1、`dp`数组的下标意义。`dp[i]`指明在梅花桩数组为`i`的最长顺序子序列的长度。
>
> 2、`dp`数组的初始化。由于梅花桩题目中要求每次都是从低往高走，假设梅花桩选中在开始点为梅花桩的最高位，则步数为`1`，因此设置`dp`数组的初始化均为数值`1`。
>
> 3、`dp`数组的递归公式。如果要到梅花桩`i`则要么从梅花桩`j`来（其中`j<i`），要么直接从`i`开始。
>
> 4、`dp`数组的遍历顺序。遍历顺序需要根据题目进行对照。

### 2. **HJ91** **走方格的方案数**

**描述**:

请计算n*m的棋盘格子（n为横向的格子数，m为竖向的格子数）从棋盘左上角出发沿着边缘线从左上角走到右下角，总共有多少种走法，要求不能走回头路，即：只能往右和往下走，不能往左和往上走。

注：沿棋盘格之间的边缘线行走

数据范围： 1≤*n*,*m*≤8 

**输入描述**：

输入两个正整数n和m，用空格隔开。(1≤n,m≤8)

**输出描述**：

输出一行结果

```c++
#include <cstring>
#include <iostream>
#include <iterator>
using namespace std;

int main() {
    int n, m;
    int dp[100][100];

    while (cin >> n >> m) { 
        memset(dp, 0, size(dp));
        for (int i = 0; i <=n; ++i) {
            for (int j = 0; j <= m; j++) {
                if (i == 0 & j == 0) {
                    dp[i][j] = 1;
                    continue;
                }
                if (i == 0) {
                    dp[i][j] = dp[i][j - 1];
                    continue;
                }
                if (j == 0) {
                    dp[i][j] = dp[i - 1][j];
                    continue;
                }
                dp[i][j]=dp[i][j - 1]+dp[i - 1][j];
            }
        }
        cout<<dp[n][m]<<endl;
    }
}
```

