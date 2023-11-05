/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_initilisation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:21:32 by ljerinec          #+#    #+#             */
/*   Updated: 2023/11/05 20:23:37 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_south(t_cub *cub)
{
	cub->player->angle = -(2 * PI) / 4;
	cub->player->plane_x = 0;
	cub->player->plane_y = -0.66;
}

void	set_north(t_cub *cub)
{
	cub->player->angle = (2 * PI) / 4;
	cub->player->plane_x = 0;
	cub->player->plane_y = 0.66;
}

void	set_west(t_cub *cub)
{
	cub->player->angle = PI;
	cub->player->plane_x = 0.66;
	cub->player->plane_y = 0;
}

void	set_east(t_cub *cub)
{
	cub->player->angle = 2 * PI;
	cub->player->plane_x = -0.66;
	cub->player->plane_y = 0;
}

void	setup_start_dir(t_cub *cub, char direction)
{
	if (direction == 'C')
		set_north(cub);
	else if (direction == 'S')
		set_south(cub);
	else if (direction == 'E')
		set_west(cub);
	else if (direction == 'D')
		set_east(cub);
}
