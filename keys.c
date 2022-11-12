/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:54:42 by akadi             #+#    #+#             */
/*   Updated: 2022/11/12 14:39:53 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	more_keys(int key, t_data *data)
{
	if (key == 123)
		data->angle -= 0.1;
	if (key == 124)
		data->angle += 0.1;
	if (key == 53)
		exit(0);
	return ;
}

int	keys(int key,t_data *data)
{
	if (key == 1
		&& (data->map[(int)round(data->Y_player + data->pixel_y + 0.2)]
			[(int)round(data->X_player + data->pixel_x - 0.1)] != '1'
			&& data->map[(int)round(data->Y_player + data->pixel_y + 0.2)]
			[(int)round(data->X_player + data->pixel_x + 0.1)] != '1')) // keyword 'S'
	{
		//if (data->map[data->X_player + 1][data->Y_player] != '1')
			data->pixel_y += 0.1;
	}
	if (key == 13
		&& data->map[(int)round(data->Y_player + data->pixel_y - 0.2)]
		[(int)round(data->X_player + data->pixel_x - 0.1)] != '1'
			&& data->map[(int)round(data->Y_player + data->pixel_y - 0.2)]
			[(int)round(data->X_player + data->pixel_x + 0.1)] != '1') // keyword 'W'
	{
		//if (data->map[data->X_player - 1][data->Y_player] != '1')
			data->pixel_y -= 0.1;
	}
	if (key == 2 && data->map[(int)round(data->Y_player + data->pixel_y)][(int)round(data->X_player + data->pixel_x + 0.2)] != '1') // keyword 'D'
	{
		//if (data->map[data->X_player][data->Y_player + 1] != '1')
			data->pixel_x += 0.1;
	}
	if (key == 0 && data->map[(int)round(data->Y_player + data->pixel_y)][(int)round(data->X_player + data->pixel_x - 0.2)] != '1') //keyword 'A'
	{
		//if (data->map[data->X_player][data->Y_player - 1] != '1')
			data->pixel_x -= 0.1;
	}
	more_keys(key, data);
	mlx_destroy_image(data->mlx, data->img);
	draw_2d(data);
	return (0);
}