/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:24:44 by smunio            #+#    #+#             */
/*   Updated: 2023/10/30 18:03:19 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	store_text_path(t_cub *cub, char c, char *line)
{
	while (is_alpha(*line))
		line++;
	while (is_space(*line))
		line++;
	if (c == 'E')
		cub->elements->east_path = ft_substr(line, 0, ft_strlen(line) - 1);
	else if (c == 'W')
		cub->elements->west_path = ft_substr(line, 0, ft_strlen(line) - 1);
	else if (c == 'S')
		cub->elements->south_path = ft_substr(line, 0, ft_strlen(line) - 1);
	else if (c == 'N')
		cub->elements->north_path = ft_substr(line, 0, ft_strlen(line) - 1);
	else
		error_msg("Missing path", cub);
	if (cub->parsing_error == 0)
	{
		cub->v->nb_t++;
		load_texture(cub, c);
	}
}

int	is_texture(char *line, int i, t_cub *cub, char *ext)
{
	int	u;
	int	j;

	u = 0;
	j = 0;
	while (line[u] && line[i] != '\n')
		u++;
	if (u < 5)
		return (error_msg("Missing text path", cub), 0);
	u -= 5;
	while (line[u] && ext[j] && line[u] != '\n')
	{
		if (line[u++] != ext[j++])
			return (error_msg("Wrong texture extension", cub), 0);
	}
	if (line[i] == 'S' && line[i + 1] == 'O')
		return (1);
	else if (line[i] == 'N' && line[i + 1] == 'O')
		return (1);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		return (1);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		return (1);
	else
		return (error_msg("Wrong texture identifier", cub), 0);
}

void	load_texture(t_cub *cub, char c)
{
	if (c == 'N')
	{
		cub->elements->north_texture = mlx_load_png(cub->elements->north_path);
		if (cub->elements->north_texture == NULL)
			return (error_msg("Tex. load failed", cub));
	}
	else if (c == 'S')
	{
		cub->elements->south_texture = mlx_load_png(cub->elements->south_path);
		if (cub->elements->south_texture == NULL)
			return (error_msg("Tex. load failed", cub));
	}
	else if (c == 'E')
	{
		cub->elements->east_texture = mlx_load_png(cub->elements->east_path);
		if (cub->elements->east_texture == NULL)
			return (error_msg("Tex. load failed", cub));
	}
	else if (c == 'W')
	{
		cub->elements->west_texture = mlx_load_png(cub->elements->west_path);
		if (cub->elements->west_texture == NULL)
			return (error_msg("Tex. load failed", cub));
	}
}

void	which_texture_0(t_cub *cub, char *line)
{
	while (!is_alpha(*line))
		line++;
	if (!ft_strncmp(line, "NO", 2))
	{
		if (cub->elements->north_path != NULL)
			return (error_msg("NO texture already filled", cub));
		store_text_path(cub, 'N', line);
	}
	else if (!ft_strncmp(line, "SO", 2))
	{
		if (cub->elements->south_path != NULL)
			return (error_msg("SO texture already filled", cub));
		store_text_path(cub, 'S', line);
	}
	else if (!ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "WE", 2))
		which_texture_1(cub, line);
	else
		error_msg("Wrong texture identifier or format", cub);
}

void	which_texture_1(t_cub *cub, char *line)
{
	if (!ft_strncmp(line, "EA", 2))
	{
		if (cub->elements->east_path != NULL)
			return (error_msg("EA texture already filled", cub));
		store_text_path(cub, 'E', line);
	}	
	else if (!ft_strncmp(line, "WE", 2))
	{
		if (cub->elements->west_path != NULL)
			return (error_msg("WE texture already filled", cub));
		store_text_path(cub, 'W', line);
	}
}
