/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:57:37 by akadi             #+#    #+#             */
/*   Updated: 2022/10/17 14:57:19 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	color_is_valid(char *color)
{
	int	i;
	int	num;

	i = 0;
	while (color[i])
	{
		if (!ft_isdigit(color[i]))
			return(0);
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


int	is_space(char line)
{
	if ((line >= 9 && line <= 13) || line == ' ')
		return (1);
	return (0);
}

int		layerOneChecker(char *line)
{
	if ((line[0] == 'F' || line[0] == 'C') && (line[1] == ' ') && num_of_comma(line) == 2)
		return (1);
	return (0);
}

int		layerTwoChecker(char *line)
{
	int i;

	i = 2;
	while (line[i] && is_space(line[i]))
		i++;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ',')
			return (0);
		i++;
	}
	return (1);
}

// void	fill_data(char *num, char *line, t_data *data)
// {
// 	(void)data;
// 	(void)line;
// 	if (line[0] == 'C')
// 	{
// 		data->Floor[]
// 	}
// }

int		layerThreeChecker(char *line, t_data *data)
{
	(void)data;
	int j;
	int i;
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
			{
				if (line[0] == 'C')
					data->Floor[k++] = ft_atoi(ft_substr(line, j, i - j));
				if (line[0] == 'F')
					data->sky[k++] = ft_atoi(ft_substr(line, j, i - j));
				//printf("[%s]\n", ft_substr(line, j, i - j));
			}
			j = i+1;
		}
		i++;
	}
	return (1);
}

void	check_color_line(char *line, t_data *data)
{
	(void)data;
	if (layerOneChecker(line) && layerTwoChecker(line) && layerThreeChecker(line, data))
		return ;
	else
	{
		printf("Error color");
		exit(1);
	}
}

void	check_each_line(char *line, char *direction, t_data *data)
{
	int	i;
	int	fd;
	
	i = -1;
	if (!ft_strncmp(line, direction, 3) && ft_strnstr(line, "./texture/", ft_strlen(line)))
	{
		line = ft_strnstr(line, "./texture/", ft_strlen(line));
		fd = open(line, O_RDONLY);
		if (fd < 0)
		{
			printf("FILE ERROR\n");
			exit(1);
		}
		close(fd);
		// fill structure ...
		if (data->SO == NULL && direction[0] == 'S')
			data->SO = line;
		else if (data->NO == NULL && direction[0] == 'N')
			data->NO = line;
		else if (data->EA == NULL && direction[0] == 'E')
			data->EA = line;
		else if (data->WE == NULL && direction[0] == 'W')
			data->WE = line;
		else
			printf("Duplicate\n");
	}
	else
	{
		printf("ERROR ---\n");
		exit(1);
	}
}

int	lines_before_map(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] != '1' && content[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	check_line(char *line, t_data *data, int *j)
{
	if (line[0] && line[0] == 'N')
		check_each_line(line, "NO ", data);
	else if (line[0] && line[0] == 'S')
		check_each_line(line, "SO ", data);
	else if (line[0] && line[0] == 'W')
		check_each_line(line, "WE ", data);
	else if (line[0] && line[0] == 'E')
		check_each_line(line, "EA ", data);
	else if (line[0] && line[0] == 'F')
		check_color_line(line, data);
	else if (line[0] && line[0] == 'C')
		check_color_line(line, data);
	else if (line[0])
	{
		printf("map Error\n");
		return ;
	}
	else
		*j+=1;
}

void	extract_line(char **content, t_data *data)
{
	int	i;
	int	j;
	char *line;

	i = -1;
	j = 0;
	while(content[++i])
	{
		line = ft_strtrim(content[i], "\t \n");
		if (line[0] && lines_before_map(line))
			break ;
		check_line(line, data, &j);
	}
	if (i - j -1 < 5)
		printf("Error\n");
	printf("##%s##\n", data->NO);
	printf("##%s##\n", data->SO);
	printf("##%s##\n", data->EA);
	printf("##%s##\n", data->WE);
	printf("##%d##\n", data->Floor[0]);
	printf("##%d##\n", data->Floor[1]);
	printf("##%d##\n", data->Floor[2]);
	printf("##%d##\n", data->sky[0]);
	printf("##%d##\n", data->sky[1]);
	printf("##%d##\n", data->sky[2]);
}