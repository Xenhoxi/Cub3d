/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 23:43:06 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/09 17:24:23 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "libft/libft.h"
# include "parsing.h"
# include "struct.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>

// Engine
# define TS 64
# define PI 3.14159265359
# define WIN_HEIGHT 920
# define WIN_WIDTH 1280
# define SPEED_SIDE 1.5
# define SPEED 1.8
# define TRUE 1
# define FALSE 0
# define NB_RAY 60

// Map
# define TSMAP 50
# define PM_SIZE 20

/*
	img;
	pixels; Nb pixel a draw
	map_x; map[x][y]
	map_y; map[x][y]
	dir_x; Direction en trigo
	dir_y; Direction en trigo
	step_x; Taille sur une unite de map
	step_y; Taille sur une unite de map
	angle; 
	lenght_x; Taille de la line sur le maillage en X
	lenght_y; Taille de la line sur le maillage en X
	dx; Difference entre start_x et end_x
	dy; Difference entre start_y et end_y
	sx; scaleX pente de la droite sur une unite de X
	sy; scaleY pente de la droite sur une unite de Y
	dx_p; Dif entre start_x et end_x diviser par pixel (draw)
	dy_p; Dif entre start_y et end_y diviser par pixel (draw)
	s_x; start_x
	s_y; start_y
	end_x; Position de fin du segment en X
	end_y; Position de fin du segment en Y
*/

// ray_drawing
void		draw_rays(t_cub *cub);
void		draw_rayline(t_cub *cub, t_line *line);
mlx_image_t	**setup_array_line(void);
void		alloc_rays(t_cub *cub);
// minimap
void		minimap(t_cub *cub);
void		draw_minimap(t_map *map, mlx_t *mlx, mlx_image_t *img_1, mlx_image_t *img_0);
mlx_image_t	*create_img_full(int size, mlx_t *mlx, uint64_t color);

// player
void		player_update(t_cub *cub);
int			entity_hitbox(char **map, int x, int y);
void		init_player(t_cub *cub);
void		find_spawn(char **map, int *x, int *y);
void		draw_direction(t_cub *cub);

// player_movement
void		move_forward(t_cub *cub);
void		move_backward(t_cub *cub);
void		move_left(t_cub *cub);
void		move_right(t_cub *cub);

// minimap_utils
void		print_char_map(char **map);

// free_utils
void		free_int_array(int	**array, char **map);
# define TRUE 1
# define FALSE 0

#endif