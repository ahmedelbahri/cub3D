/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:57:07 by akadi             #+#    #+#             */
/*   Updated: 2022/10/13 15:03:38 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_data(t_data *data)
{
	data->NO = NULL;
	data->SO = NULL;
	data->EA = NULL;
	data->WE = NULL;
	data->Floor[0] = -1;
	data->Floor[1] = -1;
	data->Floor[2] = -1;
	data->sky[0] = -1;
	data->sky[1] = -1;
	data->sky[2] = -1;
}