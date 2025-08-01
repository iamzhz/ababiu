# CmdLineParser
[头文件查看](https://github.com/iamzhz/Ababiu/blob/main/src/CmdLineParser/CmdLineParser.h)  
[代码实现查看](https://github.com/iamzhz/Ababiu/blob/main/src/CmdLineParser/CmdLineParser.cc)  
## CmdLineParser (Command Line Parser) 的意图
  通过main函数设置两个有关命令行参数的 argc, argv 的值, 再将其解析 (parser) , 使得更好地处理命令行参数.  
## CmdLineParser 的成员变量
  1. `int argc`, `char **argv` (private)  
   > 存放两个有关命令行参数的变量的值.  
  2. `vector<string> inputFiles` (public)  
   > 存放输入文件(们)的文件名.
  3. `string outputFile` (public)  
   > 存放输出文件的文件名.
## CmdLineParser 的成员函数(方法)
  1. `bool isOption(char *para)` **(private)**
   > 是否为选项(即`-xxx`的形式 (`xxx`指一些字母,可有一个也可以多个(除特殊的只能有一个), 但只有第一个字母是选项 (option)))  
   > 如何 `para` 的第一个字符为`-`, 且第二个不为`'\0'`, 则该函数返回 true, 反之 false.  
  2. `string deleteDash(char *para)` **(private)**
   > 删除 `para` 前面的所有 `-` (dash), 并返回为 std::string.
  3. `bool option(string first, string second)` **(private)**
   > 根据 first 的情况, 处理对应的键与值,  
   > 但 second 不一定会用到, 如果用到了就返回 true, 反之返回 false.  
  4. `void setArgs(int argc, char** argv)` **(public)**
   > 将 argc, argv 复制到该类的 argc, argv的成员变量中.
  5. `CmdLineParser(int argc, char** argv)` **(public)**
   > 构造函数, 相当于给 *setArgs() 套了个壳
  6. `void run()` **(public)**
   > 遍历 argv 并调用成员函数 *option() 实现解析
  7. `void print()` **(public)**
   > debug 时用, 打印解析结果