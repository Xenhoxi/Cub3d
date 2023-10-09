/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:32:16 by sammeuss          #+#    #+#             */
/*   Updated: 2023/10/07 15:21:11 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	convert_rgb(char *line)
{
	int				r;
	int				g;
	int				b;
	unsigned int	start;

	start = 0;
	while (!is_digit(line[start]))
		start++;
	r = ft_atoi(ft_substr(line, start, 3));
	if (r > 255 || r < 0)
		return (printf("Error\nColor should be between 0 and 255\n"), 0);
	start += 3;
	while (!is_digit(line[start]))
		start++;
	g = ft_atoi(ft_substr(line, start, 3));
	if (g > 255 || g < 0)
		return (printf("Error\nColor should be between 0 and 255\n"), 0);
	start += 3;
	while (!is_digit(line[start]))
		start++;
	b = ft_atoi(ft_substr(line, start, 3));
	if (b > 255 || b < 0)
		return (printf("Error\nColor should be between 0 and 255\n"), 0);
	return ((r << 16) | (g << 8) | b);
}

int	is_color(char *line, int i)
{
	int	nb_count;
	int	comma_count;

	comma_count = 0;
	nb_count = 0;
	while (!is_digit(line[i]))
		i++;
	while (line[i])
	{
		if (is_digit(line[i]))
			nb_count++;
		else if (line[i] == ',')
			comma_count++;
		else if (line[i] != '\n' && !is_space(line[i]) && nb_count < 9)
			return (printf("Error\nWrong color syntax\n"), 0);
		else if ((line[i] == '\n' || is_space(line[i])) && nb_count < 9)
			return (printf("Error\nWrong color syntax\n"), 0);
		i++;
	}	
	if (color_check(nb_count, comma_count))
		return (1);
	return (0);
}

int	color_check(int nb_count, int comma_count)
{
	if (nb_count == 9 && comma_count == 2)
		return (1);
	else
		printf("Error\nColors should be declared like : I 255, 255, 255\n");
	return (0);
}

void	store_color(t_elements *elements, char *line)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (line[i] == 'F')
		elements->floor_color = convert_rgb(line);
	else if (line[i] == 'C')
		elements->ceiling_color = convert_rgb(line);
	else
		printf("Error\nWrong color syntax\n");
}
