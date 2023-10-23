/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 16:17:23 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/23 15:34:01 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	minimap(t_cub *cub)
{
	mlx_image_t	*img_0;
	mlx_image_t	*img_1;

	img_1 = create_img_full(TSMAP, cub->mlx, 0xFFFF00FF);
	img_0 = create_img_full(TSMAP, cub->mlx, 0xFFFFFF01);
	// draw_minimap(cub->map, cub->mlx, img_1, img_0);
}

void	draw_minimap(t_map *map, mlx_t *mlx, mlx_image_t *img_1, mlx_image_t *img_0)
{
	char	**map_char;
	int		x;
	int		y;

	map_char = map->map;
	x = -1;
	y = -1;
	while (map_char[++y])
	{
		while (map_char[y][++x])
		{
			if (map_char[y][x] == '1')
				mlx_image_to_window(mlx, img_1, x * TSMAP, y * TSMAP);
			else
				mlx_image_to_window(mlx, img_0, x * TSMAP, y * TSMAP);
		}
		x = -1;
	}
}

mlx_image_t	*chose_image_to_draw(t_cub *cub, int x, int y)
{	
	if (x < 0 || y < 0)
		return (cub->image->wall_img);
	if (cub->map->map[y][x] == 0)
		return (cub->image->floor_img);
	if (cub->map->map[y][x] == 1)
		return (cub->image->wall_img);
	if (cub->map->map[y][x] == 2)
		return (cub->image->door_img);
	return (NULL);
}

void	put_image_to_image(t_cub *cub, int x_map, int y_map)
{
	int			y_img;
	int			x_img;
	uint32_t	*pixel;
	uint32_t	color;
	mlx_image_t	*img;

	y_img = 0;
	x_img = 0;
	img = chose_image_to_draw(cub, x_map, y_map);
	if (!img)
		return ;
	while (y_img < TSMAP)
	{
		while (x_img < TSMAP)
		{
			pixel = (uint32_t *)(img->pixels + (y_img + x_img * TSMAP) * sizeof(uint32_t));
			color = *pixel;
			color = get_rgba(color);
			mlx_put_pixel(cub->windows_img, x_map * TSMAP + x_img, y_map * TSMAP + y_img, color);
			x_img++;
		}
		y_img++;
		x_img = 0;
	}
}

void	draw_minimap_v2(t_cub *cub)
{
	int	x;
	int	y;

	x = floor(cub->player->pos_x) - NB_TILE;
	y = floor(cub->player->pos_y) - NB_TILE;
	while (y < y + NB_TILE * 2)
	{
		while (x < x + NB_TILE * 2)
			put_image_to_image(cub, x, y);
		y++;
		x = 0;
	}
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
				mlx_put_pixel(img, x, y, color);
			else
				mlx_put_pixel(img, x, y, 0x000000FF);
		}
		x = -1;
	}
	return (img);
}
