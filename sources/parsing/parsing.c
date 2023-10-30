/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 20:44:15 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/30 17:13:15 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parsing(char *map, t_cub *cub)
{
	char	*line;
	int		fd;

	cub->v = setup_var();
	fd = selected_fd(map);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line && cub->parsing_error != 1)
	{
		sort_element(cub, line);
		free(line);
		line = get_next_line(fd);
	}
	if (cub->parsing_error != 1 && parsing_checker(cub))
		cub->parsing_error = 1;
	free(line);
	close(fd);
}

int	parsing_checker(t_cub *cub)
{
	if (cub->v->parsing_map == 0 && cub->v->nb_c == 0
		&& cub->v->nb_t == 0)
		return (error_msg("File seems empty", cub), 1);
	if (!cub->map->map)
		return (error_msg("Map missing", cub), 1);
	if (!map_is_valid(cub->map->map))
		if (!map_is_closed(cub->map->map, cub))
			if (!element_checker(cub->elements, cub))
				return (0);
	return (1);
}
