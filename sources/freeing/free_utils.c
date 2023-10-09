/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:59:36 by sammeuss          #+#    #+#             */
/*   Updated: 2023/10/03 23:00:18 by sammeuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_int_array(int	**array, char **map)
{
	int	i;

	i = -1;
	while (++i < ft_array_len_int(array, map))
		free(array[i]);
	free(array);
}
