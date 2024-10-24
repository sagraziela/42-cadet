#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <limits.h>

#define DECIMAL "0123456789"
#define HEXA    "0123456789abcdef"

size_t  ft_putstr(char *str)
{
    size_t i;

    i = 0;
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
    return (i);
}

size_t  ft_putint(int nbr)
{
    size_t length;

    length = 0;
    if (nbr == -2147483648)
    {
        length += write(1, "-2147483648", 11);
        return (length);
    }
    if (nbr < 0)
    {
        length += write(1, "-", 1);
        nbr *= -1;
    }
    if (nbr > 10)
    {
        length += ft_putint(nbr / 10);
    }
    length += write(1, &DECIMAL[nbr % 10], 1);
    return (length);
}

size_t ft_puthex(unsigned int nbr)
{
    size_t length;

    length = 0;
    if (nbr > 16)
    {
        length += ft_puthex(nbr / 16);
    }
    length += write(1, &HEXA[nbr % 16], 1);
    return (length);
}

size_t  get_var_value(va_list args, char type)
{
    size_t length;

    length = 0;
    if (type == 's')
        length += ft_putstr(va_arg(args, char*));
    if (type == 'd')
        length += ft_putint(va_arg(args, int));
    if (type == 'x')
        length += ft_puthex(va_arg(args, unsigned int));
    return (length);
}

size_t ft_printf(const char *str, ...)
{
    size_t  i;
    size_t  length;
    va_list args;

    i = 0;
    length = 0;
    va_start(args, str);
    while (str[i])
    {
        if (str[i] == '%')
        {
            length += get_var_value(args, str[++i]);
        }
        else
        {
            length += write(1, &str[i], 1);
        }
        i++;
    }
    va_end(args);
    return (length);
}

int main(void)
{
    int size;

    size = ft_printf("Hello, %s!\n", "you");
    printf("SIZE = %d\n\n", size);
    size = printf("Hello, %s!\n", "you");
    printf("SIZE = %d\n\n", size);
    //
    size = ft_printf("The %s number is %d!   HEXA: %x\n", "magic", 42, 42);
    printf("SIZE = %d\n\n", size);
    size = printf("The %s number is %d!   HEXA: %x\n", "magic", 42, 42);
    printf("SIZE = %d\n\n", size);
    //
    size = ft_printf("INT_MAX: %d  |   INT_MIN: %d\n", INT_MAX, INT_MIN);
    printf("SIZE = %d\n\n", size);
    size = printf("INT_MAX: %d  |   INT_MIN: %d\n", INT_MAX, INT_MIN);
    printf("SIZE = %d\n\n", size);
    //
    size = ft_printf("HEXA_INT_MAX: %x  |   HEXA_INT_MIN: %x\n", INT_MAX, INT_MIN);
    printf("SIZE = %d\n\n", size);
    size = printf("HEXA_INT_MAX: %x  |   HEXA_INT_MIN: %x\n", INT_MAX, INT_MIN);
    printf("SIZE = %d\n\n", size);
    return (0);
}

// cc ft_printf.c -Wall -Wextra -Werror
