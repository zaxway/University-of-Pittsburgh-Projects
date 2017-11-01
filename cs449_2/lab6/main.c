#include <stdio.h>
#include <dlfcn.h>

int main() {
	void* handle;
	void (*my_str_copy)(char*, char*);
	handle = dlopen("mystr.so", RTLD_LAZY);
	if (handle = NULL) {
		printf("Couldn't load library! %s\n", dlerror());
		return 1;
	}
	
	my_str_copy = dlsym(handle, "my_strcpy");

	if (my_str_copy == NULL) {
		printf("Couldn't load function! %s\n", dlerror());
		return 1;
	}
	
	char dest[100];
	my_str_copy(dest, "Hello World!");
	printf("%s\n", dest);

	dlclose(handle);
	return 0;
}
