/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_environnement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:19:17 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/17 16:10:14 by ljerinec         ###   ########.fr       */
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

void	draw_vision(t_cub *cub, t_line *line)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	(void) cub;
	line_height = (int)(H / line->reel_dist);
	draw_start = (-line_height / 2) + H / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + H / 2;
	if (draw_end >= H)
		draw_end = H - 1;
	drawline(cub, line, draw_start, draw_end);
	// int texNum;
	// texNum = cub->map->map[line->map_x][line->map_y];

	// double wallX;
	// if (line->side == '0')
	// 	wallX = line->sx + line->reel_dist * line->dir_y;
	// else
	// 	wallX = line->sx + line->reel_dist * line->dir_y;
	// wallX -= floor((wallX));

	// int texX = wallX * 100;
	// if(line->side == 0 && line->dir_x > 0) texX = H - texX - 1;
	// if(line->side == 1 && line->dir_y < 0) texX = H - texX - 1;
}
