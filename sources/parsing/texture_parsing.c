/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:24:44 by smunio            #+#    #+#             */
/*   Updated: 2023/10/22 02:05:00 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	which_texture(t_elements *elements, char *line)
{
	while (!is_alpha(*line))
		line++;
	if (!ft_strncmp(line, "NO", 2))
		store_text_path(elements, 'N', line);
	else if (!ft_strncmp(line, "SO", 2))
		store_text_path(elements, 'S', line);
	else if (!ft_strncmp(line, "EA", 2))
		store_text_path(elements, 'E', line);
	else if (!ft_strncmp(line, "WE", 2))
		store_text_path(elements, 'W', line);
	else
		printf("Error\nWrong texture identifier or format\n");
}

void	store_text_path(t_elements *elements, char c, char *line)
{
	while (is_alpha(*line))
		line++;
	while (is_space(*line))
		line++;
	if (c == 'E')
		elements->east_path = ft_strdup(line);
	else if (c == 'W')
		elements->west_path = ft_strdup(line);
	else if (c == 'S')
		elements->south_path = ft_strdup(line);
	else if (c == 'N')
		elements->north_path = ft_strdup(line);
	else
		printf("Error\nMissing path\n");
	load_texture(elements, c);
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

void	load_texture(t_elements *elements, char c)
{
	if (c == 'N')
	{
		elements->north_texture = malloc(sizeof(mlx_texture_t));
		elements->north_texture = mlx_load_png(elements->north_path);
	}
	else if (c == 'S')
	{
		elements->south_texture = malloc(sizeof(mlx_texture_t));
		elements->south_texture = mlx_load_png(elements->south_path);
	}
	else if (c == 'E')
	{
		elements->east_texture = malloc(sizeof(mlx_texture_t));
		elements->east_texture = mlx_load_png(elements->east_path);
	}
	else if (c == 'W')
	{
		elements->west_texture = malloc(sizeof(mlx_texture_t));
		elements->west_texture = mlx_load_png(elements->west_path);
	}
}
