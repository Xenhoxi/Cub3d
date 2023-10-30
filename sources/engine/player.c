/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:09:37 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/30 12:01:09 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_update(t_cub *cub)
{
	mlx_t	*mlx;

	mlx = cub->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move_left(cub);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move_right(cub);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		move_forward(cub);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		move_backward(cub);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		right_rotation(cub, ROTSPEED * cub->dt);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		left_rotation(cub, ROTSPEED * cub->dt);
}

void	draw_player(t_cub *cub)
{
	cub->player->ray_img = create_img_full(6, cub->mlx, 0xFFFF0000);
	mlx_image_to_window(cub->mlx, cub->player->ray_img,
		TSMAP * 7 - 3, TSMAP * 7 - 3);
}

void	init_player(t_cub *cub)
{
	int			x;
	int			y;
	t_player	*player;

	find_spawn(cub->map->map, &y, &x);
	player = cub->player;
	player->pos_x = x + 0.5;
	player->pos_y = y + 0.5;
	setup_start_dir(cub, cub->map->map[y][x]);
	cub->player->dir_x = cos(cub->player->angle);
	cub->player->dir_y = sin(cub->player->angle);
	draw_player(cub);
}

void	find_spawn(char **map, int *x, int *y)
{
	*x = 0;
	*y = 0;
	if (!map)
		return ;
	while (map[*x])
	{
		while (map[*x][*y])
		{
			if (map[*x][*y] == 'N' || map[*x][*y] == 'E'
				|| map[*x][*y] == 'W' || map[*x][*y] == 'S')
				return ;
			(*y)++;
		}
		*y = 0;
		(*x)++;
	}
}
