/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_keypresses.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlasko <dmlasko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 00:04:00 by fvargas           #+#    #+#             */
/*   Updated: 2025/07/23 17:16:18 by dmlasko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	process_vertical_look(t_data *dt)
{
	if (!ENABLE_VERTICAL_LOOK)
		return ;
	if (dt->keys[XK_Up])
	{
		dt->has_changed = 1;
		dt->view->screen_center_y = ft_min(
				dt->view->screen_center_y + KEYBOARD_VERTICAL_LOOK_STEP,
				WINDOW_H / 2 + VERTICAL_LOOK_LOCK_UP);
	}
	if (dt->keys[XK_Down])
	{
		// dt->has_changed = 1;
		dt->view->screen_center_y = ft_max(
				dt->view->screen_center_y - KEYBOARD_VERTICAL_LOOK_STEP,
				WINDOW_H / 2 - VERTICAL_LOOK_LOCK_DOWN);
	}
}

void	open_close_door(t_data *dt, int dir)
{
	t_coor	cell_ahead;
	t_door	*door;

	// dt->has_changed = 1;
	cell_ahead = get_cell_ahead(dt);
	if (ft_strchr(DOOR_TYPES, get_cell_type(&dt->map, &cell_ahead)))
	{
		// dt->view->show_door_open_message = 1;
		door = find_door_at(dt, cell_ahead.x, cell_ahead.y);
		if (dir == 1)
			door->open_progress = fmax(0.0f, door->open_progress - door->speed);
		else
			door->open_progress = fmin(1.0f, door->open_progress + door->speed);
	}
}

static void	process_door(t_data *dt)
{
	if (dt->keys[XK_bracketleft])
		open_close_door(dt, -1);
	if (dt->keys[XK_bracketright])
		open_close_door(dt, 1);
}

void	process_keypresses(t_data *dt)
{
	int is_moving_now = 0;

	if (dt->keys[XK_w])
	{
		move_forward_backward(dt, 1);
		is_moving_now = 1;
	}
	else if (dt->keys[XK_s])
	{
		move_forward_backward(dt, -1);
		is_moving_now = 1;
	}

	if (dt->keys[XK_a])
	{
		move_sideways(dt, -1);
		is_moving_now = 1;
	}
	else if (dt->keys[XK_d])
	{
		move_sideways(dt, 1);
		is_moving_now = 1;
	}

	if (dt->keys[XK_f])
	{
		dt->test_value_1 -= 10.0f;
		printf("%f\n", dt->test_value_1);
	}
	if (dt->keys[XK_g])
	{
		dt->test_value_1 += 10.0f;
		printf("%f\n", dt->test_value_1);
	}
	if (dt->keys[XK_v])
		dt->sprites[74].active = 0;
	if (dt->keys[XK_b])
		dt->sprites[74].active = 1;
	if (dt->keys[XK_h])
		dt->test_value_3 -= 10.0f;
	if (dt->keys[XK_j])
		dt->test_value_3 += 10.0f;
	if (dt->keys[XK_n])
		dt->test_value_4 -= 0.001f;
	if (dt->keys[XK_m])
		dt->test_value_4 += 0.001f;
	if (dt->keys[XK_9])
	{
		//dt->ambient_light -= 10.0f;
		dt->ambient_light = fmax(0.0f, dt->ambient_light / 1.1f);
		printf("Ambient light: %.2f\n", dt->ambient_light);
	}
	if (dt->keys[XK_0])
	{
		dt->ambient_light = fmin(1000.0f, dt->ambient_light * 1.1f);
		printf("Ambient light: %.2f\n", dt->ambient_light);
	}


	dt->player.is_moving = is_moving_now;

	if (dt->keys[XK_Left])
		rotate_player(dt, KEYBOARD_PLAYER_ROTATION_STEP, 1);
	if (dt->keys[XK_Right])
		rotate_player(dt, KEYBOARD_PLAYER_ROTATION_STEP, -1);
	if (dt->keys[XK_Shift_L])
		dt->player.move_speed_multiplier = MOVE_SPEED_MULTIPLIER_SLOW;
	// if (dt->keys[XK_Control_L])
	// {
	// 	dt->player.move_speed_multiplier = 0.4f;
	// 	dt->view->crouch = 1.5f;
	// }
	else
	{
		dt->player.move_speed_multiplier = 1;
		dt->view->crouch = 1.0f;
	}

	process_door(dt);
	process_vertical_look(dt);
}
