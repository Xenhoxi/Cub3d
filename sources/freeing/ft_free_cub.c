/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_cub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:44:43 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/30 15:58:29 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_elements(t_cub *cub, t_elements *elements)
{
	mlx_delete_image(cub->mlx, elements->west_image);
	mlx_delete_image(cub->mlx, elements->east_image);
	mlx_delete_image(cub->mlx, elements->south_image);
	mlx_delete_image(cub->mlx, elements->north_image);
	mlx_delete_texture(elements->west_texture);
	mlx_delete_texture(elements->south_texture);
	mlx_delete_texture(elements->north_texture);
	mlx_delete_texture(elements->east_texture);
	free(elements);
}

void	ft_free_cub(t_cub *cub)
{
	mlx_delete_image(cub->mlx, cub->windows_img);
	mlx_delete_image(cub->mlx, cub->windows_img_door);
	mlx_terminate(cub->mlx);
	free(cub);
}

void	ft_free_all(t_cub *cub)
{
	free(cub->v);
	ft_free_player(cub, cub->player);
	ft_free_image(cub, cub->image);
	ft_free_map(cub->map);
	ft_free_elements(cub, cub->elements);
	ft_free_cub(cub);
}

void	ft_free_parsing(t_cub *cub)
{
	free(cub->elements->north_path);
	free(cub->elements->south_path);
	free(cub->elements->west_path);
	free(cub->elements->east_path);
}
