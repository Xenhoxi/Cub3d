/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_doors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:09:15 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/29 15:22:29 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player_close_to_door(t_cub *cub, t_doors *door)
{
	t_vec	result;
	double	delta;

	delta = 2;
	result.x = cub->player->pos_x - (door->x + 0.5);
	result.y = cub->player->pos_y - (door->y + 0.5);
	if (result.x > -delta && result.x < delta && result.y > -delta && result.y < delta)
		return (1);
	else
		return (0);
}

void	open_door(t_cub *cub, t_doors *door)
{
	if (door->current_img < NB_FRM_DOOR - 1)
		door->current_img += 0.6;
	cub->map->door_moving = 1;
	door->state = 'O';
	if (door->current_img >= NB_FRM_DOOR - 1)
		cub->map->map[door->y][door->x] = '0';
}

void	close_door(t_cub *cub, t_doors *door)
{
	if (door->current_img > 0)
		door->current_img -= 0.6;
	cub->map->door_moving = 1;
	if (door->current_img < NB_FRM_DOOR - 1)
		cub->map->map[door->y][door->x] = 'D';
}

void	door_update(t_cub *cub)
{
	int		i;
	t_doors	*door;

	i = -1;
	while (cub->map->doors[++i])
	{
		door = cub->map->doors[i];
		if (is_player_close_to_door(cub, door))
			open_door(cub, door);
		else if (door->state != 'C')
			close_door(cub, door);
	}
}