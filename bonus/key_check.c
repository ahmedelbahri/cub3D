/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:24:57 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/12/16 20:08:04 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

int	register_keys(int key, t_data *data)
{
	if (key == 13)
		data->events.w_pressed = 1;
	if (key == 0)
		data->events.a_pressed = 1;
	if (key == 1)
		data->events.s_pressed = 1;
	if (key == 2)
		data->events.d_pressed = 1;
	if (key == 124)
		data->events.rarr_pressed = 1;
	if (key == 123)
		data->events.larr_pressed = 1;
	return (1);
}

int	key_rel(int key, t_data *data)
{
	if (key == 13)
		data->events.w_pressed = 0;
	else if (key == 0)
		data->events.a_pressed = 0;
	else if (key == 1)
		data->events.s_pressed = 0;
	else if (key == 2)
		data->events.d_pressed = 0;
	else if (key == 124)
		data->events.rarr_pressed = 0;
	else if (key == 123)
		data->events.larr_pressed = 0;
	else if (key == 53)
		exit(0);
	return (0);
}
