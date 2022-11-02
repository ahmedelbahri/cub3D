/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:46:12 by akadi             #+#    #+#             */
/*   Updated: 2022/11/02 11:48:39 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_color_line(char *line, t_data *data)
{
	if (layerOneChecker(line) && layerTwoChecker(line) \
	&& layerThreeChecker(line, data))
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
}