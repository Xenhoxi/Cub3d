/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_structures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:30:15 by sammeuss          #+#    #+#             */
/*   Updated: 2023/10/24 16:11:15 by ljerinec         ###   ########.fr       */
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
	// cub->ray_array = malloc(sizeof(t_line *) * (WIN_WIDTH + 1));
	// alloc_rays(cub);
	cub->player->pos_x = 0;
	cub->player->pos_y = 0;
	cub->player->angle = 0;
	cub->player->dir_x = 0;
	cub->player->dir_y = 0;
	cub->game_on = 0;
	cub->parsing_error = 0;
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
	elements->north_path = NULL;
	elements->south_path = NULL;
	elements->east_path = NULL;
	elements->west_path = NULL;
	elements->north_texture = malloc(sizeof(mlx_texture_t));
	elements->south_texture = malloc(sizeof(mlx_texture_t));
	elements->east_texture = malloc(sizeof(mlx_texture_t));
	elements->west_texture = malloc(sizeof(mlx_texture_t));
	return (elements);
}
