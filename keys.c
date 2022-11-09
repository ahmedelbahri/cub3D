/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:54:42 by akadi             #+#    #+#             */
/*   Updated: 2022/11/09 19:41:32 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	more_keys(int key)
{
	if (key == 53)
		exit(0);
	return ;
}

int	keys(int key,t_data *data)
{
	if (key == 1) // keyword 'S'
	{
		//if (data->map[data->X_player + 1][data->Y_player] != '1')
			data->pixel_y += 0.1;
	}
	if (key == 13) // keyword 'W'
	{
		//if (data->map[data->X_player - 1][data->Y_player] != '1')
			data->pixel_y -= 0.1;
	}
	if (key == 2) // keyword 'D'
	{
		//if (data->map[data->X_player][data->Y_player + 1] != '1')
			data->pixel_x += 0.1;
	}
	if (key == 0) //keyword 'A'
	{
		//if (data->map[data->X_player][data->Y_player - 1] != '1')
			data->pixel_x -= 0.1;
	}
	more_keys(key);
	mlx_destroy_image(data->mlx, data->img);
	draw_2d(data);
	return (0);
}