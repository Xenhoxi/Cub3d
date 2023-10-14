/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_environnement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:19:17 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/14 19:02:24 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	drawline(t_cub *cub, t_line *line, int draw_start, int draw_end)
{
	int			x;
	int			y;

	x = -1;
	y = -1;
	if (line->img_text)
		mlx_delete_image(cub->mlx, line->img_text);
	line->img_text = mlx_new_image(cub->mlx, PRECISION, draw_end - draw_start);
	if (!line->img_text)
		return ;
	while (++y < (draw_end - draw_start))
	{
		while (++x < PRECISION)
		{
			mlx_put_pixel(line->img_text, x, y, 0xFFFFFFFF);
		}
		x = -1;
	}
	mlx_image_to_window(cub->mlx, line->img_text, line->i * PRECISION, draw_start);
}

void	draw_vision(t_cub *cub, t_line *line, int fdist)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	(void) cub;
	if (line->side == '0')
		line->reel_dist = fdist - line->sx;
	else
		line->reel_dist = fdist - line->sy;

	line_height = (int)(H / line->reel_dist);
	draw_start = -line_height / 2 + H / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + H / 2;
	if (draw_end >= H)
		draw_end = H - 1;
	// printf("----------Ray------------\n");
	// printf("line height %d\n", line_height);
	// printf("draw start %d\n", draw_start);
	// printf("draw end %d\n", draw_end);
	// printf("line reel %f\n", line->reel_dist);

	printf("line %d\n", line->i);
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
	// if(line->side == 0 && line->dir_x > 0) texX = 100 - texX - 1;
	// if(line->side == 1 && line->dir_y < 0) texX = 100 - texX - 1;
}
