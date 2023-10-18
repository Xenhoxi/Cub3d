/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_environnement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:19:17 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/17 22:20:09 by ljerinec         ###   ########.fr       */
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
	int		line_height;
	int		draw_start;
	int		draw_end;

	(void) cub;
	line_height = (int)(WIN_HEIGHT / line->reel_dist);
	draw_start = (-line_height / 2) + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	drawline(cub, line, draw_start, draw_end);

	// double	wallX;
	// if (line->side == 'W' || line->side == 'E')
	// 	wallX = line->s_y + line->reel_dist * line->dir_y;
	// else
	// 	wallX = line->s_x + line->reel_dist * line->dir_x;
	// wallX -= floor((wallX));

	// int texX = wallX * TEX_SIZE;
	// if((line->side == 'W' || line->side == 'E') && line->dir_x > 0)
	// 	texX = WIN_HEIGHT - texX - 1;
	// if((line->side == 'N' || line->side == 'S') && line->dir_y < 0)
	// 	texX = WIN_HEIGHT - texX - 1;
	// double	step = 1.0 * TEX_SIZE / line_height;
	// double	texPos = (draw_start - WIN_HEIGHT / 2 + line_height / 2) * step;

}
