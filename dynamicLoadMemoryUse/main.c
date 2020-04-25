#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

void main()
{
    void* plib;
    typedef void (*FUN_HELLO)();
    FUN_HELLO funHello = NULL;
    printf("Before loading dynamic library.\n");
    printf("Please enter to continue:");
    getchar();

    plib = dlopen("./libtest.so", RTLD_NOW | RTLD_GLOBAL);
    if (plib == NULL)
    {
        printf("error\n");
    }

    funHello = dlsym(plib, "printHello");
    funHello();

    dlclose(plib);
    printf("After releasing dynamic library.\n");
    printf("Please enter to continue:");
    getchar();
}
