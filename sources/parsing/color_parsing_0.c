/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:32:16 by sammeuss          #+#    #+#             */
/*   Updated: 2023/10/30 15:30:28 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	convert_rgb(char *line, t_cub *cub, char c)
{	
	char	**tab;
	int		i;

	i = 0;
	while (!is_digit(*line))
		line++;
	tab = ft_split(line, ',');
	check_color_tab(tab, cub);
	if (cub->parsing_error != 1)
	{
		cub->elements->r = ft_atoi(tab[0]);
		cub->elements->g = ft_atoi(tab[1]);
		cub->elements->b = ft_atoi(tab[2]);
	}
	color_bitshift(cub, c);
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
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
	if (line[i] == 'C')
		convert_rgb(line, cub, 'C');
	else if (line[i] == 'F')
		convert_rgb(line, cub, 'F');
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
