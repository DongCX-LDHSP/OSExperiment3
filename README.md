# 实验三

## 静态链接

较为简单，直接按照老师的代码敲就完了，然后编译运行。

1. 码代码 `fred.c` `bill.c` `lib.h` `slmain.c`
2. `gcc -c fred.c bill.c`
3. `gcc -c slmain.c`
4. `gcc -o slmain slmain.o bill.o`
5. `./slmain`
6. 使用`ar`命令创建静态库，使用`ranlib`命令为文档建立索引
7. `ar crv libfoo.a bill.o fred.o`
8. `ranlib libfoo.a`
9. `gcc -o slmain slmain.o libfoo.a`
10. `./slmain`

## 动态链接

较为简单，只须将`静态链接`中的`slmain.c`的代码复制一份重命名为`dlmain.c`即可，然后使用不同的命令进行链接

1. `gcc -c -fPIC bill.c fred.c` `-f`后跟一些编译选项，`PIC(Position Independent Code)`表示生成位置无关代码
2. `gcc -shared -o libfoo.so bill.o fred.o`
3. `cp slmain.c dlmain.c` 拷贝一份静态链接的代码
4. `gcc dlmain.c -o dlmain -L ./ -lfoo`
5. `sudo cp libfoo.so /usr/lib` 将生成的动态链接库拷贝到`usr/lib`路径下，因为操作系统默认前往该路径查找动态链接库
6. `./dlmain`

## 动态加载

难度不大，参照课上或实验指导中的教程照猫画虎即可

1. 在代码中写入第二个实验内容生成的动态链接库
2. `gcc damain.c -o damain -ldl` `-l`表示链接某一个库，之前的`-lpthread`也是这种情况
3. `./damain`

## 比较`slmain` `dlmain` `damain`三个文件

使用`ldd 文件名`进行观察比较即可

## 确认动态库加载内存使用

1. 编写`libtest.c`文件
2. 编写`main.c`文件
3. 使用命令`gcc libtest.c -shared -fPIC -o libtest.so` 生成动态链接库 `libtest.so`
4. 使用命令`gcc main.c -o main -ldl`生成链接了动态库的可执行文件`main`
5. `./main`运行程序
6. 使用命令`ps -ef | grep main`查询`main`程序的`pid`
7. 打开相应的文件夹 `/proc/pid`
8. 结合程序的流程使用命令 `cat maps` 观察内存变化

## 动态链接函数的含义

1. `dlopen`：打开动态库。函数原型`void* dlopen(const char* filename, int flag);` `dlopen`用于打开指定名字`(filename)`的动态库，并返回操作句柄。
2. `dlsym`，取函数执行地址。函数原型为`void* dlsym(void* handle, char *symbol);` `dlsym`根据动态库操作句柄`(handle)`与符号`(symbol)`，返回符号对应的函数的执行代码地址。
3. `dlclose`，关闭动态库。函数原型为`int dlclose (void *handle);` `dlclose`用于关闭指定句柄的动态库，只有当此动态库的使用计数为`0`时，才会真正被系统卸载。
