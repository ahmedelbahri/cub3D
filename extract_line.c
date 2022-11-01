/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:57:37 by akadi             #+#    #+#             */
/*   Updated: 2022/11/01 16:24:55 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
			continue;
		}
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

int		layerOneChecker(char *line)
{
	if ((line[0] == 'F' || line[0] == 'C') && (line[1] == ' ' || line[1] == '\t') && num_of_comma(line) == 2)
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
		if (!is_space(line[i]) && !ft_isdigit(line[i]) && line[i] != ',')
			return (0);
		i++;
	}
	return (1);
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

int		layerThreeChecker(char *line, t_data *data)
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
			j = i+1;
		}
		i++;
	}
	return (1);
}

void	check_color_line(char *line, t_data *data)
{
	if (layerOneChecker(line) && layerTwoChecker(line) && layerThreeChecker(line, data))
		return ;
	else
	{
		printf("Error color");
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

void	check_each_line(char *line, char *direction, t_data *data)
{
	int	i;
	int	fd;

	i = -1;
	if ((!ft_strncmp(line, direction, 3) || !ft_strncmp(&line[2], "\t", 1)) \
	&& ft_strnstr(line, "./texture/", ft_strlen(line)))
	{
		line = ft_strnstr(line, "./texture/", ft_strlen(line));
		fd = open(line, O_RDONLY);
		if (fd < 0)
		{
			printf("FILE ERROR\n");
			exit(1);
		}
		close(fd);
		condition_texture(data, direction[0], line);
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
		if (content[i] != '1' && content[i] != ' ' && content[i] != '\t' 
		&& content[i] != '*')
			return (0);
		i++;
	}
	return (1);
}

void	check_line(char *line, t_data *data, t_info *info)
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
		exit(1) ;
	}
	else
		info->empty_lines+=1;
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
		data->X = k;
		data->Y = s;
		data->map[k][s] = '0';
	}
	else if (data->map[k][s] != '0' && data->map[k][s] != '1' 
	&& data->map[k][s] != '*')
	{
		printf("invalid map\n");
			exit(1);
	}
}

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

int	check_up_down(t_data *data, int i, int j)
{
	if (data->map[i - 1][j] == '*' || data->map[i + 1][j] == '*')
		return (0);
	if (data->map[i][j - 1] == '*' || data->map[i][j + 1] == '*')
		return (0);
	else
		return (1);
}

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
			printf("no map\n");
			exit(1);
		}
	}
}

void	extract_line(char **content, t_data *data, t_info *info)
{
	int	i;
	char *line;

	i = -1;
	while (content[++i])
	{
		line = ft_strtrim(content[i], "\t \n");
		if (line[0] && lines_before_map(line))
		{
			free(line);
			break ;
		}
		check_line(line, data, info);
		free(line);
	}
	condition(content, i, info, data);
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
	printf("##%c##\n", data->Direction);
	printf("##%d##\n", data->X);
	printf("##%d##\n", data->Y);
}