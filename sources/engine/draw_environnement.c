/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_environnement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:19:17 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/30 12:01:37 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	drawline_wall(t_cub *cub, t_line *line, int tex_x)
{
	double	step;
	double	texpos;
	int		y;
	int		tex_y;

	step = 1.0 * TEX_SIZE / line->l_height;
	texpos = (line->d_start - WIN_HEIGHT / 2 + line->l_height / 2) * step;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		if (y >= line->d_start && y <= line->d_end)
		{
			tex_y = (int)texpos;
			texpos += step;
			if (tex_y >= TEX_SIZE)
				tex_y = TEX_SIZE - 1;
			else if (tex_y < 0)
				tex_y = 0;
			mlx_put_pixel(cub->windows_img, line->i, y,
				get_color_coord(tex_x, tex_y, chose_image(cub, line)));
		}
		else
			mlx_put_pixel(cub->windows_img, line->i, y, 0);
		y++;
	}
}

void	drawtexture(t_line *line, t_cub *cub)
{
	double	wall_x;
	int		tex_x;

	if (line->side == 'W' || line->side == 'E')
		wall_x = line->pos.y + line->reel_dist * line->dir.y;
	else
		wall_x = line->pos.x + line->reel_dist * line->dir.x;
	wall_x -= floor((wall_x));
	tex_x = (int)(wall_x * (double)TEX_SIZE);
	if ((line->side == 'W' || line->side == 'E') && line->dir.x > 0)
		tex_x = TEX_SIZE - tex_x - 1;
	if ((line->side == 'N' || line->side == 'S') && line->dir.y < 0)
		tex_x = TEX_SIZE - tex_x - 1;
	drawline_wall(cub, line, tex_x);
}

void	draw_vision(t_cub *cub, t_line *line)
{
	if (line->side == 'E' || line->side == 'W')
		line->reel_dist = line->lenght.x - line->scale.x;
	else
		line->reel_dist = line->lenght.y - line->scale.y;
	line->l_height = (int)(WIN_HEIGHT / line->reel_dist);
	line->d_start = (-line->l_height / 2) + WIN_HEIGHT / 2;
	if (line->d_start < 0)
		line->d_start = 0;
	line->d_end = line->l_height / 2 + WIN_HEIGHT / 2;
	if (line->d_end >= WIN_HEIGHT)
		line->d_end = WIN_HEIGHT - 1;
	drawtexture(line, cub);
}

void	draw_outdoor(t_cub *cub)
{
	mlx_image_t	*img_celling;
	mlx_image_t	*img_floor;

	img_celling = create_img_cf(WIN_WIDTH, WIN_HEIGHT / 2,
			cub->mlx, cub->elements->ceiling_color);
	img_floor = create_img_cf(WIN_WIDTH, WIN_HEIGHT / 2,
			cub->mlx, cub->elements->floor_color);
	mlx_image_to_window(cub->mlx, img_floor, 0, WIN_HEIGHT / 2);
	mlx_image_to_window(cub->mlx, img_celling, 0, 0);
}

void	draw_update(t_cub *cub)
{
	mlx_t	*mlx;

	mlx = cub->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_A) || mlx_is_key_down(mlx, MLX_KEY_D)
		|| mlx_is_key_down(mlx, MLX_KEY_S) || mlx_is_key_down(mlx, MLX_KEY_W)
		|| mlx_is_key_down(mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(mlx, MLX_KEY_RIGHT) || cub->mouse_moved != 0
		|| cub->map->door_moving != 0)
	{
		ray_cast(cub);
		draw_minimap(cub);
		cub->mouse_moved = 0;
		cub->map->door_moving = 0;
	}
}
