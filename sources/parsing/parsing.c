/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 20:44:15 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/09 12:55:56 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	alloc_rays(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < NB_RAY)
		cub->ray_array[i] = malloc(sizeof(t_line));
	cub->ray_array[i] = NULL;
}

void	parsing(char *map, t_cub *cub)
{
	char	*line;
	int		fd;

	fd = selected_fd(map);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		sort_element(cub, line);
		line = get_next_line(fd);
	}
	print_char_map(cub->map->map);
	print_elements(cub->elements);
	if (map_checker(cub))
		cub->parsing_error = 1;
	free(line);
	close(fd);
}

t_cub	*setup_cub(void)
{
	t_cub	*cub;

	cub = malloc(sizeof(t_cub));
	cub->player = malloc(sizeof(t_player));
	cub->map = setup_map();
	cub->elements = setup_elements();
	cub->ray_array = malloc(sizeof(t_line *) * (NB_RAY + 1));
	alloc_rays(cub);
	cub->player->pos_x = 0;
	cub->player->pos_y = 0;
	cub->player->angle = 0;
	cub->player->dir_x = 0;
	cub->player->dir_y = 0;
	cub->game_on = 0;
	cub->parsing_error = 0;
	printf("Angle = %f\n", cub->player->angle);
	printf("dir_x = %f, dir_y = %f\n", cub->player->dir_x, cub->player->dir_y);
	return (cub);
}

t_map	*setup_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->map = NULL;
	map->array = NULL;
	map->height = 0;
	map->height_px = 0;
	map->map_index = 0;
	map->width = 0;
	map->width_px = 0;
	map->x = 0;
	map->y = 0;
	return (map);
}

t_elements	*setup_elements(void)
{
	t_elements	*elements;

	elements = malloc(sizeof(t_elements));
	elements->ceiling_color = 0;
	elements->floor_color = 0;
	elements->east = NULL;
	elements->north = NULL;
	elements->south = NULL;
	elements->west = NULL;
	return (elements);
}
