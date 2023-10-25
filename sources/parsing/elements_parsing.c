/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smunio <smunio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:33:31 by sammeuss          #+#    #+#             */
/*   Updated: 2023/10/25 13:16:09 by smunio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_element(t_cub	*cub, char *line)
{
	static int		parsing_map;
	char			*type;

	type = element_type(line);
	if (!line || !type)
		return ;
	else if (!ft_strncmp(type, "TEXTURE_PATH", 13))
	{
		if (parsing_map == 1)
			return (error_msg("Map is always last element\n"));
		which_texture(cub, line);
	}
	else if (!ft_strncmp(type, "MAP", 4))
	{
		parsing_map = 1;
		cub->map->map = array_join(cub->map->map, line);
	}
	else if (!ft_strncmp(type, "COLOR", 6))
	{
		if (parsing_map == 1)
			return (error_msg("Map is always last element\n"));
		store_color(cub->elements, line);
	}
	else if (line[0] != '\n')
		printf("%s\n", type);
}

char	*element_type(char *line)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (is_alpha(line[i]))
	{
		if (line[i] == 'F' || line[i] == 'C')
		{
			if (is_color(line, i))
				return ("COLOR");
		}
		else if (is_texture(line, i))
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

int	element_checker(t_elements *elements)
{
	if (elements->ceiling_color != 0)
		if (elements->floor_color != 0)
			if (elements->east_path != NULL)
				if (elements->north_path != NULL)
					if (elements->south_path != NULL)
						if (elements->west_path != NULL)
							return (0);
	error_msg("Missing colors or textures");
	return (1);
}
