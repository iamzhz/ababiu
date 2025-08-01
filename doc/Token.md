# Token
[头文件](https://github.com/iamzhz/Ababiu/blob/main/src/Token/Token.h)  
[代码实现](https://github.com/iamzhz/Ababiu/blob/main/src/Token/Token.cc)
## Token 的意图
> 顾名思义, 存放代码中的 token, 该类主要用于存放 token 的类型, 以及 token 的值.  
> 另外, 该类还提供了一些辅助函数, 使得更容易地设置和使用 token.
## Token 的成员
### 变量
#### std::string content;
> 用于存放 token 的值.
#### enum tokenType type;
> 用于存放 token 的类型.
#### int line;
> 用于存放 token 的行号.
#### int column;
> 用于存放 token 的列号.
# 函数
#### bool idToKeyword();
> 如果 content 是一个关键字, 则将其转换为关键字类型, 可以的话返回 true, 反之 false.  
> 为了是更快速, 它先计算 content 的长度, 再与长度相等的关键字进行比较.
#### bool matchSign(std::string content);
> 如果该类中的 type 是 tokenTypeSign, 且 content 与 this->content 相等, 则返回 true, 反之 false.
#### bool matchKeyword(std::string content);
> 如果该类中的 type 是 tokenTypeKeyword, 且 content 与 this->content 相等, 则返回 true, 反之 false.
#### void addToContent(char newChar);
> 将 newChar 加到 content 尾部.
#### void addToContent(int newChar);
> 先将 newChar 转化为字符的形式, 再调用 addToContent(char).
#### bool isEof();
> 判断该类中 type 是否是 tokenTypeEof, 返回相应的 bool 值.
### std::string Token::typeToText();
> 将 type 转化为对应的字符串, 并返回, 仅调试时会被编译.