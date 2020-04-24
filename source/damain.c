#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

void main()
{
    printf("作者：181110305董成相\n");
    void* plib;
    typedef void (*FUN_HELLO)();
    FUN_HELLO funHello = NULL;
    plib = dlopen("./libfoo.so", RTLD_NOW | RTLD_GLOBAL);
    if (plib == NULL)
    {
        printf("动态库加载异常。\n");
    }
    funHello = dlsym(plib, "bill");
    funHello("Hello world");
    dlclose(plib);
}
