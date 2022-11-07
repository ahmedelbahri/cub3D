/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:00:06 by akadi             #+#    #+#             */
/*   Updated: 2022/11/07 14:16:07 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	fill_map_with_z(t_data *data)
{
	int	s;
	int	k;

	k = 0;
	s = 0;
	while (data->map[k])
	{
		s = 0;
		while (data->map[k][s])
		{
			fill_direction(data, k, s);
			s++;
		}
		k++;
	}
}

void	fill_color(char line, char *sub, t_data *data, int k)
{
	if (line == 'C')
	{
		data->sky[k] = ft_atoi(sub);
		free(sub);
	}
	if (line == 'F')
	{
		data->Floor[k] = ft_atoi(sub);
		free(sub);
	}
}

void	fill_direction(t_data *data, int k, int s)
{
	if (data->map[k][s] == ' ' || data->map[k][s] == '\t')
		data->map[k][s] = '*';
	else if (data->map[k][s] == 'E' || data->map[k][s] == 'S' 
	|| data->map[k][s] == 'W' || data->map[k][s] == 'N')
	{
		if (data->Direction)
		{
			printf("Direction full\n");
			exit(1);
		}
		data->Direction = data->map[k][s];
		data->X_player = k;
		data->Y_player = s;
		data->map[k][s] = '0';
	}
	else if (data->map[k][s] != '0' && data->map[k][s] != '1' 
	&& data->map[k][s] != '*')
	{
		printf("invalid map\n");
		exit(1);
	}
}

void	condition_texture(t_data *data, char direction, char *line)
{
	if (data->SO == NULL && direction == 'S')
		data->SO = ft_strdup(line);
	else if (data->NO == NULL && direction == 'N')
		data->NO = ft_strdup(line);
	else if (data->EA == NULL && direction == 'E')
		data->EA = ft_strdup(line);
	else if (data->WE == NULL && direction == 'W')
		data->WE = ft_strdup(line);
	else
	{
		printf("Duplicate\n");
		exit(1);
	}
}