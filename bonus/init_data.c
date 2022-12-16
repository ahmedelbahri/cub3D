/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:57:07 by akadi             #+#    #+#             */
/*   Updated: 2022/12/16 20:08:04 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	init_data(t_data *data)
{
	data->map = NULL;
	data->coord.no = NULL;
	data->coord.so = NULL;
	data->coord.ea = NULL;
	data->coord.we = NULL;
	data->events.w_pressed = 0;
	data->events.a_pressed = 0;
	data->events.s_pressed = 0;
	data->events.d_pressed = 0;
	data->events.larr_pressed = 0;
	data->events.rarr_pressed = 0;
	data->player.direction = 0;
	data->player.x = -1;
	data->player.y = -1;
	data->texture.sky[0] = -1;
	data->texture.sky[1] = -1;
	data->texture.sky[2] = -1;
	data->texture.floor[0] = -1;
	data->texture.floor[1] = -1;
	data->texture.floor[2] = -1;
	data->pars.max_line = 0;
	data->pars.empty_lines = 0;
	data->mlx.ptr = mlx_init();
}
