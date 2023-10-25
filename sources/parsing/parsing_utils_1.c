/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smunio <smunio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:26:08 by sammeuss          #+#    #+#             */
/*   Updated: 2023/10/25 13:22:18 by smunio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_int_array(char **map, int **array)
{
	int	i;
	int	u;

	if (!map)
		return ;
	u = -1;
	i = 0;
	while (i < get_map_index(map))
		i++;
	while (map[i])
	{
		while (map[i][++u])
			printf("%d", array[i][u]);
		printf("\n");
		u = -1;
		i++;
	}
}

int	change_case(char **map, int i, int u)
{
	if (map[i][u] == '1')
		return (1);
	else if (map[i][u] == 'S')
		return (2);
	else if (is_space(map[i][u]))
		return (-2);
	else
		return (-1);
}

char	**array_join(char **array, char *line)
{
	int		i;
	char	**new_array;
	int		len;

	i = 0;
	if (array != NULL)
		while (array[i])
			i++;
	len = i;
	new_array = malloc(sizeof(char *) * (i + 2));
	if (!new_array)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_array[i] = array[i];
		i++;
	}
	if (line[ft_strlen(line) - 1] == '\n')
		new_array[i] = ft_substr(line, 0, ft_strlen(line) - 1);
	else
		new_array[i] = ft_strdup(line);
	new_array[++i] = NULL;
	free(array);
	return (new_array);
}

int	check_ext(char	*file_name, char	*ext)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (file_name[i] && file_name[i] != '\n')
		i++;
	if (i < 5)
	{
		ft_printf("Error\nFile name too short\n");
		return (1);
	}
	i -= 4;
	while (file_name[i] && ext[j])
	{
		if (file_name[i] != ext[j])
		{
			error_msg("Wrong file extension");
			return (1);
		}
		i++;
		j++;
	}
	return (0);
}

int	file_exist(char	*file_name)
{
	if (open(file_name, O_RDONLY) == -1)
	{
		error_msg("File does not exist");
		return (1);
	}
	return (0);
}
