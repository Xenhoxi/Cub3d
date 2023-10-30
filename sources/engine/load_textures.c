/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:13:22 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/30 12:58:47 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_texture_t	**load_door_png(void)
{
	mlx_texture_t	**door_array;

	door_array = malloc(sizeof(mlx_texture_t *) * 12);
	door_array[0] = mlx_load_png("sources/textures/door_frames/door_001.png");
	door_array[1] = mlx_load_png("sources/textures/door_frames/door_002.png");
	door_array[2] = mlx_load_png("sources/textures/door_frames/door_003.png");
	door_array[3] = mlx_load_png("sources/textures/door_frames/door_004.png");
	door_array[4] = mlx_load_png("sources/textures/door_frames/door_005.png");
	door_array[5] = mlx_load_png("sources/textures/door_frames/door_006.png");
	door_array[6] = mlx_load_png("sources/textures/door_frames/door_007.png");
	door_array[7] = mlx_load_png("sources/textures/door_frames/door_008.png");
	door_array[8] = mlx_load_png("sources/textures/door_frames/door_009.png");
	door_array[9] = mlx_load_png("sources/textures/door_frames/door_010.png");
	door_array[10] = mlx_load_png("sources/textures/door_frames/door_011.png");
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
	images->map_void = create_img_cf(TSMAP, TSMAP, cub->mlx, 0x808080FF);
	images->door_tex = load_door_png();
	door_png_to_textures(cub, images);
	return (images);
}
