/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_possible.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:48:35 by sammeuss          #+#    #+#             */
/*   Updated: 2023/10/05 15:13:01 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_is_possible(char	**map, t_cub *cub)
{
	int	count;

	count = 2;
	cub->map->array = init_int_array(map);
	// print_int_array(map, array);
	while (nb_possibilities(cub->map->array, count, map, cub) > 0)
		count++;
	if (final_check(map, cub->map->array) == 1)
	{
		ft_printf("Error\nMap is not possible\n");
		free_int_array(cub->map->array, map);
		return (1);
	}
	else if (final_check(map, cub->map->array) == 2)
		printf("Map is missing\n");
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
	print_int_array(map, array);
	return (r);
}

int	check_sides_int_array(t_cub	*cub, int count, int i, int u)
{
	int		r;

	r = 0;
	printf("i =%d\n u =%d\n", i, u);
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
			else if (map[i][u] == 'S')
				array[i][u] = 2;
			else
				array[i][u] = -1;
		}
		u = -1;
	}
	return (array);
}
