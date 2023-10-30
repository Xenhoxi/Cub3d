/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 23:50:45 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/30 13:26:20 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	*cub;

	(void)argc;
	cub = setup_cub();
	if (argc != 2 || check_file(argv))
		return (1);
	parsing(argv[1], cub);
	ft_free_parsing(cub);
	if (!cub->parsing_error)
	{
		run(cub);
		ft_free_all(cub);
	}
	return (0);
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
}

void	ft_load(t_cub *cub)
{
	convert_texture_to_image(cub);
	cub->windows_img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	cub->windows_img_door = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	draw_outdoor(cub);
	init_player(cub);
	init_door(cub);
	ray_cast(cub);
	mlx_image_to_window(cub->mlx, cub->windows_img, 0, 0);
	mlx_image_to_window(cub->mlx, cub->windows_img_door, 0, 0);
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
	door_update(cub);
	delta_time(cub);
	draw_update(cub);
	return ;
}
