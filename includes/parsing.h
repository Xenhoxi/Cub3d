/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:19:46 by smunio            #+#    #+#             */
/*   Updated: 2023/10/24 15:12:45 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

# define PARSING_H

typedef struct s_cub		t_cub;
typedef struct s_map		t_map;
typedef struct s_player		t_player;
typedef struct s_elements	t_elements;

// setup_structures
t_cub		*setup_cub(void);
t_map		*setup_map(void);
t_elements	*setup_elements(void);

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
void		find_spawn(char **map, int *x, int *y);
int			open_file(char *path);
void		print_elements(t_elements *elements);

// elements_parsing
char		*element_type(char *line);
void		sort_element(t_cub	*cub, char *line);
int			element_checker(t_elements *elements);

// color_parsing
uint64_t	convert_rgb(char *line);
int			is_color(char *line, int i);
int			color_check(int nb_count, int comma_count);
void		store_color(t_elements *elements, char *line);
uint32_t	get_rgba(u_int32_t color);

// texture_parsing
void		convert_texture_to_image(t_cub *cub);
void		which_texture(t_cub *cub, char *line);
int			is_texture(char *line, int i);
void		store_text_path(t_cub *cub, char c, char *line);
void		load_texture(t_cub *cub, char c);
#endif