/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:52:35 by akadi             #+#    #+#             */
/*   Updated: 2022/11/02 16:11:57 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_map_error(t_data *data, t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (i + 1 == info->num_lines && !lines_before_map(data->map[i]))
			{
				printf("mapppp EEError\n");
				exit(1);
			}
			if (data->map[i][j] == '0' && !check_up_down(data, i , j))
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

void	malloc_map(t_data *data, char **content, t_info *info, int i)
{
	int	k;
	int	z;
	char	*trim;

	k = -1;
	info->num_lines = info->num_lines - i;
	data->map = malloc(sizeof(char *) * info->num_lines + 1);
	while (++k < info->num_lines)
		data->map[k] = malloc(sizeof(char) * data->MAX_LINE + 1);
	k = -1;
	while (++k < info->num_lines)
	{
		trim = ft_strtrim(content[i], "\n");
		z = ft_strlcpy(data->map[k], trim, data->MAX_LINE + 1);
		while (z < data->MAX_LINE)
		{
			data->map[k][z] = '*';
			if (z + 1 == data->MAX_LINE)
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
		if(data->MAX_LINE < len)
			data->MAX_LINE = len;
		i++;
		free(trim);
	}
}

void	condition(char **content, int i, t_info *info, t_data *data)
{
	if (i - info->empty_lines -1 < 5)
	{
		printf("Missing / Error\n");
		exit(1);
	}
	else
	{
		// map...
		tallest_line(content, i, data);
		malloc_map(data, content, info, i);
		fill_map_with_z(data);
		check_map_error(data, info);
		if (!data->Direction)
		{
			
			printf("no direction\n");
			exit(1);
		}
	}
}