
#include <stdio.h>
#include <dlfcn.h>

void *handle;
int (*fun1)(int);
const char *err;

int main() {
    printf(__FILE__": pripojeni ./libtest1.so\n");
    handle = dlopen("./libtest1.so",RTLD_LAZY);
    if(!handle)
        return 1;
    fun1 = dlsym(handle, "fun1"); 
    /* if(!fun1) return 2; */
    err = dlerror();
    if(err) {
        fprintf(stderr, "dlsym: error %s\n", err);
        return 3;
    }

    /* call */
    fun1(5);

    printf(__FILE__": odpojeni ./libtest1.so\n");
    dlclose(handle);
    /**/

    printf(__FILE__": pripojeni ./libtest2.so\n");
    handle = dlopen("./libtest2.so",RTLD_LAZY);
    if(!handle)
        return 1;
    fun1 = dlsym(handle, "fun2"); 
    /* if(!fun1) return 2; */
    err = dlerror();
    if(err) {
        fprintf(stderr, "dlsym: error %s\n", err);
        return 3;
    }

    /* call */
    fun1(5);

    printf(__FILE__": odpojeni ./libtest2.so\n");
    dlclose(handle);

    return 0;
}
