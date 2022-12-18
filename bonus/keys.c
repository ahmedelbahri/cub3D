/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:54:42 by akadi             #+#    #+#             */
/*   Updated: 2022/12/17 20:14:30 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	more_keys(t_data *data)
{
	if (data->events.larr_pressed == 1)
	{
		if (data->player.angle <= SPEED)
			data->player.angle = 6.29 - data->player.angle - SPEED;
		else
			data->player.angle -= SPEED;
	}
	if (data->events.rarr_pressed == 1)
		data->player.angle += SPEED;
	if (data->player.angle >= 6.29 || data->player.angle <= -6.29)
		data->player.angle = 0;
	return ;
}

void	collision_s_d(t_data *data, double *x, double *y)
{
	if (data->events.s_pressed == 1)
	{
		(*x) += (cos(data->player.angle) * (-(SPEED * 2)));
		(*y) += (sin(data->player.angle) * (-(SPEED * 2)));
	}
	if (data->events.d_pressed == 1)
	{
		(*x) += (sin(data->player.angle) * (-(SPEED * 2)));
		(*y) += (cos(data->player.angle) * (SPEED * 2));
	}
}

int	check_player_collision(t_data *data)
{
	double	x;
	double	y;

	x = data->player.x;
	y = data->player.y;
	if (data->events.w_pressed == 1)
	{
		x += (cos(data->player.angle) * (SPEED * 2));
		y += (sin(data->player.angle) * (SPEED * 2));
	}
	if (data->events.a_pressed == 1)
	{
		x += (sin(data->player.angle) * (SPEED * 2));
		y += (cos(data->player.angle) * (-(SPEED * 2)));
	}
	collision_s_d(data, &x, &y);
	if (data->map[(int)round(y)][(int)round(x)] == '0'
		|| data->map[(int)round(y)][(int)round(x)] == '3')
		return (1);
	return (0);
}

int	keys(t_data *data)
{
	if (check_player_collision(data))
	{
		if (data->events.w_pressed == 1)
		{
			data->player.x += (cos(data->player.angle) * SPEED);
			data->player.y += (sin(data->player.angle) * SPEED);
		}
		if (data->events.a_pressed == 1)
		{
			data->player.x += (sin(data->player.angle) * SPEED);
			data->player.y += (cos(data->player.angle) * (-SPEED));
		}
		if (data->events.s_pressed == 1)
		{
			data->player.x += (cos(data->player.angle) * (-SPEED));
			data->player.y += (sin(data->player.angle) * (-SPEED));
		}
		if (data->events.d_pressed == 1)
		{
			data->player.x += (sin(data->player.angle) * (-SPEED));
			data->player.y += (cos(data->player.angle) * SPEED);
		}
	}
	more_keys(data);
	return (mlx_destroy_image(data->mlx.ptr, data->mlx.img), draw_2d(data), 0);
}
