/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:00:24 by smunio            #+#    #+#             */
/*   Updated: 2023/10/27 15:33:08 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H

# define STRUCT_H

# include "../MLX42/include/MLX42/MLX42.h"

typedef	struct	s_vector
{
	int	x;
	int	y;
}	t_vector;

typedef	struct	s_var
{
	int	start;
	int	len;
	int	index;
	int	comma;
	int	mouse;
	int	error;
}	t_var;

typedef struct s_line
{
	int			i;
	mlx_image_t	*img;
	char		side;
	double		reel_dist;
	int			pixels;
	int			map_x;
	int			map_y;
	double		dir_x;
	double		dir_y;
	int			step_x;
	int			step_y;
	double		angle;
	double		lenght_x;
	double		lenght_y;
	double		dx;
	double		dy;
	double		sx;
	double		sy;
	double		dx_p;
	double		dy_p;
	double		s_x;
	double		s_y;
	double		end_x;
	double		end_y;
	int			is_door;
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
	u_int32_t		floor_color;
	u_int32_t		ceiling_color;
}	t_elements;

typedef struct s_player
{
	t_line		*line;
	mlx_image_t	*img_map;
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
	int		**array;
	int		map_index;
	int		x;
	int		y;
	int		height;
	int		width;
	int		height_px;
	int		width_px;
}	t_map;

typedef struct s_image
{
	mlx_image_t		*map_floor;
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
	t_image			*image;
	t_player		*player;
	t_map			*map;
	t_elements		*elements;
	int				parsing_error;
	double			dt;
	double			prev_dt;
	int				mouse_moved;
	int				game_on;
	t_var			v;
}	t_cub;

#endif