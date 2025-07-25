/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_door_at.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 00:06:38 by fvargas           #+#    #+#             */
/*   Updated: 2025/07/15 16:33:38 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_door	*find_door_at(t_data *dt, int x, int y)
{
	size_t	i;

	i = 0;
	while (i < dt->door_count)
	{
		if (dt->doors[i].cell_x == x && dt->doors[i].cell_y == y)
			return (&dt->doors[i]);
		i++;
	}
	return (NULL);
}
