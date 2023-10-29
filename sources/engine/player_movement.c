/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:00:31 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/29 14:57:46 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(char tile_type)
{
	if (tile_type == '1' || tile_type == 'D')
		return (1);
	return (0);
}

void	move_forward(t_cub *cub)
{
	int		next_pos_x;
	int		next_pos_y;
	double	speed;

	speed = SPEED * cub->dt;
	next_pos_x = (int)(cub->player->pos_x + cub->player->dir_x * speed);
	next_pos_y = (int)(cub->player->pos_y + cub->player->dir_y * speed);
	if (!is_wall(cub->map->map[(int)cub->player->pos_y][next_pos_x]))
		cub->player->pos_x += cub->player->dir_x * speed;
	if (!is_wall(cub->map->map[next_pos_y][(int)cub->player->pos_x]))
		cub->player->pos_y += cub->player->dir_y * speed;
}

void	move_backward(t_cub *cub)
{
	int		next_pos_x;
	int		next_pos_y;
	double	speed;

	speed = SPEED * cub->dt;
	next_pos_x = (int)(cub->player->pos_x - cub->player->dir_x * speed);
	next_pos_y = (int)(cub->player->pos_y - cub->player->dir_y * speed);
	if (!is_wall(cub->map->map[(int)cub->player->pos_y][next_pos_x]))
		cub->player->pos_x -= cub->player->dir_x * speed;
	if (!is_wall(cub->map->map[next_pos_y][(int)cub->player->pos_x]))
		cub->player->pos_y -= cub->player->dir_y * speed;
}

void	move_left(t_cub *cub)
{
	int		next_pos_x;
	int		next_pos_y;
	double	speed;

	speed = SPEED * cub->dt;
	next_pos_x = (int)(cub->player->pos_x
			+ (cos(cub->player->angle - (2 * PI / 4))) * speed * 5);
	next_pos_y = (int)(cub->player->pos_y
			+ (sin(cub->player->angle - (2 * PI / 4))) * speed * 5);
	if (!is_wall(cub->map->map[(int)cub->player->pos_y][next_pos_x]))
		cub->player->pos_x += (cos(cub->player->angle - (2 * PI / 4))) * speed;
	if (!is_wall(cub->map->map[next_pos_y][(int)cub->player->pos_x]))
		cub->player->pos_y += (sin(cub->player->angle - (2 * PI / 4))) * speed;
}

void	move_right(t_cub *cub)
{
	int		next_pos_x;
	int		next_pos_y;
	double	speed;

	speed = SPEED * cub->dt;
	next_pos_x = (int)(cub->player->pos_x
			- (cos(cub->player->angle - (2 * PI / 4))) * speed * 5);
	next_pos_y = (int)(cub->player->pos_y
			- (sin(cub->player->angle - (2 * PI / 4))) * speed * 5);
	if (!is_wall(cub->map->map[(int)cub->player->pos_y][next_pos_x]))
		cub->player->pos_x -= (cos(cub->player->angle - (2 * PI / 4))) * speed;
	if (!is_wall(cub->map->map[next_pos_y][(int)cub->player->pos_x]))
		cub->player->pos_y -= (sin(cub->player->angle - (2 * PI / 4))) * speed;
}
