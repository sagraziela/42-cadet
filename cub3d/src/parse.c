#include "../includes/cub.h"

t_bool	parse(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_length)
	{
		j = 0;
		while (data->map[i][j] != '\0')
		{
			if (i == 0 || j == 0 || !data->map[i][j + 1] || i == data->map_length - 1)
			{
				if (data->map[i][j] != '1')
				{
					printf("ERROR: map is not valid.\n");
					return (FALSE);
				}
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}