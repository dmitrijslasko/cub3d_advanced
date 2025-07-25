/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pos_render_sprites.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 00:08:36 by fvargas           #+#    #+#             */
/*   Updated: 2025/07/12 20:20:38 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_position_and_render_sprite(t_data *dt, t_sprite *sprite)
{
	t_x_y	dist_to_player;
	t_x_y	transform;
	int		sprite_screen_x;
	t_coor	sprite_size;
	t_coor	offset;

	dist_to_player.x = sprite->pos.x - dt->player.pos.x;
	dist_to_player.y = sprite->pos.y - dt->player.pos.y;
	transform.y = (dt->player.direction_vector.x * dist_to_player.x + \
					dt->player.direction_vector.y * dist_to_player.y);

	if (transform.y <= 0.4f)
		return (EXIT_SUCCESS);

	transform.x = (-1.0f / FIELD_OF_VIEW_SCALE) * \
					(dt->player.direction_vector.y * dist_to_player.x - \
								dt->player.direction_vector.x * dist_to_player.y);
	sprite_size.y = fmin(WINDOW_H * 4, WINDOW_H / transform.y);
	sprite_size.x = fmin(WINDOW_W * 4, sprite_size.y);
	sprite_screen_x = (WINDOW_W / 2) * (1 + transform.x / transform.y);
	offset.x = sprite_screen_x - sprite_size.x / 2;
	offset.y = dt->view->screen_center_y - sprite_size.y / 3;
	render_sprite(dt, sprite, &offset, &sprite_size);
	return (EXIT_SUCCESS);
}
