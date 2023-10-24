/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:09:37 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/24 17:11:58 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	right_rotation(t_cub *cub)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rotspeed;

	rotspeed = ROTSPEED * cub->dt;
	cub->player->angle += rotspeed;
	if (cub->player->angle > 2 * PI)
		cub->player->angle -= 2 * PI;
	else if (cub->player->angle < 0)
		cub->player->angle += 2 * PI;
	cub->player->dir_x = cos(cub->player->angle);
	cub->player->dir_y = sin(cub->player->angle);
	old_dir_x = cub->player->dir_x;
	cub->player->dir_x = cub->player->dir_x * cos(-rotspeed) - cub->player->dir_y * sin(-rotspeed);
	cub->player->dir_y = old_dir_x * sin(-rotspeed) + cub->player->dir_y * cos(-rotspeed);
	old_plane_x = cub->player->plane_x;
	cub->player->plane_x = cub->player->plane_x * cos(-rotspeed) - cub->player->plane_y * sin(-rotspeed);
	cub->player->plane_y = old_plane_x * sin(-rotspeed) + cub->player->plane_y * cos(-rotspeed);
}

void	left_rotation(t_cub *cub)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rotspeed;

	rotspeed = ROTSPEED * cub->dt;
	cub->player->angle -= rotspeed;
	if (cub->player->angle < 0)
		cub->player->angle += 2 * PI;
	else if (cub->player->angle > 2 * PI)
		cub->player->angle -= 2 * PI;
	cub->player->dir_x = cos(cub->player->angle);
	cub->player->dir_y = sin(cub->player->angle);
	old_dir_x = cub->player->dir_x;
	cub->player->dir_x = cub->player->dir_x * cos(rotspeed) - cub->player->dir_y * sin(rotspeed);
	cub->player->dir_y = old_dir_x * sin(rotspeed) + cub->player->dir_y * cos(rotspeed);
	old_plane_x = cub->player->plane_x;
	cub->player->plane_x = cub->player->plane_x * cos(rotspeed) - cub->player->plane_y * sin(rotspeed);
	cub->player->plane_y = old_plane_x * sin(rotspeed) + cub->player->plane_y * cos(rotspeed);
}

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
		right_rotation(cub);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		left_rotation(cub);
	if (mlx_is_key_down(mlx, MLX_KEY_A) || mlx_is_key_down(mlx, MLX_KEY_D)
		|| mlx_is_key_down(mlx, MLX_KEY_S) || mlx_is_key_down(mlx, MLX_KEY_W)
		|| mlx_is_key_down(mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(mlx, MLX_KEY_RIGHT) || cub->mouse_moved != 0)
	{
		draw_rays(cub);
		draw_minimap(cub);
		cub->mouse_moved = 0;
	}
}

int	entity_hitbox(char **map, int x, int y)
{
	int	x_map;
	int	y_map;

	x_map = x / TSMAP;
	y_map = y / TSMAP;
	printf("x = %d | y = %d\n", x_map, y_map);
	printf("map[] = %c\n", map[y_map][x_map]);
	if (map[y_map][x_map] == '1')
		return (1);
	return (0);
}

void	draw_direction(t_cub *cub)
{
	t_line	line;

	line.end_x = cub->player->pos_x + (cub->player->dir_x * 10);
	line.end_y = cub->player->pos_y + (cub->player->dir_y * 10);
	line.s_x = cub->player->pos_x * TSMAP;
	line.s_y = cub->player->pos_y * TSMAP;
	line.dx = line.end_x - cub->player->pos_x;
	line.dy = line.end_y - cub->player->pos_y;
	line.pixels = sqrt((line.dx * line.dx) + (line.dy * line.dy));
	line.dx_p = line.dx;
	line.dy_p = line.dy;
	line.dx_p /= line.pixels;
	line.dy_p /= line.pixels;
	if (cub->player->ray_img)
		mlx_delete_image(cub->mlx, cub->player->ray_img);
	cub->player->ray_img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	while (line.pixels > 0 && line.s_x > 0 && line.s_y > 0)
	{
		mlx_put_pixel(cub->player->ray_img, line.s_x, line.s_y, 0xFF0000FF);
		line.s_x += line.dx_p;
		line.s_y += line.dy_p;
		line.pixels--;
	}
	mlx_image_to_window(cub->mlx, cub->player->ray_img, 0, 0);
}

void	draw_player(t_cub *cub)
{
	cub->player->ray_img = create_img_full(6, cub->mlx, 0xFFFF0000);
	mlx_image_to_window(cub->mlx, cub->player->ray_img, TSMAP * 7 - 3, TSMAP * 7 - 3);
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
	cub->player->angle = -((2 * PI / 4));
	cub->player->dir_x = cos(cub->player->angle);
	cub->player->dir_y = sin(cub->player->angle);
	cub->player->plane_x = 0;
	cub->player->plane_y = 0.66;
	cub->player->ray_on = 0;
	draw_player(cub);
}

void	find_spawn(char **map, int *x, int *y)
{
	*x = 0;
	*y = 0;
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
