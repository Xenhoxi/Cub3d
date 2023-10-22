/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_environnement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:19:17 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/22 18:07:39 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint64_t	chose_color(t_line *line)
{
	if (line->side == 'S')
		return (0xFF0000FF);
	else if (line->side == 'N')
		return (0x00FFFFFF);
	else if (line->side == 'W')
		return (0xFFFF00FF);
	else if (line->side == 'E')
		return (0xFF00FFFF);
	return (0xFFFFFFFF);
}

void	drawline(t_cub *cub, t_line *line, int draw_start, int draw_end)
{
	int			y;

	y = -1;
	if (!line->img_text)
		return ;
	while (++y < WIN_HEIGHT)
	{
		if (y >= draw_start && y <= draw_end)
			mlx_put_pixel(cub->windows_img, line->i, y, chose_color(line));
		else
			mlx_put_pixel(cub->windows_img, line->i, y, 0);
	}
}

void	drawtexture(int line_height, int draw_start, int draw_end, t_line *line, t_cub *cub)
{
	double	wallX;
	if (line->side == 'W' || line->side == 'E')
		wallX = line->s_y + line->reel_dist * line->dir_y;
	else
		wallX = line->s_x + line->reel_dist * line->dir_x;
	wallX -= floor((wallX));
	printf("wallX %f\n", wallX);
	int texX = (int)(wallX * (double)TEX_SIZE);
	if((line->side == 'W' || line->side == 'E') && line->dir_x > 0)
		texX = TEX_SIZE - texX - 1;
	if((line->side == 'N' || line->side == 'S') && line->dir_y < 0)
		texX = TEX_SIZE - texX - 1;
	double	step = 1.0 * TEX_SIZE / line_height;
	double	texPos = (draw_start - WIN_HEIGHT / 2 + line_height / 2) * step;
	int	y;
	int	texY;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		if (y >= draw_start && y <= draw_end)
		{
			texY = texPos;
			texPos += step;
			mlx_put_pixel(cub->windows_img, line->i, y,
				get_color_coord(texX, texY, cub->elements->west_image));
		}
		else
			mlx_put_pixel(cub->windows_img, line->i, y, 0);
		y++;
	}
}

void	draw_vision(t_cub *cub, t_line *line)
{
	int		line_height;
	int		draw_start;
	int		draw_end;

	// (void) cub;
	line_height = (int)(WIN_HEIGHT / line->reel_dist);
	draw_start = (-line_height / 2) + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	// drawline(cub, line, draw_start, draw_end);
	// printf("%u\n", get_color_coord(0, 0, mlx_texture_to_image(cub->mlx, cub->elements->east_texture)));
	drawtexture(line_height, draw_start, draw_end, line, cub);
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

void	draw_outdoor(t_cub *cub)
{
	mlx_image_t	*img_celling;
	mlx_image_t	*img_floor;
	
	printf("c = %llu et f = %llu\n", cub->elements->ceiling_color, cub->elements->floor_color);
	img_celling = create_img_cf(WIN_WIDTH, WIN_HEIGHT / 2, cub->mlx, cub->elements->ceiling_color);
	img_floor = create_img_cf(WIN_WIDTH, WIN_HEIGHT / 2, cub->mlx, cub->elements->floor_color);
	mlx_image_to_window(cub->mlx, img_floor, 0, WIN_HEIGHT / 2);
	mlx_image_to_window(cub->mlx, img_celling, 0, 0);
}

void	load_texture_tmp(t_elements *elements)
{
	elements->east_texture = mlx_load_png("./sources/textures/beige_wall.png");
	elements->west_texture = mlx_load_png("./sources/textures/dark_wall.png");
	elements->south_texture = mlx_load_png("./sources/textures/yellow_wall.png");
	elements->north_texture = mlx_load_png("./sources/textures/gray_wall.png");
}
