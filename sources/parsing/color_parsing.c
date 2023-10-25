/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smunio <smunio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:32:16 by sammeuss          #+#    #+#             */
/*   Updated: 2023/10/25 16:31:54 by smunio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

u_int32_t	convert_rgb(char *line, t_poop *poop)
{
	int		*rgb;
	int		i;

	i = 0;
	rgb = malloc(sizeof(char *) * 3);
	while (!is_digit(line[i]))
		i++;
	poop->start = i;
	while (line[i])
	{
		if (line[i] == ',' || line[i] == '\n')
		{
			rgb[poop->index++] = ft_atoi(ft_substr(line,
						poop->start, poop->len));
			poop->len = 0;
			i++;
			poop->start = i;
		}
		else
		{
			poop->len++;
			i++;
		}
	}
	return (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255);
}

int	is_color(char *line, int i, t_poop *poop, t_cub *cub)
{
	int	nb;

	nb = 0;
	while (!is_digit(line[i]))
		i++;
	while (line[i])
	{
		if (!is_digit(line[i]) && line[i] != ',' && !is_space(line[i]) 
			&& line[i] != '\n')
			return (error_msg("Wrong char in color", cub), 0);
		if (line[i] == ',')
		{
			while (is_space(line[++i]))
				;
			if (!is_digit(line[i]))
				return (error_msg("Wrong char in color", cub), 0);
			poop->comma++;
		}
		else
			nb++;
		i++;
	}
	if (poop->comma != 2 && nb < 3)
		return (error_msg("Wrong color syntax", cub), 0);
	return (1);
}

void	store_color(t_elements *elements, char *line, t_poop *poop, t_cub *cub)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (line[i] == 'F')
		elements->floor_color = convert_rgb(line, poop);
	else if (line[i] == 'C')
		elements->ceiling_color = convert_rgb(line, poop);
	else
		error_msg("Wrong color identifier", cub);
}

u_int32_t	get_rgba_tex(u_int32_t color)
{
	u_int8_t	r;
	u_int8_t	g;
	u_int8_t	b;
	u_int8_t	a;

	a = color >> 24;
	r = color >> 16;
	g = color >> 8;
	b = color;
	return (r << 8 | g << 16 | b << 24 | a << 0);
}
