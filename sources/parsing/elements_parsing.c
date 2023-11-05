/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:33:31 by sammeuss          #+#    #+#             */
/*   Updated: 2023/11/05 20:55:12 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_element(t_cub	*cub, char *line)
{
	char			*type;

	type = element_type(line, cub);
	if (!line || !type)
		return ;
	else if (!ft_strncmp(type, "TEXTURE_PATH", 13))
	{
		if (cub->v->parsing_map == 1)
			return (error_msg("Map is always last element", cub));
		which_texture_0(cub, line);
	}
	else if (!ft_strncmp(type, "MAP", 4))
	{
		if (cub->v->nb_c != 2 && cub->v->nb_t != 4)
			return (error_msg("Map is always last element", cub));
		cub->v->parsing_map = 1;
		cub->map->map = array_join(cub->map->map, line);
	}
	else if (!ft_strncmp(type, "COLOR", 6))
	{
		if (cub->v->parsing_map == 1)
			return (error_msg("Map is always last element", cub));
		store_color(line, cub);
	}
}

char	*element_type(char *line, t_cub *cub)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (is_alpha(line[i]))
	{
		if (is_alpha(line[i]) && is_space(line[i + 1]))
		{
			if (is_color(line, i, cub))
				return ("COLOR");
		}
		else if (is_alpha(line[i]) && is_alpha(line[i + 1])
			&& is_texture(line, i, cub, ".png"))
			return ("TEXTURE_PATH");
		else
			return ("WRONG ELEMENT IDENTIFIER");
	}
	else if (line[i] == '1')
		return ("MAP");
	else
		return ("WRONG ELEMENT SYNTAX");
	return (NULL);
}

int	element_checker(t_elements *elements, t_cub *cub)
{
	if (elements->ceiling_color != 256)
		if (elements->floor_color != 256)
			if (elements->east_path != NULL)
				if (elements->north_path != NULL)
					if (elements->south_path != NULL)
						if (elements->west_path != NULL)
							return (0);
	error_msg("Missing colors or textures", cub);
	return (1);
}

int	texture_identifier_checker(char *line, t_cub *cub)
{
	int	i;

	i = 0;
	while (is_space(*line))
		line++;
	if (!is_alpha(*line))
		return (error_msg("Wrong texture identifier", cub), 1);
	while (is_alpha(line[i]))
		i++;
	if (i > 2)
		return (error_msg("Wrong texture identifier", cub), 1);
	if (!is_space(line[i]))
		return (error_msg("Texture identifier are be followed by a white space"
				, cub), 1);
	return (0);
}
