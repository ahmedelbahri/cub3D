/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:54:42 by akadi             #+#    #+#             */
/*   Updated: 2022/11/08 15:54:21 by akadi            ###   ########.fr       */
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
	if (key == 1)
	{
		if (data->map[data->X_player + 1][data->Y_player] != '1')
			data->X_player += 1;
	}
	if (key == 13)
	{
		if (data->map[data->X_player - 1][data->Y_player] != '1')
			data->X_player -= 1;
	}
	if (key == 2)
	{
		if (data->map[data->X_player][data->Y_player + 1] != '1')
			data->Y_player += 1;
	}
	if (key == 0)
	{
		if (data->map[data->X_player][data->Y_player - 1] != '1')
			data->Y_player -= 1;
	}
	more_keys(key);
	mlx_destroy_image(data->mlx, data->img);
	draw_2d(data);
	return (0);
}