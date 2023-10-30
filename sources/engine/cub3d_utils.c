/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:07:47 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/29 17:12:18 by ljerinec         ###   ########.fr       */
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
}
