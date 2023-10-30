/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smunio <smunio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:27:13 by sammeuss          #+#    #+#             */
/*   Updated: 2023/10/30 15:27:31 by smunio           ###   ########.fr       */
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
	else if (c == 'F')
		cub->elements->floor_color = (cub->elements->r << 24
				| cub->elements->g << 16
				| cub->elements->b << 8 | 255);
	else if (c == 'C')
		cub->elements->ceiling_color = (cub->elements->r << 24
				| cub->elements->g << 16
				| cub->elements->b << 8 | 255);
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
				cub->parsing_error = 1;
				error_msg("Wrong char in color", cub);
				break ;
			}
		}
		u = -1;
	}
}
