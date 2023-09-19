#include <stdio.h>
#include <dlfcn.h>

void call(const char* filename)
{
 void* handle = dlopen(filename, RTLD_LAZY);
 void (*hello)(void) = (void (*)(void))dlsym(handle, "hello");
 (*hello)();
 dlclose(handle);
}

int main()
{
 printf("Hello!\n");
 call("./libfirst.so");
 call("./libsecond.so");
}