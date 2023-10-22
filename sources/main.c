/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 23:50:45 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/22 01:54:32 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_hook(void *param)
{
	t_cub	*cub;
	mlx_t	*mlx;

	cub = (t_cub *)param;
	mlx = cub->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

uint32_t	get_rgba(u_int32_t color)
{
	u_int8_t	r;
	u_int8_t	g;
	u_int8_t	b;
	u_int8_t	a;

	a = color >> 24;
	r = color >> 16;
	g = color >> 8;
	b = color;
	return (r << 8 | g << 16 | b << 24 | a << 0);
}

u_int32_t	get_color_coord(int x, int y, mlx_image_t *img)
{
	uint32_t	*pixel;
	u_int32_t	color;

	pixel = NULL;
	if (x > 0 && x < TEX_SIZE && y > 0 && y < TEX_SIZE)
	{
		pixel = (uint32_t *)(img->pixels + (x + y * TEX_SIZE) * sizeof(uint32_t));
		color = *pixel;
		return (get_rgba(color));
	}
	// else
		// printf("x = %d y = %d\n", x, y);
	return (0);
}

void	test(t_cub *cub)
{
	mlx_image_t *img;
	mlx_image_t *img_vo;
	int y = 0;
	int x = 0;
	
	uint32_t	*pixel;
	uint32_t	color;
	img = mlx_new_image(cub->mlx, TEX_SIZE, TEX_SIZE);
	img_vo = mlx_texture_to_image(cub->mlx, cub->elements->north_texture);
	while (x < TEX_SIZE)
	{
		while (y < TEX_SIZE)
		{
			pixel = (uint32_t *)(img_vo->pixels + (x + y * TEX_SIZE) * sizeof(uint32_t));
			color = *pixel;
			color = get_rgba(color);
			mlx_put_pixel(img, x, y, color);
			y++;
		}
		x++;
		y = 0;
	}
	printf("%u\n", get_color_coord(69, 69, mlx_texture_to_image(cub->mlx, cub->elements->east_texture)));
	mlx_image_to_window(cub->mlx, img_vo, 0, 0);
	mlx_image_to_window(cub->mlx, img, 0, 70);
}

void	ft_load(t_cub *cub)
{
	load_texture_tmp(cub->elements);
	cub->windows_img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->elements->west_image = mlx_texture_to_image(cub->mlx, cub->elements->west_texture);
	draw_outdoor(cub);
	init_player(cub);
	draw_rays(cub);
	printf("ici\n");
	mlx_image_to_window(cub->mlx, cub->windows_img, 0, 0);
	minimap(cub);
	// test(cub);
	draw_direction(cub);
}

void	ft_update(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	player_update(cub);
	return ;
}

void	run(t_cub *cub)
{
	cub->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Black ops 2 Zombies", true);
	if (!cub->mlx)
		exit(EXIT_FAILURE);
	ft_load(cub);
	mlx_loop_hook(cub->mlx, ft_update, (void *)cub);
	mlx_loop_hook(cub->mlx, key_hook, (void *)cub);
	mlx_loop(cub->mlx);
	mlx_terminate(cub->mlx);
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	(void)argc;
	cub = setup_cub();
	if (argc != 2 || check_file(argv))
		return (1);
	parsing(argv[1], cub);
	// if (!cub->parsing_error)
		run(cub);
	return (0);
}
