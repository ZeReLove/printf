#include "ft_printf.h"
#include <stdio.h>

int main()
{
    int i;
    double f;
    char    *p;
    char    a;

    i = ft_printf("% d\n", 42);
    f = printf("% d\n", 42);
    printf("%i\n", i);
    printf("%i\n", f);
    //ft_printf("The number is %.5f\n", f);
    // Все флаги, ширина, точность вроде работают с типами d и i
    // Типы s и c вроде работают
    // тип f работает
    // Типы o u x X вроде равботают
    // Тип p работает
    // Размер вроде работает
    return (0);
}
