/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_img_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:18:05 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/30 12:01:40 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

u_int32_t	get_color_coord(int x, int y, mlx_image_t *img)
{
	uint32_t	*pixel;
	u_int32_t	color;

	pixel = NULL;
	pixel = (uint32_t *)(img->pixels + (x + y * TEX_SIZE) * sizeof(uint32_t));
	color = *pixel;
	return (get_rgba_tex(color));
	return (0);
}

mlx_image_t	*create_img_cf(int width, int height, mlx_t *mlx, uint64_t color)
{
	int			x;
	int			y;
	mlx_image_t	*img;

	x = -1;
	y = -1;
	img = mlx_new_image(mlx, width, height);
	if (!img)
		return (NULL);
	while (++y < height)
	{
		while (++x < width)
			mlx_put_pixel(img, x, y, color);
		x = -1;
	}
	return (img);
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

mlx_image_t	*chose_image(t_cub *cub, t_line *line)
{
	if (line->side == 'S')
		return (cub->elements->south_image);
	else if (line->side == 'N')
		return (cub->elements->north_image);
	else if (line->side == 'W')
		return (cub->elements->west_image);
	else if (line->side == 'E')
		return (cub->elements->east_image);
	else
		return (NULL);
}
