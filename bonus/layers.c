/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:49:20 by akadi             #+#    #+#             */
/*   Updated: 2022/12/16 20:08:04 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

int	layeronechecker(char *line)
{
	if (num_of_comma(line) == 2 && (line[0] == 'F' || line[0] == 'C') \
	&& (line[1] == ' ' || line[1] == '\t'))
		return (1);
	return (0);
}

int	layertwochecker(char *line)
{
	int	i;

	i = 2;
	while (line[i] && is_space(line[i]))
		i++;
	while (line[i])
	{
		if (!is_space(line[i]) && !ft_isdigit(line[i]) && line[i] != ',')
			return (0);
		i++;
	}
	return (1);
}

int	layerthreechecker(char *line, t_data *data)
{
	int			j;
	int			i;
	static int	k;

	j = 0;
	i = 2;
	k = 0;
	while (line[i] && is_space(line[i]))
		i++;
	j = i;
	while (i <= (int)ft_strlen(line))
	{
		if (line[i] == ',' || !line[i + 1])
		{
			if (!line[i + 1])
				i++;
			if (!color_is_valid(ft_substr(line, j, i - j)))
				return (0);
			else
				fill_color(line[0], ft_substr(line, j, i - j), data, k++);
			j = i + 1;
		}
		i++;
	}
	return (1);
}
