/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 18:20:50 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/28 22:05:36 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_curr_img_door(t_cub *cub, t_line *line)
{
	int	i;

	i = -1;
	while (cub->map->doors[++i])
		if (cub->map->doors[i]->x == floor(line->map.x)
			&& cub->map->doors[i]->y == floor(line->map.y))
			return (cub->map->doors[i]->current_img);
	return (0);
}

void	drawtexture_doors(int line_height, int draw_start, int draw_end, t_line *line, t_cub *cub)
{
	double	wallX;
	if (line->side == 'W' || line->side == 'E')
		wallX = line->pos.y + line->reel_dist * line->dir.y;
	else
		wallX = line->pos.x + line->reel_dist * line->dir.x;
	wallX -= floor((wallX));
	int texX = (int)(wallX * (double)TEX_SIZE);
	if((line->side == 'W' || line->side == 'E') && line->dir.x > 0)
		texX = TEX_SIZE - texX - 1;
	if((line->side == 'N' || line->side == 'S') && line->dir.y < 0)
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
			texY = (int)texPos;
			texPos += step;
			if (texY >= TEX_SIZE)
				texY = TEX_SIZE - 1;
			else if (texY < 0)
				texY = 0;
			mlx_put_pixel(cub->windows_img_door, line->i, y,
				get_color_coord(texX, texY, cub->image->door_img[find_curr_img_door(cub, line)]));
		}
		else
			mlx_put_pixel(cub->windows_img, line->i, y, 0);
		y++;
	}
}

void	draw_doors(t_cub *cub, t_line *line)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	line->map.x = line->map_door.x;
	line->map.y = line->map_door.y;
	line->side = line->door_side;
	line->reel_dist = line->door_dist;
	if (line->side == 'E' || line->side == 'W')
		line->reel_dist = line->door_lenght.x - line->scale.x;
	else
		line->reel_dist = line->door_lenght.y - line->scale.y;
	line_height = (int)(WIN_HEIGHT / line->reel_dist);
	draw_start = (-line_height / 2) + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	drawtexture_doors(line_height, draw_start, draw_end, line, cub);
}

void	clear_vertical_stripe(t_cub *cub, t_line *line)
{
	int	y;

	y = -1;
	while (++y < WIN_HEIGHT)
		mlx_put_pixel(cub->windows_img_door, line->i, y, 0);
}
