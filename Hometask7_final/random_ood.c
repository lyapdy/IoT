#include <stdio.h>


random_odd()
{
    int res;
    res = rand() % 14;
    if (res % 2 != 0)
        return res;
    else
        return res + 1;
    // if (res % 2 == 0 && res == 0)
    //     return (rand() % 14) + 1;
}

int main()
{
    printf("%d\n", random_odd());
    printf("%d\n", random_odd());
    printf("%d\n", random_odd());
    printf("%d\n", random_odd());
    printf("%d\n", random_odd());
    printf("%d\n", random_odd());
    printf("%d\n", random_odd());
    printf("%d\n", random_odd());
    printf("%d\n", random_odd());
    return 0;
}