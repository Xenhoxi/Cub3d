/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 23:43:06 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/30 12:02:20 by ljerinec         ###   ########.fr       */
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
# define TEX_SIZE 70
# define ROTSPEED 3500
# define SPEED 3.5
# define TRUE 1
# define FALSE 0
# define NB_FRM_DOOR 11

// Map
# define TSMAP 20
# define NB_TILE 6

// main.c
void			run(t_cub *cub);
void			ft_load(t_cub *cub);
void			ft_update(void *param);

// cub3d_utils.c
void			key_hook(t_cub *cub);
void			delta_time(t_cub *cub);

/*----------*/
/* TEXTURES */
/*----------*/

// loading_img.c
mlx_texture_t	**load_door_png(void);
void			door_png_to_textures(t_cub *cub, t_image *images);
t_image			*setup_image(t_cub *cub);

// colors_utils.c
u_int32_t		get_color_coord(int x, int y, mlx_image_t *img);
mlx_image_t		*create_img_cf(int width, int height, mlx_t *mlx, uint64_t color);
mlx_image_t		*create_img_full(int size, mlx_t *mlx, uint64_t color);
mlx_image_t		*chose_image(t_cub *cub, t_line *line);

/*----------*/
/*  PLAYER  */
/*----------*/

// player.c
void			player_update(t_cub *cub);
void			draw_player(t_cub *cub);
void			init_player(t_cub *cub);
void			find_spawn(char **map, int *x, int *y);

// init_player.c
void			setup_start_dir(t_cub *cub, char direction);
void			set_north(t_cub *cub);
void			set_south(t_cub *cub);
void			set_west(t_cub *cub);
void			set_east(t_cub *cub);

// player_movement.c
int				is_wall(char tile_type);
void			move_forward(t_cub *cub);
void			move_backward(t_cub *cub);
void			move_left(t_cub *cub);
void			move_right(t_cub *cub);

// player_rotation.c
void			right_rotation(t_cub *cub, double rotspeed);
void			left_rotation(t_cub *cub, double rotspeed);

/*-------------*/
/* RAY-CASTING */
/*-------------*/

// ray_casting.c
void			scale_for_ray(t_cub *cub, t_line *line);
void			calcul_offset(t_line *line);
void			dda_algorithm(t_cub *cub, t_line *line);
void			ray_cast(t_cub *cub);
int				is_entity(char tile_check, t_line *line);

// draw_environnement.c
void			drawline_wall(t_cub *cub, t_line *line, int tex_x);
void			drawtexture(t_line *line, t_cub *cub);
void			draw_vision(t_cub *cub, t_line *line);
void			draw_outdoor(t_cub *cub);
void			draw_update(t_cub *cub);

/*----------*/
/* MINI-MAP */
/*----------*/

// minimap.c
int				is_spawn(char type);
mlx_image_t		*chose_image_to_draw(t_cub *cub, int x, int y);
void			put_image_to_image(t_cub *cub, t_vector map, t_vector pos);
void			draw_minimap(t_cub *cub);

/*---------*/
/*  DOORS  */
/*---------*/

// init_doors.c
t_doors			*create_door(int x, int y);
int				count_doors(char **map);
void			init_door(t_cub *cub);

// control_doors.c
int				is_player_close_to_door(t_cub *cub, t_doors *door);
void			open_door(t_cub *cub, t_doors *door);
void			close_door(t_cub *cub, t_doors *door);
void			door_update(t_cub *cub);

// draw_doors.c
int				find_curr_img_door(t_cub *cub, t_line *line);
void			drawtexture_doors(t_line *line, t_cub *cub);
void			draw_doors(t_cub *cub, t_line *line);
void			clear_vertical_stripe(t_cub *cub, t_line *line);

/*---------*/
/*  MOUSE  */
/*---------*/

// mouse_handler
void			mouse_hook(t_cub *cub);
void			mouse_on_off(t_cub *cub);

/*---------*/
/* FREEING */
/*---------*/

// free_utils
void			free_int_array(int	**array, char **map);

#endif