/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:27:13 by sammeuss          #+#    #+#             */
/*   Updated: 2023/10/27 16:13:45 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	color_bitshift(t_cub *cub, char c)
{
	if (!color_check(cub))
	{
		error_msg("RGB Colors should be between 0 and 255", cub);
		cub->parsing_error = 1;
	}
	if (c == 'F')
		cub->elements->floor_color = cub->elements->r << 24
			| cub->elements->g << 16
			| cub->elements->b << 8 | 255;
	else
		cub->elements->ceiling_color = cub->elements->r << 24
			| cub->elements->g << 16
			| cub->elements->b << 8 | 255;
}

void	get_r(t_cub *cub, char *line)
{
	printf("r = %s\n", ft_substr(line, cub->v->start, cub->v->len));
	cub->elements->r = ft_atoi(ft_substr(line,
				cub->v->start, cub->v->len));
	cub->v->len = 0;
}

void	get_g(t_cub *cub, char *line)
{
	printf("g = %s\n", ft_substr(line, cub->v->start, cub->v->len));
	cub->elements->g = ft_atoi(ft_substr(line,
				cub->v->start, cub->v->len));
	cub->v->len = 0;
}

void	get_b(t_cub *cub, char *line)
{
	printf("b = %s\n", ft_substr(line, cub->v->start, cub->v->len));
	cub->elements->b = ft_atoi(ft_substr(line,
				cub->v->start, cub->v->len));
	cub->v->len = 0;
}
