/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:59:36 by sammeuss          #+#    #+#             */
/*   Updated: 2023/10/30 15:58:36 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_int_array(int	**array, char **map)
{
	int	i;

	i = -1;
	while (++i < ft_array_len_int(array, map))
		free(array[i]);
	free(array);
}

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
