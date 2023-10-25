/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smunio <smunio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:33:31 by sammeuss          #+#    #+#             */
/*   Updated: 2023/10/25 16:31:42 by smunio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_element(t_cub	*cub, char *line, t_poop *poop)
{
	static int		parsing_map;
	char			*type;

	type = element_type(line, poop, cub);
	if (!line || !type)
		return ;
	else if (!ft_strncmp(type, "TEXTURE_PATH", 13))
	{
		if (parsing_map == 1)
			return (error_msg("Map is always last element\n", cub));
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
			return (error_msg("Map is always last element\n", cub));
		store_color(cub->elements, line, poop, cub);
	}
	else if (line[0] != '\n')
		printf("%s\n", type);
}

char	*element_type(char *line, t_poop	*poop, t_cub *cub)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (is_alpha(line[i]))
	{
		if (line[i] == 'F' || line[i] == 'C')
		{
			if (is_color(line, i, poop, cub))
				return ("COLOR");
		}
		else if (is_texture(line, i, cub))
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
