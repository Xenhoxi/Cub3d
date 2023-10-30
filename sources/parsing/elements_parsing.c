/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:33:31 by sammeuss          #+#    #+#             */
/*   Updated: 2023/10/30 16:59:36 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_element(t_cub	*cub, char *line)
{
	static int		parsing_map;
	char			*type;

	printf("line = %s\n", line);
	type = element_type(line, cub);
	if (!line || !type)
		return ;
	else if (!ft_strncmp(type, "TEXTURE_PATH", 13))
	{
		if (parsing_map == 1)
			return (error_msg("Map is always last element", cub));
		which_texture(cub, line);
	}
	else if (!ft_strncmp(type, "MAP", 4))
	{
		if (cub->v->nb_c != 2 && cub->v->nb_t != 4)
			return (error_msg("Map is always last element", cub));
		parsing_map = 1;
		cub->map->map = array_join(cub->map->map, line);
	}
	else if (!ft_strncmp(type, "COLOR", 6))
	{
		if (parsing_map == 1)
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
				return (cub->v->nb_c++, "COLOR");
		}
		else if (is_texture(line, i, cub, ".png"))
			return (cub->v->nb_t++, "TEXTURE_PATH");
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
	if (elements->ceiling_color != 0)
		if (elements->floor_color != 0)
			if (elements->east_path != NULL)
				if (elements->north_path != NULL)
					if (elements->south_path != NULL)
						if (elements->west_path != NULL)
							return (0);
	error_msg("Missing colors or textures", cub);
	return (1);
}
