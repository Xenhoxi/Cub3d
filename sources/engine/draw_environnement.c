/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_environnement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:19:17 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/10 15:35:41 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vision(t_cub *cub, t_line *line, int fdist)
{
	// int	line_height;
	// int	draw_start;
	// int	draw_end;

	(void) cub;
	if (line->side == '0')
		line->reel_dist = fdist - line->sx;
	else
		line->reel_dist = fdist - line->sy;
	// line_height = (int)(H / line->reel_dist);
	// draw_start = -line_height / 2 + H / 2;
	// if (draw_start < 0)
	// 	draw_start = 0;
	// draw_end = (int)(H / line->reel_dist);
	// if (draw_end >= H)
	// 	draw_end = H - 1;

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
