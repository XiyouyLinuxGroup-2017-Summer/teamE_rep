
# 周学习总结
> 在小组待得这第一个周的时间真的是……累死累活的（=-=）总结一下自己到底都学到什么了。

## 1.Linux上的一些文件操作
这周的项目是ls，其中用的最多的话还是文件(文件夹也是一种文件qwq)属性判断的一些相关操作。
> 其中用的最多的是文件夹操作类的。
```c
#include <sys/types.h> 
#include <dirent.h>
// 以下的函数均被包含于以上两个头文件中
DIR *opendir(const char *name);
// 该函数会返回一个DIR*类型的句柄，以便后续函数的使用
struct dirent *readdir(DIR *dir) 
// 该函数通过使用openddir（）函数所提供的DIR*格式的变量作为参数。
// 返回一个dirent格式的结构体，若后面在没有文件就返回NULL。
// 以下是该结构体的定义
struct dirent { 
    ino_t          d_ino;       /* inode number */ 
    off_t          d_off;       /* offset to the next dirent */ 
    unsigned short d_reclen;    /* length of this record */ 
    unsigned char  d_type;      /* type of file */ 
    char           d_name[256]; /* filename */ 
};
// 该结构体里面 d_name保存的是该文件的文件名。也是之后调用lstat函数所需要的。
// 有开有读必有关
int closedir(DIR *dir)；
// closedir函数关闭与指针dir相联系的目录流。关闭后，目录流描述符dir不再可用。
// 成功时返回0；失败是返回-1，并设置相应的错误代码errno。
```




只要这样通过while循环反复,就可以显示一个文件夹内所有的文件了。
> 当然只是获取名字还是远远不够的。
> 还需要获取到文件的属性。
```c
int fstat(int filedes, struct stat *buf);
int stat(const char *path, struct stat *buf);
// 其中fstat与stat类似，区别在于fstat的第一个参数是一个文件描述符。
// 也就是通过系统调用open所获取得那个。而stat和lstat仅需要文件的“全路径”
int lstat(const char *path, struct stat *buf);
// 而stat和lstat的区别在于，lstat针对链接文件可以获取到连接文件本身的信息
// 而stst获取到的是链接文件所指向的文件的信息。
```

感觉最主要的倒还不是这些，还有很多知识点，但这都不是最重要的。最重要的感觉应该是在每两天一次讲解算法时候的学长对于一些细节的掌握。

## 2.printf（）函数、scanf（）函数的参数。

当时有一道题是截掉某串字符串前五个。很多人都是指针，字符串操作（=-=我还不如他们）。然后就讲完之后学长上去写了如下的代码
```c
scanf("%*5d%d",nums);
```
这………………………和我平常用的是一个语言么QAQ（还有这种操作的？！！！）

反正是感觉基础还是蛮重要的，积累和积淀也是很重要的。不只是这些还有学长说的扫描集啦，%n的计数啦，真的是第一次听。

## 3. 总结。
再就是一点生活上的总结吧。前面说的也都挺概括的hhh。

总的来说最主要的还是看到了别人努力起来是什么样子的。以前自己其实是真的一点都没有努力过，什么东西都是学了一点点了解了点连皮毛都不是的东西就沾沾自喜，转而去学另一点点连皮毛都不是的东西。真是可笑的人生。

我可能就是所说的井底之蛙吧。

不过不管怎么样井底之蛙也好啊，癞蛤蟆也好啊。我也是可以努力的。不管天赋到底能怎么样吧。Keep moving.

共勉。
