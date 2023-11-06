/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smunio <smunio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:09:25 by sammeuss          #+#    #+#             */
/*   Updated: 2023/11/06 13:45:34 by smunio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map_index(char **map, t_cub *cub)
{
	int		i;
	char	*type;

	if (!map)
		return (0);
	type = NULL;
	i = -1;
	while (map[++i])
	{
		type = element_type(map[i], cub);
		if (!ft_strncmp(type, "MAP", ft_strlen(type)))
			return (i);
	}
	return (0);
}

int	is_wrong_char(char c)
{
	if (c != '0' && c != '1' && c != 'S' && c != 'N' && c != 'E'
		&& c != 'W' && c != 'D')
		return (1);
	return (0);
}

int	map_is_closed(char **map)
{
	int	i;
	int	u;
	int	r;

	r = 0;
	i = -1;
	u = -1;
	while (map[++i])
	{
		while (map[i][++u])
		{
			if (map[i][u] == '0' || map[i][u] == 'D' || map[i][u] == 'S'
				|| map[i][u] == 'N' || map[i][u] == 'W' || map[i][u] == 'E')
			{
				if (check_sides_char_map(map, i, u, r) != 4)
					return (1);
			}
		}
		u = -1;
	}
	return (0);
}

int	check_sides_char_map(char **map, int i, int u, int r)
{
	if (u < (int)ft_strlen(map[i]) - 1 && map[i][u + 1])
	{
		if (is_wrong_char(map[i][u + 1]))
			return (1);
		r++;
	}
	if (u > 0 && map[i][u - 1])
	{
		if (is_wrong_char(map[i][u - 1]))
			return (1);
		r++;
	}
	if (i < ft_array_len(map) - 1 && map[i + 1][u])
	{
		if (is_wrong_char(map[i + 1][u]))
			return (1);
		r++;
	}
	if (i > 0 && map[i - 1][u])
	{
		if (is_wrong_char(map[i - 1][u]))
			return (1);
		r++;
	}
	return (r);
}
