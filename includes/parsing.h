/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smunio <smunio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:19:46 by smunio            #+#    #+#             */
/*   Updated: 2023/10/25 16:31:26 by smunio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

# define PARSING_H

typedef struct s_cub			t_cub;
typedef struct s_map			t_map;
typedef struct s_player			t_player;
typedef struct s_elements		t_elements;
typedef struct s_poop			t_poop;

// setup_structures
t_cub		*setup_cub(void);
t_map		*setup_map(void);
t_elements	*setup_elements(void);
void		setup_poop(t_poop *poop);

// parsing
void		parsing(char *map, t_cub *cub);
int			parsing_checker(t_cub *cub);

// map_parsing_0
int			get_map_index(char **map);
int			is_wrong_char(char c);
int			map_is_closed(char **map);
int			check_sides_char_map(char **map, int i, int u, int r);

//	map_parsing_1
int			map_is_valid(char	**map);
int			check_for_spawn(char **map);
int			ft_array_len_int(int	**array, char **map);

// map_is_possible
int			check_sides_int_array(t_cub *cub, int count, int i, int u);
int			nb_possibilities(int **array, int count, char **map, t_cub *cub);
int			final_check(char **map, int **array);
int			**init_int_array(char **map);

// parsing_utils_0
int			is_digit(char c);
int			is_alpha(char c);
int			is_space(char c);
int			ft_array_len(char	**array);

// parsing_utils_1
void		print_int_array(char **map, int **array);
int			change_case(char **map, int i, int u);
char		**array_join(char **array, char *line);
int			check_ext(char	*file_name, char	*ext);
int			file_exist(char	*file_name);

// parsing_utils_2
int			selected_fd(char *map);
int			check_file(char **argv);
int			open_file(char *path);
void		print_elements(t_elements *elements);
void		error_msg(char *msg, t_cub *cub);

// elements_parsing
char		*element_type(char *line, t_poop	*poop, t_cub *cub);
void		sort_element(t_cub	*cub, char *line, t_poop *poop);
int			element_checker(t_elements *elements, t_cub *cub);

// color_parsing
u_int32_t	convert_rgb(char *line, t_poop *poop);
int			is_color(char *line, int i, t_poop *poop, t_cub *cub);
int			color_check(int nb_count, int comma_count);
void		store_color(t_elements *elements, char *line, t_poop *poop, t_cub *cub);
u_int32_t	get_rgba(u_int32_t color);

// texture_parsing
void		convert_texture_to_image(t_cub *cub);
void		which_texture(t_cub *cub, char *line);
int			is_texture(char *line, int i, t_cub *cub);
void		store_text_path(t_cub *cub, char c, char *line);
void		load_texture(t_cub *cub, char c);
#endif