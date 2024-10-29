#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <limits.h>

#define DECIMAL "0123456789"
#define HEXA "0123456789abcdef"

int ft_putstr(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (write(1, "(null)", 6));
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
    return (i);
}

int ft_putnbr(int nbr)
{
    int len;

    len = 0;
    if (nbr == -2147483648)
    {
        len += write(1, "-2147483648", 11);
        return (len);
    }
    if (nbr < 0)
    {
        len += write(1, "-", 1);
        nbr *= -1;
    }
    if (nbr > 9)
        len += ft_putnbr(nbr / 10);
    len += write(1, &DECIMAL[nbr % 10], 1);
    return (len);
}

int ft_puthexa(unsigned int nbr)
{
    int len;

    len = 0;
    if (nbr > 9)
        len += ft_puthexa(nbr / 16);
    len += write(1, &HEXA[nbr % 16], 1);
    return (len);
}

int get_value(va_list args, char c)
{
    int len;

    len = 0;
    if (c == 's')
        len += ft_putstr(va_arg(args, char*));
    if (c == 'd')
        len += ft_putnbr(va_arg(args, int));
    if (c == 'x')
        len += ft_puthexa(va_arg(args, unsigned int));
    return (len);
}

int ft_printf(const char *str, ... )
{
    va_list args;
    int     len;
    int     i;

    i = 0;
    len = 0;
    va_start(args, str);
    while (str[i])
    {
        if (str[i] == '%')
        {
            len += get_value(args, str[++i]);
        }
        else
            len += write(1, &str[i], 1);
        i++;
    }
    va_end(args);
    return (len);
}

int main(void)
{
    int     len;
    char    *str;

    str = NULL;
    len = ft_printf("Hello, %s!\n", str);
    printf("LEN = %d\n", len);
    len = printf("Hello, %s!\n", str);
    printf("LEN = %d\n\n", len);
    /////////////////////
    len = ft_printf("The magic %s is %d! ... Hexa: %x\n", "number", INT_MIN, INT_MIN);
    printf("LEN = %d\n", len);
    len = printf("The magic %s is %d! ... Hexa: %x\n", "number", INT_MIN, INT_MIN);
    printf("LEN = %d\n\n", len);
    /////////////////////
    len = ft_printf("INT_MIN = %d | INT_MAX = %d\n", INT_MIN, INT_MAX);
    printf("LEN = %d\n", len);
    len = printf("INT_MIN = %d | INT_MAX = %d\n", INT_MIN, INT_MAX);
    printf("LEN = %d\n\n", len);
}
