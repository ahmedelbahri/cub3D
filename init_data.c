/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:57:07 by akadi             #+#    #+#             */
/*   Updated: 2022/11/16 13:57:23 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_data(t_data *data)
{
	data->NO = NULL;
	data->SO = NULL;
	data->EA = NULL;
	data->WE = NULL;
	data->map = NULL;
	data->Direction = 0;
	data->MAX_LINE = 0;
	data->Floor[0] = -1;
	data->Floor[1] = -1;
	data->Floor[2] = -1;
	data->sky[0] = -1;
	data->sky[1] = -1;
	data->sky[2] = -1;
	data->X_player = -1;
	data->Y_player = -1;
	data->empty_lines = 0;
	data->w_pressed = 0;
	data->a_pressed = 0;
	data->s_pressed = 0;
	data->d_pressed = 0;
	data->larr_pressed = 0;
	data->rarr_pressed = 0;
}