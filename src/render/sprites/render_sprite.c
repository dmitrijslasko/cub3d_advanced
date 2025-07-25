/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvargas <fvargas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 00:08:41 by fvargas           #+#    #+#             */
/*   Updated: 2025/07/02 00:08:42 by fvargas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_sprite(t_data *dt, t_sprite *sprite, \
					t_coor *offset, t_coor	*sprite_size)
{
	t_coor	coor;
	t_coor	tex_coor;

	if (sprite->active == 0)
		return (0);
	sprite->time = (dt->time.last_time - dt->time.start_time) / 100 % 2;
	coor.y = ft_max(offset->y, 0);
	while (coor.y < sprite_size->y + offset->y && coor.y < WINDOW_H)
	{
		coor.x = ft_max(offset->x, 0);
		while (coor.x < sprite_size->x + offset->x && coor.x < WINDOW_W)
		{
			if (check_if_sprite_is_closer_than_wall(dt, &coor, sprite))
			{
				tex_coor = calculate_tex_x_y(sprite->texture,
						&coor, offset, sprite_size);
				sprite_put_color(dt, sprite, &coor, &tex_coor);
			}
			coor.x++;
		}
		coor.y++;
	}
	return (EXIT_SUCCESS);
}
