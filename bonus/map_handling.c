/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:52:35 by akadi             #+#    #+#             */
/*   Updated: 2022/12/16 20:28:42 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	check_map_error(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (i + 1 == data->pars.num_lines \
				&& !lines_before_map(data->map[i]))
			{
				printf("mapppp EEError\n");
				exit(1);
			}
			if ((data->map[i][j] == '0' && !check_up_down(data, i, j)) \
			|| (data->map[i][j] == '2' && !check_door(data, i, j)))
			{
				printf("mapppp Error\n");
				exit(1);
			}
			j++;
		}
		i++;
	}
}

int	check_up_down(t_data *data, int i, int j)
{
	if (data->map[i - 1][j] == '*' || data->map[i + 1][j] == '*')
		return (0);
	if (data->map[i][j - 1] == '*' || data->map[i][j + 1] == '*')
		return (0);
	else
		return (1);
}

void	malloc_map(t_data *data, char **content, int i)
{
	int		k;
	int		z;
	char	*trim;

	k = -1;
	data->pars.num_lines = data->pars.num_lines - i;
	data->map = malloc(sizeof(char *) * data->pars.num_lines + 1);
	while (++k < data->pars.num_lines)
		data->map[k] = malloc(sizeof(char) * data->pars.max_line + 1);
	k = -1;
	while (++k < data->pars.num_lines)
	{
		trim = ft_strtrim(content[i], "\n");
		z = ft_strlcpy(data->map[k], trim, data->pars.max_line + 1);
		while (z < data->pars.max_line)
		{
			data->map[k][z] = '*';
			if (z + 1 == data->pars.max_line)
				data->map[k][z + 1] = '\0';
			z++;
		}
		i++;
		free(trim);
	}
	data->map[k] = NULL;
}

void	tallest_line(char **content, int i, t_data *data)
{
	int		len;
	char	*trim;

	while (content[i])
	{
		trim = ft_strtrim(content[i], "\n");
		len = ft_strlen(trim);
		if (data->pars.max_line < len)
			data->pars.max_line = len;
		i++;
		free(trim);
	}
}

void	condition(char **content, int i, t_data *data)
{
	if (i - data->pars.empty_lines -1 < 5)
	{
		printf("Error\n Missing data");
		exit(1);
	}
	else
	{
		tallest_line(content, i, data);
		malloc_map(data, content, i);
		fill_map_with_z(data);
		check_map_error(data);
		if (!data->player.direction)
		{
			printf("Error\n no direction");
			exit(1);
		}
	}
}
