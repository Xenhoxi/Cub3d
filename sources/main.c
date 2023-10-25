/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 23:50:45 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/25 13:17:07 by ljerinec         ###   ########.fr       */
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

void	mouse_hook(t_cub *cub)
{
	int	old_x;
	int	old_y;

	old_y = 0;
	old_x = WIN_WIDTH / 2;
	mlx_get_mouse_pos(cub->mlx, &old_x, &old_y);
	if (old_x > WIN_WIDTH / 2)
	{
		right_rotation(cub);
		cub->mouse_moved = 1;
	}
	if (old_x < WIN_WIDTH / 2)
	{
		left_rotation(cub);
		cub->mouse_moved = 1;
	}
	mlx_set_mouse_pos(cub->mlx, WIN_WIDTH / 2, WIN_HEIGHT / 2);

}

void	ft_load(t_cub *cub)
{
	convert_texture_to_image(cub);
	cub->windows_img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	draw_outdoor(cub);
	init_player(cub);
	draw_rays(cub);
	mlx_image_to_window(cub->mlx, cub->windows_img, 0, 0);
	draw_minimap(cub);
	mlx_set_cursor(cub->mlx, NULL);
	mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(cub->mlx, WIN_WIDTH / 2, WIN_HEIGHT / 2);
}

void	ft_update(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	key_hook(cub);
	mouse_hook(cub);
	player_update(cub);
	delta_time(cub);
	return ;
}

t_image	*setup_image(t_cub *cub)
{
	t_image	*image_struct;

	image_struct = malloc(sizeof(t_image));
	if (!image_struct)
		return (NULL);
	image_struct->door_img = create_img_full(TSMAP, cub->mlx, 0xFF6600FF);
	image_struct->wall_img = create_img_full(TSMAP, cub->mlx, 0x808080FF);
	image_struct->floor_img = create_img_full(TSMAP, cub->mlx, 0xC8AD7FFF);
	image_struct->transparent_img = create_img_cf(TSMAP, TSMAP, cub->mlx, 0x808080FF);
	return (image_struct);
}

void	run(t_cub *cub)
{
	cub->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Black ops 2 Zombies", true);
	if (!cub->mlx)
		exit(EXIT_FAILURE);
	cub->image = setup_image(cub);
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
