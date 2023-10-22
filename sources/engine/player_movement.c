/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:00:31 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/19 19:41:39 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(char tile_type)
{
	if (tile_type == '1')
		return (1);
	return (0);
}

void	move_forward(t_cub *cub)
{
	int	next_pos_x;
	int	next_pos_y;

	next_pos_x = (int)(cub->player->pos_x + cub->player->dir_x * 10 * SPEED);
	next_pos_y = (int)(cub->player->pos_y + cub->player->dir_y * 10 * SPEED);
	if (!is_wall(cub->map->map[(int)cub->player->pos_y][next_pos_x]))
		cub->player->pos_x += cub->player->dir_x * SPEED;
	if (!is_wall(cub->map->map[next_pos_y][(int)cub->player->pos_x]))
		cub->player->pos_y += cub->player->dir_y * SPEED;
}

void	move_backward(t_cub *cub)
{
	int	next_pos_x;
	int	next_pos_y;

	next_pos_x = (int)(cub->player->pos_x - cub->player->dir_x * 10 * SPEED);
	next_pos_y = (int)(cub->player->pos_y - cub->player->dir_y * 10 * SPEED);
	if (!is_wall(cub->map->map[(int)cub->player->pos_y][next_pos_x]))
		cub->player->pos_x -= cub->player->dir_x * SPEED;
	if (!is_wall(cub->map->map[next_pos_y][(int)cub->player->pos_x]))
		cub->player->pos_y -= cub->player->dir_y * SPEED;
}

void	move_left(t_cub *cub)
{
	int	next_pos_x;
	int	next_pos_y;

	next_pos_x = (int)(cub->player->pos_x + (cos(cub->player->angle - (2 * PI / 4))) * SPEED * 5);
	next_pos_y = (int)(cub->player->pos_y + (sin(cub->player->angle - (2 * PI / 4))) * SPEED * 5);
	if (!is_wall(cub->map->map[(int)cub->player->pos_y][next_pos_x]))
		cub->player->pos_x += (cos(cub->player->angle - (2 * PI / 4))) * SPEED;
	if (!is_wall(cub->map->map[next_pos_y][(int)cub->player->pos_x]))
		cub->player->pos_y += (sin(cub->player->angle - (2 * PI / 4))) * SPEED;
}

void	move_right(t_cub *cub)
{
	int	next_pos_x;
	int	next_pos_y;

	next_pos_x = (int)(cub->player->pos_x - (cos(cub->player->angle - (2 * PI / 4))) * SPEED * 5);
	next_pos_y = (int)(cub->player->pos_y - (sin(cub->player->angle - (2 * PI / 4))) * SPEED * 5);
	if (!is_wall(cub->map->map[(int)cub->player->pos_y][next_pos_x]))
		cub->player->pos_x -= (cos(cub->player->angle - (2 * PI / 4))) * SPEED;
	if (!is_wall(cub->map->map[next_pos_y][(int)cub->player->pos_x]))
		cub->player->pos_y -= (sin(cub->player->angle - (2 * PI / 4))) * SPEED;
}
