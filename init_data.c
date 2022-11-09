/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:57:07 by akadi             #+#    #+#             */
/*   Updated: 2022/11/09 19:42:19 by akadi            ###   ########.fr       */
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
	data->pixel_x = 0;
	data->pixel_y = 0;
}