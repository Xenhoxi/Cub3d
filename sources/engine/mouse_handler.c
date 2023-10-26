/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:58:16 by sammeuss          #+#    #+#             */
/*   Updated: 2023/10/26 13:56:27 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mouse_on_off(t_cub *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_M))
		cub->v.mouse = 1;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_N))
		cub->v.mouse = 0;
	if (cub->v.mouse == 1)
	{
		mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_HIDDEN);
		mlx_set_mouse_pos(cub->mlx, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	}
	else
		mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_NORMAL);
}

void	mouse_hook(t_cub *cub)
{
	int	old_x;
	int	old_y;

	old_y = 0;
	old_x = WIN_WIDTH / 2;
	mlx_get_mouse_pos(cub->mlx, &old_x, &old_y);
	mouse_on_off(cub);
	if (cub->v.mouse == 1)
	{
		if (old_x > WIN_WIDTH / 2)
		{
			right_rotation(cub, ((double)old_x -(WIN_WIDTH / 2)));
			cub->mouse_moved = 1;
		}
		if (old_x < WIN_WIDTH / 2)
		{
			left_rotation(cub, ((double)(WIN_WIDTH / 2) - old_x));
			cub->mouse_moved = 1;
		}
	}
}
