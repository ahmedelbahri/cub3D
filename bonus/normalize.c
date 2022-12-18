/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 21:16:22 by akadi             #+#    #+#             */
/*   Updated: 2022/12/17 22:24:51 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	checkisdoor(t_data *data, t_int_idx *index, int face)
{
	if (face == 1)
	{
		data->inter.map_x_h = index->x;
		data->inter.map_y_h = index->y;
	}
	else
	{
		data->inter.map_x_v = index->x;
		data->inter.map_y_v = index->y;
	}
}

int	checkiswall(t_data *data, t_index inter, int check, int face)
{
	t_int_idx	index;

	if (face == 1)
		inter.y += check;
	else
		inter.x += check;
	if (inter.y > data->pars.num_lines * SQ)
		return (0);
	if (inter.x > data->pars.max_line * SQ)
		return (0);
	index.x = floor(inter.x / SQ);
	index.y = floor(inter.y / SQ);
	if (index.y < 0 || index.y >= data->pars.num_lines)
		return (0);
	if (index.x < 0 || index.x >= data->pars.max_line)
		return (0);
	checkisdoor(data, &index, face);
	if (data->map[index.y][index.x] == '1'
		|| data->map[index.y][index.x] == '2')
		return (0);
	return (1);
}

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
