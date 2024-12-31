#include <stdio.h>
#include <stdlib.h>

int add(int *a, int*b, int *c)
{
    return *a + *b + *c;
}

int main(int argc, char *argv[])
{
    int a = 2, b = 3, c = 7;
    printf("%d + %d + %d = %d\n", a, b, c, add(&a, &b, &c));
    return EXIT_SUCCESS;
}
