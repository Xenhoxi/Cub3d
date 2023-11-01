/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:27:13 by sammeuss          #+#    #+#             */
/*   Updated: 2023/11/01 10:26:40 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	color_bitshift(t_cub *cub, char c)
{
	if (!color_check(cub))
		return (error_msg("RGB Colors should be between 0 and 255", cub));
	else if (c == 'F')
	{
		if (cub->elements->floor_color != 256)
			return (error_msg("Floor color already filled", cub));
		cub->elements->floor_color = (cub->elements->r << 24
				| cub->elements->g << 16
				| cub->elements->b << 8 | 255);
		cub->v->nb_c++;
	}
	else if (c == 'C')
	{
		if (cub->elements->ceiling_color != 256)
			return (error_msg("Ceiling color already filled", cub));
		cub->elements->ceiling_color = (cub->elements->r << 24
				| cub->elements->g << 16
				| cub->elements->b << 8 | 255);
		cub->v->nb_c++;
	}
}

void	check_color_tab(char **tab, t_cub *cub)
{
	int	i;
	int	u;

	u = -1;
	i = -1;
	while (tab[++i])
	{
		while (tab[i][++u])
		{
			if (is_alpha(tab[i][u]) || is_space(tab[i][u]))
			{
				error_msg("Wrong char in color", cub);
				break ;
			}
		}
		u = -1;
	}
	if (i < 3)
		error_msg("Missing digit(s) in color", cub);
}
