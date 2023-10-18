/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 23:50:45 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/18 16:01:11 by ljerinec         ###   ########.fr       */
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

uint32_t	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	test(t_cub *cub)
{
	mlx_image_t *img;
	mlx_image_t *img_vo;
	mlx_image_t *img_test;
	int u = 0;
	int i = -1;
	int	v1 = 0;
	// int	v2 = 0;

	img_test = create_img_cf(70, 70, cub->mlx, 0xFFFF00FF);
	img = mlx_new_image(cub->mlx, TEX_SIZE, TEX_SIZE);
	img_vo = mlx_texture_to_image(cub->mlx, cub->elements->east_texture);
	printf("nb byte by pixels %d\n", cub->elements->east_texture->bytes_per_pixel);
	while (++i < TEX_SIZE)
	{
		while (u < TEX_SIZE)
		{
			uint8_t	a = img_test->pixels[(i * v1 + u)];
			uint8_t	r = img_test->pixels[(i * (v1 + 4) + u)];
			uint8_t	g = img_test->pixels[(i * (v1 + 8) + u)];
			uint8_t	b = img_test->pixels[(i * (v1 + 12) + u)];
			printf("r %d g %d b %d a %d\n", r, g, b, a);
			mlx_put_pixel(img, i, u, get_rgba(r, g, b, a));
			u++;
		}
		u = 0;
	}
	mlx_image_to_window(cub->mlx, img, 0, 0);
	mlx_image_to_window(cub->mlx, img_test, 0, 70);
}

void	ft_load(t_cub *cub)
{
	load_texture_tmp(cub->elements);
	cub->windows_img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	draw_outdoor(cub);
	init_player(cub);
	draw_rays(cub);
	mlx_image_to_window(cub->mlx, cub->windows_img, 0, 0);
	minimap(cub);
	test(cub);
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
