/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:04:39 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/30 13:10:40 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_doors	*create_door(int x, int y)
{
	t_doors	*door;

	door = malloc(sizeof(t_doors));
	door->x = x;
	door->y = y;
	door->state = 'C';
	door->current_img = 0;
	return (door);
}

int	count_doors(char **map)
{
	int		x;
	int		y;
	int		i;

	x = -1;
	y = -1;
	i = 0;
	while (map[++y])
	{
		while (map[y][++x])
			if (map[y][x] == 'D')
				i++;
		x = -1;
	}
	return (i);
}

void	init_door(t_cub *cub)
{
	t_map	*map;
	int		x;
	int		y;
	int		i;

	map = cub->map;
	x = -1;
	y = -1;
	i = -1;
	map->doors = malloc(sizeof(t_doors *) * (count_doors(map->map) + 1));
	while (map->map[++y])
	{
		while (map->map[y][++x])
			if (map->map[y][x] == 'D')
				map->doors[++i] = create_door(x, y);
		x = -1;
	}
	map->doors[i + 1] = NULL;
}
