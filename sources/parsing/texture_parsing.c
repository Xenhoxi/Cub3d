/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:24:44 by smunio            #+#    #+#             */
/*   Updated: 2023/10/10 13:54:46 by sammeuss         ###   ########.fr       */
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
		open_texture_path(elements, line, 'N');
	else if (!ft_strncmp(line, "SO", 2))
		open_texture_path(elements, line, 'S');
	else if (!ft_strncmp(line, "EA", 2))
		open_texture_path(elements, line, 'E');
	else if (!ft_strncmp(line, "WE", 2))
		open_texture_path(elements, line, 'W');
	else
		printf("Error\nWrong texture identifier or format\n");
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

void	open_texture_path(t_elements *elements, char *line, char c)
{
	while (*line != '.')
		line++;
	if (!line || line[1] != '/')
		printf("Error\nPath to texture syntax is -> ./path\n");
	if (c == 'N')
	{
		if (!open_file(line))
			elements->north_path = ft_strdup(line);
	}
	else if (c == 'S')
	{
		if (!open_file(line))
			elements->south_path = ft_strdup(line);
	}
	else if (c == 'E')
	{
		if (!open_file(line))
			elements->east_path = ft_strdup(line);
	}
	else if (c == 'W')
	{
		if (!open_file(line))
			elements->west_path = ft_strdup(line);
	}
}

void	load_textures(t_elements *elements)
{
	if (elements->east_path && elements->north_path
		&& elements->south_path && elements->west_path)
	{
		mlx_load_png(elements->east_path);
		mlx_load_png(elements->west_path);
		mlx_load_png(elements->south_path);
		mlx_load_png(elements->north_path);
		return ;
	}	
	printf("Error\nMissing some textures, can't load them\n");
}
