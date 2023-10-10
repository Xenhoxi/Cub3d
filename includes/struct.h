/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:00:24 by smunio            #+#    #+#             */
/*   Updated: 2023/10/09 15:09:21 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H

# define STRUCT_H

# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_line
{
	mlx_image_t	*img;
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
}	t_line;

typedef struct s_elements
{
	char			*north_path;
	char			*south_path;
	char			*west_path;
	char			*east_path;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*west_texture;
	int				floor_color;
	int				ceiling_color;
}	t_elements;

typedef struct s_player
{
	t_line		*line;
	mlx_image_t	*img_map;
	mlx_image_t	*ray_img;
	int			ray_on;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		angle;
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

typedef struct s_cub
{
	mlx_t			*mlx;
	mlx_texture_t	*texture;
	t_player		*player;
	t_map			*map;
	t_line			**ray_array;
	int				game_on;
	t_elements		*elements;
	int				parsing_error;
}	t_cub;

#endif