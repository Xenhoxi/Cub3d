/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerinec <ljerinec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:11:42 by ljerinec          #+#    #+#             */
/*   Updated: 2023/10/19 12:11:45 by ljerinec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void	*b, int c, size_t len)
{
	size_t	i;
	char	*buffer_pointeur;

	buffer_pointeur = (char *)b;
	i = 0;
	while (i < len)
	{
		buffer_pointeur[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
