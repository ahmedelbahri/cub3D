/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:27:18 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/12/16 22:07:02 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

double	distance(double x, double y, double x1, double y1)
{
	return (sqrt(pow(x1 - x, 2) + pow(y1 - y, 2)));
}

double	horizontal_inter(t_data *data, t_index player, double angle)
{
	int		check;

	check = 0;
	angle = normalize_angle(angle);
	data->first.y = floor(player.y / SQ) * SQ;
	if ((angle > 0 && angle < M_PI))
		data->first.y += SQ;
	data->first.x = player.x + (data->first.y - player.y) / tan(angle);
	data->steps.y = SQ;
	if (!(angle > 0 && angle < M_PI))
	{
		data->steps.y *= -1;
		check = -1;
	}
	data->steps.x = data->steps.y / tan(angle);
	if ((angle < 0.5 * M_PI || angle > 1.5 * M_PI) && data->steps.x < 0)
		data->steps.x *= -1;
	if (!(angle < 0.5 * M_PI || angle > 1.5 * M_PI) && data->steps.x > 0)
		data->steps.x *= -1;
	loop_check_wall_h(data, check);
	data->inter.ray_hor_inter_x = data->first.x;
	data->inter.ray_hor_inter_y = data->first.y;
	return (distance(player.x, player.y, data->first.x, data->first.y));
}

double	vertical_inter(t_data *data, t_index player, double angle)
{
	int		check;

	check = 0;
	angle = normalize_angle(angle);
	data->first.x = floor(player.x / SQ) * SQ;
	if ((angle < 0.5 * M_PI || angle > 1.5 * M_PI))
		data->first.x += SQ;
	data->first.y = player.y + (data->first.x - player.x) * tan(angle);
	data->steps.x = SQ;
	if (!(angle < 0.5 * M_PI || angle > 1.5 * M_PI))
	{
		data->steps.x *= -1;
		check = -1;
	}
	data->steps.y = data->steps.x * tan(angle);
	if (!(angle > 0 && angle < M_PI) && data->steps.y > 0)
		data->steps.y *= -1;
	if ((angle > 0 && angle < M_PI) && data->steps.y < 0)
		data->steps.y *= -1;
	loop_check_wall_v(data, check);
	data->inter.ray_ver_inter_x = data->first.x;
	data->inter.ray_ver_inter_y = data->first.y;
	return (distance(player.x, player.y, data->first.x, data->first.y));
}
