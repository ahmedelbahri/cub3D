/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:54:42 by akadi             #+#    #+#             */
/*   Updated: 2022/11/21 14:04:49 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	more_keys(int key, t_data *data)
{
	if (data->larr_pressed == 1)
	{
		data->angle -= 0.1;
		data->angle = fmod(data->angle, (2 * M_PI));
		if (data->angle < 0)
		data->angle = data->angle + (2 * M_PI);
	}
	if (data->rarr_pressed == 1)
	{
		data->angle += 0.1;
		data->angle = fmod(data->angle, (2 * M_PI));
		if (data->angle < 0)
		data->angle = data->angle + (2 * M_PI);
	}
	if (key == 53)
		exit(0);
	if (data->angle >= 6.29 || data->angle <= -6.29)
		data->angle = 0;
	return ;
}

int	check_player_collision(t_data *data)
{
	float	x;
	float	y;

	x = data->X_player;
	y = data->Y_player;
	if (data->w_pressed == 1)
	{
		x += (cos(data->angle) * 0.2);
		y += (sin(data->angle) * 0.2);
	}
	if (data->a_pressed == 1)
	{
		x += (sin(data->angle) * 0.2);
		y += (cos(data->angle) * (-0.2));
	}
	if (data->s_pressed == 1)
	{
		x += (cos(data->angle) * (-0.2));
		y += (sin(data->angle) * (-0.2));
	}
	if (data->d_pressed == 1)
	{
		x += (sin(data->angle) * (-0.2));
		y += (cos(data->angle) * 0.2);
	}
	if (data->map[(int)round(y)][(int)round(x)] == '0')
		return (1);
	return (0);
}

int	register_keys(int key, t_data *data)
{
	if (key == 13)
		data->w_pressed = 1;
	if (key == 0)
		data->a_pressed = 1;
	if (key == 1)
		data->s_pressed = 1;
	if (key == 2)
		data->d_pressed = 1;
	if (key == 124)
		data->rarr_pressed = 1;
	if (key == 123)
		data->larr_pressed = 1;
	printf("w %d s %d rarr %d larr %d\n", data->w_pressed, data->s_pressed, data->rarr_pressed, data->larr_pressed);
	return (1);
}

int	keys(int key, t_data *data)
{
	register_keys(key, data);
	if (check_player_collision(data))
	{
		if (data->w_pressed == 1)
		{
			data->X_player += (cos(data->angle) * 0.1);
			data->Y_player += (sin(data->angle) * 0.1);
		}
		if (data->a_pressed == 1)
		{
			data->X_player += (sin(data->angle) * 0.1);
			data->Y_player += (cos(data->angle) * (-0.1));
		}
		if (data->s_pressed == 1)
		{
			data->X_player += (cos(data->angle) * (-0.1));
			data->Y_player += (sin(data->angle) * (-0.1));
		}
		if (data->d_pressed == 1)
		{
			data->X_player += (sin(data->angle) * (-0.1));
			data->Y_player += (cos(data->angle) * 0.1);
		}
	}
	more_keys(key, data);
	return (mlx_destroy_image(data->mlx, data->img), draw_2d(data), 0);
}
