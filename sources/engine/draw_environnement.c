/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_environnement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:19:17 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/29 17:11:16 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_image_t	*chose_image(t_cub *cub, t_line *line)
{
	if (line->side == 'S')
		return (cub->elements->south_image);
	else if (line->side == 'N')
		return (cub->elements->north_image);
	else if (line->side == 'W')
		return (cub->elements->west_image);
	else if (line->side == 'E')
		return (cub->elements->east_image);
	else
		return (NULL);
}

void	drawtexture(int line_height, int draw_start, int draw_end, t_line *line, t_cub *cub)
{
	double	wallX;
	if (line->side == 'W' || line->side == 'E')
		wallX = line->pos.y + line->reel_dist * line->dir.y;
	else
		wallX = line->pos.x + line->reel_dist * line->dir.x;
	wallX -= floor((wallX));
	int texX = (int)(wallX * (double)TEX_SIZE);
	if((line->side == 'W' || line->side == 'E') && line->dir.x > 0)
		texX = TEX_SIZE - texX - 1;
	if((line->side == 'N' || line->side == 'S') && line->dir.y < 0)
		texX = TEX_SIZE - texX - 1;
	double	step = 1.0 * TEX_SIZE / line_height;
	double	texPos = (draw_start - WIN_HEIGHT / 2 + line_height / 2) * step;
	int	y;
	int	texY;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		if (y >= draw_start && y <= draw_end)
		{
			texY = (int)texPos;
			texPos += step;
			if (texY >= TEX_SIZE)
				texY = TEX_SIZE - 1;
			else if (texY < 0)
				texY = 0;
			mlx_put_pixel(cub->windows_img, line->i, y,
				get_color_coord(texX, texY, chose_image(cub, line)));
		}
		else
			mlx_put_pixel(cub->windows_img, line->i, y, 0);
		y++;
	}
}

void	draw_vision(t_cub *cub, t_line *line)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	if (line->side == 'E' || line->side == 'W')
		line->reel_dist = line->lenght.x - line->scale.x;
	else
		line->reel_dist = line->lenght.y - line->scale.y;
	line_height = (int)(WIN_HEIGHT / line->reel_dist);
	draw_start = (-line_height / 2) + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	drawtexture(line_height, draw_start, draw_end, line, cub);
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
