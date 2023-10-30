/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:00:33 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/29 17:06:36 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	scale_for_ray(t_cub *cub, t_line *line)
{
	line->dir.x = cos(line->angle);
	line->dir.y = sin(line->angle);
	line->pos.x = cub->player->pos_x;
	line->pos.y = cub->player->pos_y;
	line->map.x = ((int)cub->player->pos_x);
	line->map.y = ((int)cub->player->pos_y);
	line->scale.x = 1e30;
	if (line->scale.x != 0)
		line->scale.x = fabs(1.0 / line->dir.x);
	line->scale.y = 1e30;
	if (line->scale.y != 0)
		line->scale.y = fabs(1.0 / line->dir.y);
}

void	calcul_offset(t_line *line)
{
	if (line->dir.x < 0)
	{
		line->step.x = -1;
		line->lenght.x = (line->pos.x - line->map.x) * line->scale.x;
	}
	else
	{
		line->step.x = 1;
		line->lenght.x = (line->map.x + 1.0 - line->pos.x) * line->scale.x;
	}
	if (line->dir.y < 0)
	{
		line->step.y = -1;
		line->lenght.y = (line->pos.y - line->map.y) * line->scale.y;
	}
	else
	{
		line->step.y = 1;
		line->lenght.y = (line->map.y + 1.0 - line->pos.y) * line->scale.y;
	}
}

void	dda_algorithm(t_cub *cub, t_line *line)
{
	while (1)
	{
		if (line->lenght.x < line->lenght.y)
		{
			line->lenght.x += line->scale.x;
			line->map.x += line->step.x;
			if (line->dir.x < 0)
				line->side = 'W';
			else
				line->side = 'E';
		}
		else
		{
			line->lenght.y += line->scale.y;
			line->map.y += line->step.y;
			if (line->dir.y < 0)
				line->side = 'S';
			else
				line->side = 'N';
		}
		if (is_entity(cub->map->map[line->map.y][line->map.x], line))
			break ;
	}
}

void	ray_cast(t_cub *cub)
{
	t_line		line;
	int			i;

	i = 0;
	while (i < WIN_WIDTH)
	{
		line.is_door = 0;
		line.door_dist = 0;
		line.i = i;
		line.angle = ((cub->player->angle - (PI / 6)) + (((PI / 3) / WIN_WIDTH) * i));
		scale_for_ray(cub, &line);
		calcul_offset(&line);
		dda_algorithm(cub, &line);
		draw_vision(cub, &line);
		if (line.is_door)
		{
			clear_vertical_stripe(cub, &line);
			draw_doors(cub, &line);
		}
		else
			clear_vertical_stripe(cub, &line);
		i++;
	}
}

int	is_entity(char tile_check, t_line *line)
{
	if (tile_check == 'D' && !line->is_door)
	{
		line->is_door = 1;
		line->door_side = line->side;
		line->map_door.x = line->map.x;
		line->map_door.y = line->map.y;
		if (line->door_side == 'E' || line->door_side == 'W')
			line->door_lenght.x = line->lenght.x;
		else
			line->door_lenght.y = line->lenght.y;
		return (0);
	}
	else if (tile_check == '1')
		return (1);
	return (0);
}