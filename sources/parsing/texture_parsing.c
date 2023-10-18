/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:24:44 by smunio            #+#    #+#             */
/*   Updated: 2023/10/18 09:38:50 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	store_text_path(t_elements *elements, char *line)
{
	if (check_ext(line, ".png") == 1)
		return ;
	while (!is_alpha(*line))
		line++;
	if (!ft_strncmp(line, "NO", 2))
		load_texture(elements, 'N');
	else if (!ft_strncmp(line, "SO", 2))
		load_texture(elements, 'S');
	else if (!ft_strncmp(line, "EA", 2))
		load_texture(elements, 'E');
	else if (!ft_strncmp(line, "WE", 2))
		load_texture(elements, 'W');
	else
		printf("Error\nWrong texture identifier or format\n");
}

void	load_texture(t_elements *elements, char c)
{
	if (c == 'E')
		mlx_load_png(elements->east_path);
	else if (c == 'W')
		mlx_load_png(elements->west_path);
	else if (c == 'S')
		mlx_load_png(elements->south_path);
	else if (c == 'N')
		mlx_load_png(elements->north_path);
	else
		printf("Error\nMissing texture, can't load\n");
}

int	is_texture(char *line, int i)
{
	if (line[i] == 'S' && line[i + 1] == 'O')
		return (1);
	else if (line[i] == 'N' && line[i + 1] == 'O')
		return (1);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		return (1);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		return (1);
	else
		return (printf("Error\nWrong texture identifier\n"), 0);
}
