/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 16:17:23 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/27 15:50:50 by ljerinec         ###   ########.fr       */
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

void	put_image_to_image(t_cub *cub, t_vector map, t_vector pos)
{
	int			y_img;
	int			x_img;
	uint32_t	*pixel;
	uint32_t	color;
	mlx_image_t	*img;

	y_img = 0;
	x_img = 0;
	img = chose_image_to_draw(cub, pos.x, pos.y);
	while (y_img < TSMAP)
	{
		while (x_img < TSMAP)
		{
			pixel = (uint32_t *)(img->pixels + (y_img + x_img * TSMAP)
					* sizeof(uint32_t));
			color = *pixel;
			color = get_rgba_tex(color);
			mlx_put_pixel(cub->windows_img, map.x * TSMAP + x_img,
				map.y * TSMAP + y_img, color);
			x_img++;
		}
		y_img++;
		x_img = 0;
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
			put_image_to_image(cub, map, start);
			map.x++;
			start.x++;
		}
		start.x = (int)(cub->player->pos_x) - NB_TILE;
		map.x = 0;
		start.y++;
		map.y++;
	}
	mlx_image_to_window(cub->mlx, cub->image->map_door,
		NB_TILE * TSMAP, NB_TILE * TSMAP);
}

mlx_image_t	*create_img_full(int size, mlx_t *mlx, uint64_t color)
{
	int			x;
	int			y;
	mlx_image_t	*img;

	x = -1;
	y = -1;
	img = mlx_new_image(mlx, size, size);
	if (!img)
		return (NULL);
	while (++y < size)
	{
		while (++x < size)
		{
			if (x == 0 || x == size - 1 || y == 0 || y == size - 1)
				mlx_put_pixel(img, x, y, 0xFFFFFFFF);
			else
				mlx_put_pixel(img, x, y, color);
		}
		x = -1;
	}
	return (img);
}
