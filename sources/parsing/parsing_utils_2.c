/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:45:48 by smunio            #+#    #+#             */
/*   Updated: 2023/10/20 09:19:51 by sammeuss         ###   ########.fr       */
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
	printf("ceiling color = %u\n", elements->ceiling_color);
	printf("floor color = %u\n", elements->floor_color);
	printf("north_text_path = %s\n", elements->north_path);
	printf("south_text_path = %s\n", elements->south_path);
	printf("east_text_path = %s\n", elements->east_path);
	printf("west_text_path = %s\n", elements->west_path);

}
