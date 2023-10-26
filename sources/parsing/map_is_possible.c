/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_possible.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smunio <smunio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:48:35 by sammeuss          #+#    #+#             */
/*   Updated: 2023/10/25 16:22:47 by smunio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_is_possible(char	**map, t_cub *cub)
{
	int	count;

	count = 2;
	cub->map->array = init_int_array(map);
	while (nb_possibilities(cub->map->array, count, map, cub) > 0)
		count++;
	if (final_check(map, cub->map->array) == 1)
	{
		error_msg("Map is not possible", cub);
		free_int_array(cub->map->array, map);
		return (1);
	}
	else if (final_check(map, cub->map->array) == 2)
		error_msg("Map is missing", cub);
	free_int_array(cub->map->array, map);
	return (0);
}

int	final_check(char **map, int **array)
{
	int	i;
	int	u;

	if (!map)
		return (2);
	u = -1;
	i = -1;
	while (map[++i])
	{
		while (map[i][++u])
		{
			if (!is_wrong_char(map[i][u])
				&& array[i][u] < 0)
				return (1);
		}
		u = -1;
	}
	return (0);
}

int	nb_possibilities(int **array, int count, char **map, t_cub *cub)
{
	int	i;
	int	u;
	int	r;

	r = 0;
	u = -1;
	i = -1;
	while (++i < ft_array_len_int(array, map))
	{
		while (++u < (int)ft_strlen(map[i]))
		{
			if (array[i][u] >= 2)
				r += check_sides_int_array(cub, count, i, u);
		}
		u = -1;
	}
	return (r);
}

int	check_sides_int_array(t_cub	*cub, int count, int i, int u)
{
	int		r;

	r = 0;
	if (cub->map->array[i][u + 1] == -1)
	{
		cub->map->array[i][u + 1] = count + 1;
		r++;
	}
	if (cub->map->array[i][u - 1] == -1)
	{
		cub->map->array[i][u - 1] = count + 1;
		r++;
	}
	if (cub->map->array[i + 1][u] == -1)
	{
		cub->map->array[i + 1][u] = count + 1;
		r++;
	}
	if (cub->map->array[i - 1][u] == -1)
	{
		cub->map->array[i - 1][u] = count + 1;
		r++;
	}
	return (r);
}

int	**init_int_array(char **map)
{
	int	**array;
	int	i;
	int	u;

	u = -1;
	i = -1;
	array = malloc(sizeof(int *) * ft_array_len(map) + 1);
	while (++i < ft_array_len(map))
		array[i] = malloc(sizeof(int) * ft_strlen(map[i]) + 1);
	i = -1;
	while (map[++i])
	{
		while (map[i][++u])
		{
			if (map[i][u] == '1')
				array[i][u] = 1;
			else if (map[i][u] == 'S' || map[i][u] == 'E'
					|| map[i][u] == 'W' || map[i][u] == 'N')
				array[i][u] = 2;
			else
				array[i][u] = -1;
		}
		u = -1;
	}
	return (array);
}
