#include <stdio.h>

int main() {
    printf("int\t%d bytes \n", sizeof(int));
    printf("short\t%d bytes \n", sizeof(short));
    printf("long\t%d bytes \n", sizeof(long));
    printf("long long\t%d bytes \n", sizeof(long long));
    printf("unsigned int\t%d bytes \n", sizeof(unsigned int));
    printf("char\t%d bytes \n", sizeof(char));
    printf("float\t%d bytes \n", sizeof(float));
    printf("double\t%d bytes \n", sizeof(double));
    printf("long double\t%d bytes \n", sizeof(long double));
    printf("int*\t%d bytes \n", sizeof(int*));
    printf("float*\t%d bytes \n", sizeof(float*));
    return 0;
}
