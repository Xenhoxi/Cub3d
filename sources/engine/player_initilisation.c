/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_initilisation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:21:32 by ljerinec          #+#    #+#             */
/*   Updated: 2023/11/03 16:47:52 by sammeuss         ###   ########.fr       */
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
	(void)direction;
	if (cub->v->first_texture == 'S')
		set_south(cub);
	else if (cub->v->first_texture == 'N')
		set_north(cub);
	else if (cub->v->first_texture == 'W')
		set_west(cub);
	else if (cub->v->first_texture == 'E')
		set_east(cub);
}
