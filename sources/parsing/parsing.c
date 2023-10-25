/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smunio <smunio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 20:44:15 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/25 16:25:18 by smunio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parsing(char *map, t_cub *cub)
{
	char	*line;
	int		fd;
	t_poop	poop;

	setup_poop(&poop);
	fd = selected_fd(map);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		sort_element(cub, line, &poop);
		line = get_next_line(fd);
	}
	// print_char_map(cub->map->map);
	// print_elements(cub->elements);
	if (parsing_checker(cub))
		cub->parsing_error = 1;
	free(line);
	close(fd);
}

int	parsing_checker(t_cub *cub)
{
	if (!cub->map->map)
		return (error_msg("Map missing", cub), 0);
	if (!map_is_valid(cub->map->map))
		if (!map_is_closed(cub->map->map))
			if (!element_checker(cub->elements))
				return (0);
	return (1);
}
