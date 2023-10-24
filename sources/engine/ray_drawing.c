/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:00:33 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/24 16:15:27 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	scale_for_ray(t_cub *cub, t_line *line)
{
	line->dir_x = cos(line->angle);
	line->dir_y = sin(line->angle);
	line->s_x = cub->player->pos_x;
	line->s_y = cub->player->pos_y;
	line->map_x = ((int)cub->player->pos_x);
	line->map_y = ((int)cub->player->pos_y);
	line->sx = 1e30;
	if (line->sx != 0)
		line->sx = fabs(1.0 / line->dir_x);
	line->sy = 1e30;
	if (line->sy != 0)
		line->sy = fabs(1.0 / line->dir_y);
}

void	calcul_offset(t_line *line)
{
	if (line->dir_x < 0)
	{
		line->step_x = -1;
		line->lenght_x = (line->s_x - line->map_x) * line->sx;
	}
	else
	{
		line->step_x = 1;
		line->lenght_x = (line->map_x + 1.0 - line->s_x) * line->sx;
	}
	if (line->dir_y < 0)
	{
		line->step_y = -1;
		line->lenght_y = (line->s_y - line->map_y) * line->sy;
	}
	else
	{
		line->step_y = 1;
		line->lenght_y = (line->map_y + 1.0 - line->s_y) * line->sy;
	}
}

void	dda_algorithm(t_cub *cub, t_line *line)
{
	while (1)
	{
		if (line->lenght_x < line->lenght_y)
		{
			line->lenght_x += line->sx;
			line->map_x += line->step_x;
			if (line->dir_x < 0) // '0'
				line->side = 'W';
			else
				line->side = 'E';
		}
		else
		{
			line->lenght_y += line->sy;
			line->map_y += line->step_y;
			if (line->dir_y < 0)  // '1'
				line->side = 'S';
			else
				line->side = 'N';
		}
		if (cub->map->map[line->map_y][line->map_x] == '1')
			break ;
	}
	if (line->side == 'E' || line->side == 'W')
		line->reel_dist = line->lenght_x - line->sx;
	else
		line->reel_dist = line->lenght_y - line->sy;
}

void	draw_rays(t_cub *cub)
{
	t_line		line;
	int			i;

	i = 0;
	while (i < WIN_WIDTH)
	{
		line.i = i;
		line.angle = ((cub->player->angle - (PI / 6)) + (((PI / 3) / WIN_WIDTH) * i));
		scale_for_ray(cub, &line);
		calcul_offset(&line);
		dda_algorithm(cub, &line);
		if (cub->player->ray_on && i % 20 == 0)
			draw_rayline(cub, &line);
		draw_vision(cub, &line);
		i++;
	}
}

void	draw_rayline(t_cub *cub, t_line *line)
{
	line->end_x = cub->player->pos_x * TSMAP + line->dir_x * line->reel_dist * TSMAP;
	line->end_y = cub->player->pos_y * TSMAP + line->dir_y * line->reel_dist * TSMAP;
	line->s_x = cub->player->pos_x * TSMAP;
	line->s_y = cub->player->pos_y * TSMAP;
	line->dx = line->end_x - line->s_x;
	line->dy = line->end_y - line->s_y;
	line->pixels = sqrt((line->dx * line->dx) + (line->dy * line->dy));
	line->dx_p = line->dx / line->pixels;
	line->dy_p = line->dy / line->pixels;
	if (line->img)
		mlx_delete_image(cub->mlx, line->img);
	line->img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	while (line->pixels > 0 && line->s_x > 0 && line->s_y > 0 && line->s_x < WIN_WIDTH && line->s_y < WIN_HEIGHT)
	{
		mlx_put_pixel(line->img, line->s_x, line->s_y, 0x00FFFFFF);
		line->s_x += line->dx_p;
		line->s_y += line->dy_p;
		line->pixels--;
	}
	mlx_image_to_window(cub->mlx, line->img, 0, 0);
}
