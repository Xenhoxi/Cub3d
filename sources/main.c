/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 23:50:45 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/29 15:16:08 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_hook(t_cub *cub)
{
	mlx_t	*mlx;

	mlx = cub->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void	delta_time(t_cub *cub)
{
	double		current_time;

	current_time = mlx_get_time();
	cub->dt = current_time - cub->prev_dt;
	cub->prev_dt = current_time;
	printf("dt = %f\r", cub->dt);
	fflush(stdout);
}

u_int32_t	get_color_coord(int x, int y, mlx_image_t *img)
{
	uint32_t	*pixel;
	u_int32_t	color;

	pixel = NULL;
	pixel = (uint32_t *)(img->pixels + (x + y * TEX_SIZE) * sizeof(uint32_t));
	color = *pixel;
	return (get_rgba_tex(color));
	return (0);
}

void	ft_load(t_cub *cub)
{
	convert_texture_to_image(cub);
	cub->windows_img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->windows_img_door = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	draw_outdoor(cub);
	init_player(cub);
	init_door(cub);
	draw_rays(cub);
	mlx_image_to_window(cub->mlx, cub->windows_img, 0, 0);
	mlx_image_to_window(cub->mlx, cub->windows_img_door, 0, 0);
	draw_minimap(cub);
	mlx_set_cursor(cub->mlx, NULL);
	mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(cub->mlx, WIN_WIDTH / 2, WIN_HEIGHT / 2);
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
		draw_rays(cub);
		draw_minimap(cub);
		cub->mouse_moved = 0;
		cub->map->door_moving = 0;
	}
}

void	ft_update(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	key_hook(cub);
	mouse_hook(cub);
	player_update(cub);
	door_update(cub);
	delta_time(cub);
	draw_update(cub);
	return ;
}

mlx_texture_t	**load_door_png(void)
{
	mlx_texture_t	**door_array;

	door_array = malloc(sizeof(mlx_texture_t *) * 12);
	door_array[0] = mlx_load_png("sources/textures/door_frames/image_door_001.png");
	door_array[1] = mlx_load_png("sources/textures/door_frames/image_door_002.png");
	door_array[2] = mlx_load_png("sources/textures/door_frames/image_door_003.png");
	door_array[3] = mlx_load_png("sources/textures/door_frames/image_door_004.png");
	door_array[4] = mlx_load_png("sources/textures/door_frames/image_door_005.png");
	door_array[5] = mlx_load_png("sources/textures/door_frames/image_door_006.png");
	door_array[6] = mlx_load_png("sources/textures/door_frames/image_door_007.png");
	door_array[7] = mlx_load_png("sources/textures/door_frames/image_door_008.png");
	door_array[8] = mlx_load_png("sources/textures/door_frames/image_door_009.png");
	door_array[9] = mlx_load_png("sources/textures/door_frames/image_door_010.png");
	door_array[10] = mlx_load_png("sources/textures/door_frames/image_door_011.png");
	door_array[11] = NULL;
	return (door_array);
}

void	door_png_to_textures(t_cub *cub, t_image *images)
{
	images->door_img = malloc(sizeof(mlx_image_t *) * 12);
	images->door_img[0] = mlx_texture_to_image(cub->mlx, images->door_tex[0]);
	images->door_img[1] = mlx_texture_to_image(cub->mlx, images->door_tex[1]);
	images->door_img[2] = mlx_texture_to_image(cub->mlx, images->door_tex[2]);
	images->door_img[3] = mlx_texture_to_image(cub->mlx, images->door_tex[3]);
	images->door_img[4] = mlx_texture_to_image(cub->mlx, images->door_tex[4]);
	images->door_img[5] = mlx_texture_to_image(cub->mlx, images->door_tex[5]);
	images->door_img[6] = mlx_texture_to_image(cub->mlx, images->door_tex[6]);
	images->door_img[7] = mlx_texture_to_image(cub->mlx, images->door_tex[7]);
	images->door_img[8] = mlx_texture_to_image(cub->mlx, images->door_tex[8]);
	images->door_img[9] = mlx_texture_to_image(cub->mlx, images->door_tex[9]);
	images->door_img[10] = mlx_texture_to_image(cub->mlx, images->door_tex[10]);
	images->door_img[11] = NULL;
}

t_image	*setup_image(t_cub *cub)
{
	t_image	*images;

	images = malloc(sizeof(t_image));
	if (!images)
		return (NULL);
	images->map_door = create_img_full(TSMAP, cub->mlx, 0xFF660050);
	images->map_player = create_img_full(TSMAP, cub->mlx, 0xFF6600FF);
	images->map_wall = create_img_full(TSMAP, cub->mlx, 0x808080FF);
	images->map_floor = create_img_full(TSMAP, cub->mlx, 0xC8AD7FFF);
	images->map_void = create_img_cf(TSMAP, TSMAP, cub->mlx, 0xFF808080);
	images->door_tex = load_door_png();
	door_png_to_textures(cub, images);
	return (images);
}

void	run(t_cub *cub)
{
	cub->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Black ops 2 Zombies", true);
	if (!cub->mlx)
		exit(EXIT_FAILURE);
	cub->image = setup_image(cub);
	printf("Press 'M' to enable mouse and 'N' to disable\n");
	ft_load(cub);
	mlx_set_mouse_pos(cub->mlx, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	mlx_loop_hook(cub->mlx, ft_update, (void *)cub);
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
	if (!cub->parsing_error)
		run(cub);
	return (0);
}
