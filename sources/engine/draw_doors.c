/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 18:20:50 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/30 11:54:36 by ljerinec         ###   ########.fr       */
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
			return ((int)cub->map->doors[i]->current_img);
	return (0);
}

void	drawline_door(t_cub *cub, t_line *line, int tex_x)
{
	double	step;
	double	texpos;
	int		y;
	int		tex_y;

	step = 1.0 * TEX_SIZE / line->l_height;
	texpos = (line->d_start - WIN_HEIGHT / 2 + line->l_height / 2) * step;
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		if (y >= line->d_start && y <= line->d_end)
		{
			tex_y = (int)texpos;
			texpos += step;
			if (tex_y >= TEX_SIZE)
				tex_y = TEX_SIZE - 1;
			else if (tex_y < 0)
				tex_y = 0;
			mlx_put_pixel(cub->windows_img_door, line->i, y,
				get_color_coord(tex_x, tex_y,
					cub->image->door_img[find_curr_img_door(cub, line)]));
		}
		else
			mlx_put_pixel(cub->windows_img, line->i, y, 0);
	}
}

void	drawtexture_doors(t_line *line, t_cub *cub)
{
	double	wall_x;
	int		tex_x;

	if (line->side == 'W' || line->side == 'E')
		wall_x = line->pos.y + line->reel_dist * line->dir.y;
	else
		wall_x = line->pos.x + line->reel_dist * line->dir.x;
	wall_x -= floor((wall_x));
	tex_x = (int)(wall_x * (double)TEX_SIZE);
	if ((line->side == 'W' || line->side == 'E') && line->dir.x > 0)
		tex_x = TEX_SIZE - tex_x - 1;
	if ((line->side == 'N' || line->side == 'S') && line->dir.y < 0)
		tex_x = TEX_SIZE - tex_x - 1;
	drawline_door(cub, line, tex_x);
}

void	draw_doors(t_cub *cub, t_line *line)
{
	line->map.x = line->map_door.x;
	line->map.y = line->map_door.y;
	line->side = line->door_side;
	line->reel_dist = line->door_dist;
	if (line->side == 'E' || line->side == 'W')
		line->reel_dist = line->door_lenght.x - line->scale.x;
	else
		line->reel_dist = line->door_lenght.y - line->scale.y;
	line->l_height = (int)(WIN_HEIGHT / line->reel_dist);
	line->d_start = (-line->l_height / 2) + WIN_HEIGHT / 2;
	if (line->d_start < 0)
		line->d_start = 0;
	line->d_end = line->l_height / 2 + WIN_HEIGHT / 2;
	if (line->d_end >= WIN_HEIGHT)
		line->d_end = WIN_HEIGHT - 1;
	drawtexture_doors(line, cub);
}

void	clear_vertical_stripe(t_cub *cub, t_line *line)
{
	int	y;

	y = -1;
	while (++y < WIN_HEIGHT)
		mlx_put_pixel(cub->windows_img_door, line->i, y, 0);
}
