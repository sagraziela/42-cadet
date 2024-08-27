
#include "./ft_printf.h"
#include <stdio.h>

size_t  ft_putstr(char *str)
{
    size_t  i;

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

size_t  ft_putnbr_base(long int nbr, const char *base)
{
    size_t  len;
    int     base_len;

    len = 0;
    base_len = 0;
    while (base[base_len])
        base_len++;
    if (nbr < 0)
    {
        len += write(1, "-", 1);
        nbr *= -1;
    }
    if (nbr >= base_len)
    {
        len += ft_putnbr_base(nbr / base_len, base);
    }
    len += write(1, &base[nbr % base_len], 1);
    return (len);
}

size_t  decode_var(va_list args, char code)
{
    size_t length;

    length = 0;
    if (code == 's')
        length += ft_putstr(va_arg(args, char*));
    if (code == 'd')
        length += ft_putnbr_base(va_arg(args, int), DECIMAL);
    if (code == 'x')
        length += ft_putnbr_base(va_arg(args, long unsigned int), HEXA);
    return (length);
}

int ft_printf(const char *str, ...)
{
    va_list args;
    size_t  i;
    size_t  length;

    va_start(args, str);
    i = 0;
    length = 0;
    while (str[i])
    {
        if (str[i] == '%' && str[i + 1]
            && (str[i + 1] == 's' || str[i + 1] == 'd' || str[i + 1] == 'x'))
            length += decode_var(args, str[++i]);
        else
            length += write(1, &str[i], 1);
        i++;
    }
    va_end(args);
    return (length);
}

// int main(void)
// {
//     char *str = "hello";
//     int  n = 42;
//     int original;
//     int mine;

//     original = printf("%s world of %x\n", str, n);
//     mine = ft_printf("%s world of %x\n", str, n);
//     printf("Original: %d    |   Mine: %d\n", original, mine);
//     return (0);
// }

// cc -Wall -Wextra -Werror ft_printf.c -I ./

int	main(void)
{
	int	size;
    char	*str;

	size = 0;
    str = NULL;
	size = ft_printf("%s\n", "toto");
	printf("%d\n", size);
	size = printf("%s\n", "toto");
	printf("%d\n", size);
	size = ft_printf("Magic %s is %d - %s\n", "number", 42, str);
	printf("%d\n", size);
	size = printf("Magic %s is %d - %s\n", "number", 42, str);
	printf("%d\n", size);
	size = ft_printf("Hexadecimal for %d is %x\n", 42, 42);
	printf("%d\n", size);
	size = printf("Hexadecimal for %d is %x\n", 42, 42);
	printf("%d\n", size);
	size = ft_printf("%d %d %x\n", INT_MAX, INT_MIN, UINT_MAX);
	printf("%d\n", size);
	size = printf("%d %d %x\n", INT_MAX, INT_MIN, UINT_MAX);
	printf("%d\n", size);
	size = ft_printf("%d, %d\n", 0, -24);
	printf("%d\n", size);
	size = printf("%d, %d\n", 0, -24);
	printf("%d\n", size);
	ft_printf("Hello world %\n");
	return (0);
}
