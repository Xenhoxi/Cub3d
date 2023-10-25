/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smunio <smunio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:54:14 by sammeuss          #+#    #+#             */
/*   Updated: 2023/10/25 13:21:10 by smunio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_is_valid(char	**map)
{
	if (!check_for_spawn(map))
		return (error_msg("No spawn point"), 1);
	return (0);
}

int	check_for_spawn(char **map)
{
	int	i;
	int	u;

	i = -1;
	u = -1;
	while (map[++i])
	{
		while (map[i][++u])
		{
			if (map[i][u] == 'N' || map[i][u] == 'W'
				|| map[i][u] == 'S' || map[i][u] == 'E')
				return (1);
		}
		u = -1;
	}
	return (0);
}

int	ft_array_len_int(int	**array, char **map)
{
	int		i;

	i = 0;
	if (!array)
		return (0);
	while (map[i])
		i++;
	return (i);
}
