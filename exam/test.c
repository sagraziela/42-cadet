#include <unistd.h>

void    ft_inter(char *str, char *str2)
{
    int	ascii[255] = { 0 };
    int	ascii2[255] = { 0 };
	int	i = 0;

	while (str2[i] != '\0')
	{
		if (ascii2[(int)str2[i]] == 0)
			ascii2[(int)str2[i]] = 1;
		i++;
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (ascii[(int)str[i]] == 0 && ascii2[(int)str[i]] == 1)
		{
			write(1, &str[i], 1);
			ascii[(int)str[i]] = 1;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 3)
        ft_inter(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}