/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:00:24 by smunio            #+#    #+#             */
/*   Updated: 2023/10/30 17:10:26 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H

# define STRUCT_H

# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_var
{
	int	start;
	int	len;
	int	index;
	int	comma;
	int	mouse;
	int	error;
	int	nb_t;
	int	nb_c;
	int	parsing_map;
}	t_var;

typedef struct s_doors
{
	int		x;
	int		y;
	int		state;
	double	current_img;
}	t_doors;

typedef struct s_line
{
	t_vector	map;
	t_vector	step;
	t_vec		dir;
	t_vec		lenght;
	t_vec		pos;
	t_vec		scale;
	t_vector	map_door;
	t_vec		door_lenght;
	char		side;
	int			i;
	double		reel_dist;
	double		angle;
	int			is_door;
	int			door_dist;
	char		door_side;
	int			l_height;
	int			d_start;
	int			d_end;
}	t_line;

typedef struct s_elements
{
	char			*north_path;
	char			*south_path;
	char			*east_path;
	char			*west_path;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*west_texture;
	mlx_image_t		*west_image;
	mlx_image_t		*east_image;
	mlx_image_t		*north_image;
	mlx_image_t		*south_image;
	int				r;
	int				g;
	int				b;
	u_int32_t		floor_color;
	u_int32_t		ceiling_color;
}	t_elements;

typedef struct s_player
{
	mlx_image_t	*ray_img;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		angle;
	double		plane_x;
	double		plane_y;
}	t_player;

typedef struct s_map
{
	char	**map;
	int		door_moving;
	int		**array;
	int		map_index;
	int		x;
	int		y;
	int		height;
	int		width;
	int		height_px;
	int		width_px;
	t_doors	**doors;
}	t_map;

typedef struct s_image
{
	mlx_image_t		*map_floor;
	mlx_image_t		*map_player;
	mlx_image_t		*map_wall;
	mlx_image_t		*map_door;
	mlx_image_t		*map_void;
	mlx_texture_t	**door_tex;
	mlx_image_t		**door_img;
}	t_image;

typedef struct s_cub
{
	mlx_t			*mlx;
	mlx_image_t		*windows_img;
	mlx_image_t		*windows_img_door;
	t_image			*image;
	t_player		*player;
	t_map			*map;
	t_elements		*elements;
	int				parsing_error;
	double			dt;
	double			prev_dt;
	int				mouse_moved;
	t_var			*v;
}	t_cub;

#endif