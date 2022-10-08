/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:57:37 by akadi             #+#    #+#             */
/*   Updated: 2022/10/08 18:58:18 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
			return ;
		}
		close(fd);
	}
	else
		printf("ERROR ---\n");
	//printf("clean\n");
}

void	extract_line(char **content, t_data *data)
{
	(void)data;
	int	i;
	char *line;

	i = -1;
	while(++i < 1)
	{
		line = ft_strtrim(line, "\t \n");
		if (ft_strncmp(line, "\0", 1) && !ft_strncmp(line, "NO ", 3))
			check_each_line(line, "NO ");
		else if (ft_strncmp(line, "\0", 1) && !ft_strncmp(line, "SO ", 3))
			check_each_line(line, "SO ");
		else if (ft_strncmp(line, "\0", 1) && !ft_strncmp(line, "WE ", 3))
			check_each_line(line, "WE ");
		else if (ft_strncmp(line, "\0", 1) && !ft_strncmp(line, "EA ", 3))
			check_each_line(line, "EA ");
	}
	//printf("%s", line);
}