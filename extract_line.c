/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:57:37 by akadi             #+#    #+#             */
/*   Updated: 2022/10/09 22:43:17 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// void	parse_color_line(char *line)
// {
// 	//char	**tmp;
// 	int		i;

// 	i = 0;
// 	while (line)
// 	{
// 		if (*line >= 48 && *line <= 57)
// 			break ;
// 		line++;
// 	}
// 	//tmp = ft_split(line, ',');
// 	printf("%s\n", line);
// }

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

int		layerThreeChecker(char *line)
{
	int j = 0;
	int i;
	i = 2;
	while (line[i] && is_space(line[i]))
		i++;
	int	strStart = i;
	int len = strlen(line + i);
	j = i;
	while (line[i])
	{
		if (line[i] == ',' || len - 1 == i)
		{
			if (len - 1 == i)
				i++;
			printf("%s\n", ft_substr(line + strStart, j, i - j));
			j = i+1;
		}
		i++;
	}
	return (1);
}

void	check_color_line(char *line, char *str)
{
	(void)line;
	(void)str;
	// char	*color;
	if (layerOneChecker(line) && layerTwoChecker(line) && layerThreeChecker(line))
	{
		// printf("cleaaaan\n");
		return ;
	}
	else
	{
		printf("Error color");
		exit(1);
	}
}

void	check_each_line(char *line, char *str)
{
	int	i;
	
	i = -1;
	if ((line[0] == str[0]) && (line[1] == str[1]) && (line[2] == str[2]) \
	&& ft_strnstr(line, "./texture/", ft_strlen(line)))
	{
		line = ft_strnstr(line, "./texture/", ft_strlen(line));
		int fd = open(line, O_RDONLY);
		if (fd < 0)
		{
			printf("FILE ERROR\n");
			exit(1);
		}
		close(fd);
	}
	else
	{
		printf("ERROR ---\n");
		exit(1);
	}
}

void	extract_line(char **content, t_data *data)
{
	(void)data;
	int	i;
	char *line;

	i = -1;
	while(++i < 6)
	{
		line = ft_strtrim(content[i], "\t \n");
		if (ft_strcmp(line, "\0") && line[0] == 'N')
			check_each_line(line, "NO ");
		else if (ft_strcmp(line, "\0") && line[0] == 'S')
			check_each_line(line, "SO ");
		else if (ft_strcmp(line, "\0") && line[0] == 'W')
			check_each_line(line, "WE ");
		else if (ft_strcmp(line, "\0") && line[0] == 'E')
			check_each_line(line, "EA ");
		else if (ft_strcmp(line, "\0") && line[0] == 'F')
			check_color_line(line, "F ");
		else if (ft_strcmp(line, "\0") && line[0] == 'C')
			check_color_line(line, "C ");
	}
	//printf("%s", line);
}