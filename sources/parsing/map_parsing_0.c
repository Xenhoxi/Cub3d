/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:09:25 by sammeuss          #+#    #+#             */
/*   Updated: 2023/10/25 13:38:27 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map_index(char **map)
{
	int		i;
	char	*type;
	char	*s;

	if (!map)
		return (0);
	s = ft_strdup("MAP");
	type = NULL;
	i = -1;
	while (map[++i])
	{
		type = element_type(map[i]);
		if (!ft_strncmp(type, s, ft_strlen(type)))
		{
			free(s);
			return (i);
		}
	}
	free(s);
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
			if (map[i][u] == '0')
			{
				if (check_sides_char_map(map, i, u, r) != 4)
				{
					error_msg("Map is not closed");
					return (1);
				}
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
