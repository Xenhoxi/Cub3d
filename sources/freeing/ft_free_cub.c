/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_cub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:44:43 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/30 13:26:42 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_player(t_cub *cub, t_player *player)
{
	mlx_delete_image(cub->mlx, player->ray_img);
	free(player);
}

void	ft_free_image(t_cub *cub, t_image *image)
{
	int	i;

	mlx_delete_image(cub->mlx, image->map_floor);
	mlx_delete_image(cub->mlx, image->map_player);
	mlx_delete_image(cub->mlx, image->map_wall);
	mlx_delete_image(cub->mlx, image->map_door);
	mlx_delete_image(cub->mlx, image->map_void);
	i = -1;
	while (image->door_tex[++i])
		mlx_delete_texture(image->door_tex[i]);
	free(image->door_tex);
	i = -1;
	while (image->door_img[++i])
		mlx_delete_image(cub->mlx, image->door_img[i]);
	free(image->door_img);
	free(image);
}

void	ft_free_map(t_map *map)
{
	int	i;

	i = -1;
	while (map->doors[++i])
		free(map->doors[i]);
	free(map->doors);
	i = -1;
	while (map->map[++i])
		free(map->map[i]);
	free(map->map);
	free(map);
}

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
	ft_free_player(cub, cub->player);
	ft_free_image(cub, cub->image);
	ft_free_map(cub->map);
	ft_free_elements(cub, cub->elements);
	ft_free_cub(cub);
	system("leaks cub3d");
}

void	ft_free_parsing(t_cub *cub)
{
	free(cub->elements->north_path);
	free(cub->elements->south_path);
	free(cub->elements->west_path);
	free(cub->elements->east_path);
}
