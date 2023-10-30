/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:29:36 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/29 16:30:01 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	right_rotation(t_cub *cub, double rotspeed)
{
	double	old_dir_x;
	double	old_plane_x;

	rotspeed = rotspeed / 30 * cub->dt;
	cub->player->angle += rotspeed;
	if (cub->player->angle > 2 * PI)
		cub->player->angle -= 2 * PI;
	else if (cub->player->angle < 0)
		cub->player->angle += 2 * PI;
	cub->player->dir_x = cos(cub->player->angle);
	cub->player->dir_y = sin(cub->player->angle);
	old_dir_x = cub->player->dir_x;
	cub->player->dir_x = cub->player->dir_x * cos(-rotspeed)
		- cub->player->dir_y * sin(-rotspeed);
	cub->player->dir_y = old_dir_x * sin(-rotspeed)
		+ cub->player->dir_y * cos(-rotspeed);
	old_plane_x = cub->player->plane_x;
	cub->player->plane_x = cub->player->plane_x * cos(-rotspeed)
		- cub->player->plane_y * sin(-rotspeed);
	cub->player->plane_y = old_plane_x * sin(-rotspeed)
		+ cub->player->plane_y * cos(-rotspeed);
}

void	left_rotation(t_cub *cub, double rotspeed)
{
	double	old_dir_x;
	double	old_plane_x;

	rotspeed = rotspeed / 30 * cub->dt;
	cub->player->angle -= rotspeed;
	if (cub->player->angle < 0)
		cub->player->angle += 2 * PI;
	else if (cub->player->angle > 2 * PI)
		cub->player->angle -= 2 * PI;
	cub->player->dir_x = cos(cub->player->angle);
	cub->player->dir_y = sin(cub->player->angle);
	old_dir_x = cub->player->dir_x;
	cub->player->dir_x = cub->player->dir_x * cos(rotspeed)
		- cub->player->dir_y * sin(rotspeed);
	cub->player->dir_y = old_dir_x * sin(rotspeed)
		+ cub->player->dir_y * cos(rotspeed);
	old_plane_x = cub->player->plane_x;
	cub->player->plane_x = cub->player->plane_x * cos(rotspeed)
		- cub->player->plane_y * sin(rotspeed);
	cub->player->plane_y = old_plane_x * sin(rotspeed)
		+ cub->player->plane_y * cos(rotspeed);
}
