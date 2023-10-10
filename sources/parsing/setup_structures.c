/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_structures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:30:15 by sammeuss          #+#    #+#             */
/*   Updated: 2023/10/09 17:32:46 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	elements->east_path = NULL;
	elements->north_path = NULL;
	elements->south_path = NULL;
	elements->west_path = NULL;
	elements->north_texture = NULL;
	elements->south_texture = NULL;
	elements->east_texture = NULL;
	elements->west_texture = NULL;
	return (elements);
}