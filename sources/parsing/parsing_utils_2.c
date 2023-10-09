/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:45:48 by smunio            #+#    #+#             */
/*   Updated: 2023/10/09 12:37:37 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file(char **argv)
{
	if (check_ext(argv[1], ".cub") || file_exist(argv[1]))
		return (1);
	return (0);
}

int	selected_fd(char *map)
{
	int	fd;

	fd = open(map, O_RDONLY);
	return (fd);
}

int	open_file(char *path)
{
	if (open(path, O_RDONLY) == -1)
	{
		printf("Error\nFailed to open ->%s\n", path);
		return (1);
	}
	return (0);
}

void	print_elements(t_elements *elements)
{
	printf("ceiling color = %d\n", elements->ceiling_color);
	printf("floor color = %d\n", elements->floor_color);
	printf("north = %s\n", elements->north);
	printf("south = %s\n", elements->south);
	printf("east = %s\n", elements->east);
	printf("west = %s\n", elements->west);
}
