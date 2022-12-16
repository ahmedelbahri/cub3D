/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 21:16:22 by akadi             #+#    #+#             */
/*   Updated: 2022/12/16 21:20:37 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

double	normalize_angle(double angle)
{
	angle = fmod(angle, (2 * M_PI));
	if (angle < 0)
		angle = angle + (2 * M_PI);
	return (angle);
}

void	loop_check_wall_h(t_data *data, int check)
{
	while (checkiswall(data, data->first, check, 1))
	{
		data->first.x += data->steps.x;
		data->first.y += data->steps.y;
	}
}

void	loop_check_wall_v(t_data *data, int check)
{
	while (checkiswall(data, data->first, check, 0))
	{
		data->first.x += data->steps.x;
		data->first.y += data->steps.y;
	}
}
