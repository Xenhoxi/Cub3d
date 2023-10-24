/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 16:17:23 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/24 15:10:22 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	minimap(t_cub *cub)
{
	mlx_image_t	*img_0;
	mlx_image_t	*img_1;

	img_1 = create_img_full(TSMAP, cub->mlx, 0xFFFF00FF);
	img_0 = create_img_full(TSMAP, cub->mlx, 0xFFFFFF01);
	draw_minimap(cub->map, cub->mlx, img_1, img_0);
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

int	is_spawn(char type)
{
	if (type == 'S' || type == 'N' || type == 'W' || type == 'E')
		return (1);
	return (0);
}

mlx_image_t	*chose_image_to_draw(t_cub *cub, int x, int y)
{	
	if (y >= ft_array_len(cub->map->map) || y < 0 || x < 0 || x >= (int)ft_strlen(cub->map->map[y]))
		return (cub->image->transparent_img);
	else if (cub->map->map[y][x] == '0' || is_spawn(cub->map->map[y][x]))
		return (cub->image->floor_img);
	else if (cub->map->map[y][x] == '1')
		return (cub->image->wall_img);
	else if (cub->map->map[y][x] == '2')
		return (cub->image->door_img);
	else
		return (cub->image->transparent_img);
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
			pixel = (uint32_t *)(img->pixels + (y_img + x_img * TSMAP) * sizeof(uint32_t));
			color = *pixel;
			color = get_rgba(color);
			mlx_put_pixel(cub->windows_img, map.x * TSMAP + x_img, map.y * TSMAP + y_img, color);
			x_img++;
		}
		y_img++;
		x_img = 0;
	}
}

void	draw_minimap_v2(t_cub *cub)
{
	t_vector	map;
	t_vector	start;

	map.x = 0;
	map.y = 0;
	start.x = floor(cub->player->pos_x) - NB_TILE;
	start.y = floor(cub->player->pos_y) - NB_TILE;
	while (map.y <= NB_TILE * 2)
	{
		while (map.x <= NB_TILE * 2)
		{
			put_image_to_image(cub, map, start);
			map.x++;
			start.x++;
		}
		start.x = floor(cub->player->pos_x) - NB_TILE;
		map.x = 0;
		start.y++;
		map.y++;
	}
	mlx_image_to_window(cub->mlx, cub->image->door_img, NB_TILE * TSMAP, NB_TILE * TSMAP);
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
