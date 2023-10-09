/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:24:44 by smunio            #+#    #+#             */
/*   Updated: 2023/10/07 14:17:11 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	store_text_path(t_elements *elements, char *line)
{
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
		printf("Error\nWrong texture identifier\n");
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
		printf("Error\nPath to texture should look like ./path\n");
	if (c == 'N')
	{
		if (!open_file(line))
			elements->north = ft_strdup(line);
	}
	else if (c == 'S')
	{
		if (!open_file(line))
			elements->south = ft_strdup(line);
	}
	else if (c == 'E')
	{
		if (!open_file(line))
			elements->east = ft_strdup(line);
	}
	else if (c == 'W')
	{
		if (!open_file(line))
			elements->west = ft_strdup(line);
	}
}
