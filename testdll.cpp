#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*TestHelloFunc)(void);

int main(int argc, char *argv[]) {
    void *hLib;
    TestHelloFunc TestHello;

    hLib = dlopen("./libtestfunc.so", RTLD_LAZY);
    if (!hLib) {
        printf("Cannot load library: %s\n", dlerror());
        exit(-1);
    }

    TestHello = (TestHelloFunc)dlsym(hLib, "TestHello");
    if (!TestHello) {
        printf("TestHello function not found: %s\n", dlerror());
        dlclose(hLib);
        exit(-2);
    }

    TestHello();

    dlclose(hLib);
    return 0;
}

