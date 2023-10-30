/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:41:33 by sammeuss          #+#    #+#             */
/*   Updated: 2023/10/30 18:02:42 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_alpha(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == '\t' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_array_len(char	**array)
{
	int		i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

void	convert_texture_to_image(t_cub *cub)
{
	cub->elements->south_image = mlx_texture_to_image(cub->mlx,
			cub->elements->south_texture);
	cub->elements->north_image = mlx_texture_to_image(cub->mlx,
			cub->elements->north_texture);
	cub->elements->west_image = mlx_texture_to_image(cub->mlx,
			cub->elements->west_texture);
	cub->elements->east_image = mlx_texture_to_image(cub->mlx,
			cub->elements->east_texture);
}
