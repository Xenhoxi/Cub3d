/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:24:44 by smunio            #+#    #+#             */
/*   Updated: 2023/10/21 20:54:57 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	store_text_path(t_elements *elements, char *line)
{
	while (!is_alpha(*line))
		line++;
	if (!ft_strncmp(line, "NO", 2))
	{
		elements->north_path = ft_strdup(line);
		load_texture(elements, 'N', line);
	}
	else if (!ft_strncmp(line, "SO", 2))
	{
		load_texture(elements, 'S', line);
		elements->south_path = ft_strdup(line);
	}
	else if (!ft_strncmp(line, "EA", 2))
	{
		load_texture(elements, 'E', line);
		elements->east_path = ft_strdup(line);
	}
	else if (!ft_strncmp(line, "WE", 2))
	{
		load_texture(elements, 'W', line);
		elements->west_path = ft_strdup(line);
	}
	else
		printf("Error\nWrong texture identifier or format\n");
}

void	load_texture(t_elements *elements, char c, char *line)
{
	while (is_alpha(*line))
		line++;
	while (!is_alpha(*line))
		line++;
	printf("%s\n", line);
	if (c == 'E')
		elements->east_texture = mlx_load_png(line);
	else if (c == 'W')
		elements->west_texture = mlx_load_png(line);
	else if (c == 'S')
		elements->south_texture = mlx_load_png(line);
	else if (c == 'N')
		elements->north_texture = mlx_load_png(line);
	else
		printf("Error\nMissing texture, can't load\n");
}

int	is_texture(char *line, int i)
{
	if (check_ext(line, ".png") == 1)
		return (printf("Error\nWrong texture extension\nm"));
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
