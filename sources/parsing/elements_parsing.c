/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:33:31 by sammeuss          #+#    #+#             */
/*   Updated: 2023/10/07 15:21:52 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_element(t_cub	*cub, char *line)
{
	char	*type;

	type = element_type(line);
	if (!line || !type)
		return ;
	else if (!ft_strncmp(type, "TEXTURE_PATH", 13))
		store_text_path(cub->elements, line);
	else if (!ft_strncmp(type, "MAP", 4))
		cub->map->map = array_join(cub->map->map, line);
	else if (!ft_strncmp(type, "COLOR", 6))
		store_color(cub->elements, line);
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
