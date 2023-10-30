/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_structures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:30:15 by sammeuss          #+#    #+#             */
/*   Updated: 2023/10/30 17:10:40 by sammeuss         ###   ########.fr       */
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
	cub->player->pos_x = 0;
	cub->player->pos_y = 0;
	cub->player->angle = 0;
	cub->player->dir_x = 0;
	cub->player->dir_y = 0;
	cub->parsing_error = 0;
	cub->mouse_moved = 0;
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
	elements->ceiling_color = 256;
	elements->floor_color = 256;
	elements->r = 0;
	elements->g = 0;
	elements->b = 0;
	elements->north_path = NULL;
	elements->south_path = NULL;
	elements->east_path = NULL;
	elements->west_path = NULL;
	return (elements);
}

t_var	*setup_var(void)
{
	t_var	*v;

	v = malloc(sizeof(t_var));
	v->start = 0;
	v->len = 0;
	v->index = 0;
	v->comma = 0;
	v->mouse = 0;
	v->error = 0;
	v->nb_c = 0;
	v->nb_t = 0;
	v->parsing_map = 0;
	return (v);
}
