/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 16:17:23 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/30 15:55:07 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_spawn(char type)
{
	if (type == 'S' || type == 'N' || type == 'W' || type == 'E')
		return (1);
	return (0);
}

mlx_image_t	*chose_image_to_draw(t_cub *cub, int x, int y)
{	
	if (y >= ft_array_len(cub->map->map) || y < 0 || x < 0
		|| x >= (int)ft_strlen(cub->map->map[y]))
		return (cub->image->map_void);
	else if (cub->map->map[y][x] == '0' || is_spawn(cub->map->map[y][x]))
		return (cub->image->map_floor);
	else if (cub->map->map[y][x] == '1')
		return (cub->image->map_wall);
	else if (cub->map->map[y][x] == 'D')
		return (cub->image->map_door);
	else
		return (cub->image->map_void);
}

void	put_image_to_image(t_cub *c, t_vector map, t_vector pos, int player_pos)
{
	int			y_img;
	int			x_img;
	uint32_t	*pixel;
	uint32_t	color;
	mlx_image_t	*img;

	y_img = -1;
	x_img = -1;
	if (player_pos == 0)
		img = chose_image_to_draw(c, pos.x, pos.y);
	else
		img = c->image->map_player;
	while (++y_img < TSMAP)
	{
		while (++x_img < TSMAP)
		{
			pixel = (uint32_t *)(img->pixels + (y_img + x_img * TSMAP)
					* sizeof(uint32_t));
			color = *pixel;
			color = get_rgba_tex(color);
			mlx_put_pixel(c->windows_img_door, map.x * TSMAP + x_img,
				map.y * TSMAP + y_img, color);
		}
		x_img = -1;
	}
}

void	draw_minimap(t_cub *cub)
{
	t_vector	map;
	t_vector	start;

	map.x = 0;
	map.y = 0;
	start.x = (int)(cub->player->pos_x) - NB_TILE;
	start.y = (int)(cub->player->pos_y) - NB_TILE;
	while (map.y <= NB_TILE * 2)
	{
		while (map.x <= NB_TILE * 2)
		{
			put_image_to_image(cub, map, start, 0);
			map.x++;
			start.x++;
		}
		start.x = (int)(cub->player->pos_x) - NB_TILE;
		map.x = 0;
		start.y++;
		map.y++;
	}
	map.x = NB_TILE;
	map.y = NB_TILE;
	start.x = -1;
	start.y = -1;
	put_image_to_image(cub, map, start, 1);
}
