/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:09:07 by akadi             #+#    #+#             */
/*   Updated: 2022/12/17 19:36:00 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

int	is_space(char line)
{
	if ((line >= 9 && line <= 13) || line == ' ')
		return (1);
	return (0);
}

int	color_is_valid(char *color)
{
	int	i;
	int	num;

	i = 0;
	while (color[i])
	{
		if (is_space(color[i]))
		{
			i++;
			continue ;
		}
		if (!ft_isdigit(color[i]))
			return (0);
		i++;
	}
	num = ft_atoi(color);
	if (num > 255)
		return (0);
	free(color);
	return (1);
}

int	num_of_comma(char *line)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (line[++i])
		if (line[i] == ',')
			j++;
	return (j);
}

void	free_dub(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

int	mouse(int x, int y, t_data *data)
{
	static int	old;

	data->color = 0;
	if (x < 0 || x > W || y < 0 || y > H)
		return (0);
	if (x < old)
	{
		data->events.larr_pressed = 1;
		more_keys(data);
		data->events.larr_pressed = 0;
		old = x;
	}
	else if (x > old)
	{
		data->events.rarr_pressed = 1;
		more_keys(data);
		data->events.rarr_pressed = 0;
		old = x;
	}
	return (0);
}
