/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smunio <smunio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:32:16 by sammeuss          #+#    #+#             */
/*   Updated: 2023/10/30 12:12:02 by smunio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	convert_rgb(char *line, t_cub *cub, char c, int i)
{
	while (line[i] && !is_digit(line[i]))
		i++;
	cub->v->start = i;
	while (line[i] && cub->v->index < 3)
	{
		if (line[i] == ',' || line[i] == '\n')
		{
			if (cub->v->index == 0)
				get_r(cub, line);
			else if (cub->v->index == 1)
				get_g(cub, line);
			else if (cub->v->index == 2)
				get_b(cub, line);
			i++;
			cub->v->start = i;
		}
		else
		{
			cub->v->len++;
			i++;
		}
	}
	color_bitshift(cub, c);
}

int	is_color(char *line, int i, t_cub *c)
{
	int	nb;

	nb = 0;
	while (line[i] && !is_digit(line[i]))
		i++;
	while (line[i])
	{
		if (!is_digit(line[i]) && line[i] != ',' && !is_space(line[i])
			&& line[i] != '\n')
			return (error_msg("Color syntax", c), c->parsing_error = 1, 0);
		if (line[i] == ',')
		{
			while (is_space(line[++i]))
				;
			if (!is_digit(line[i]))
				return (error_msg("Color syntax", c), c->parsing_error = 1, 0);
			c->v->comma++;
		}
		else if (!is_space(line[i]) && line[i] != '\n')
			nb++;
		i++;
	}
	if (c->v->comma != 2 && nb < 3)
		return (error_msg("Wrong color syntax", c), 0);
	return (1);
}

void	store_color(char *line, t_cub *cub)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (line[i] != 'F' && line[i] != 'C')
		error_msg("Wrong color identifier", cub);
	cub->v->index = 0;
	if (line[i] == 'C')
		convert_rgb(line, cub, 'C', 0);
	else if (line[i] == 'F')
		convert_rgb(line, cub, 'F', 0);
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

int	color_check(t_cub *cub)
{
	if (cub->elements->r <= 255 && cub->elements->r >= 0)
		if (cub->elements->g <= 255 && cub->elements->g >= 0)
			if (cub->elements->b <= 255 && cub->elements->b >= 0)
				return (1);
	return (0);
}
