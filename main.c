/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:21:56 by akadi             #+#    #+#             */
/*   Updated: 2022/11/01 15:20:33 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_argument_error(int ac, char **av)
{
	if (ac != 2)
		return (-1);
	if (!ft_strnstr(av[1], ".cub", ft_strlen(av[1])) )
		return (-1);
	return (0);
}

int	lines_of_file(char *av)
{
	int	fd;
	int	i;
	char *line;

	i = 0;
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while(line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (i);
}

char **read_map(char *av, t_info *info)
{
	char	**content;
	int 	fd;
	int		j;
	
	j = 0;
	info->num_lines = lines_of_file(av);
	content = malloc(sizeof(char *) * info->num_lines + 1);
	if (!content)
		return (printf("Malloc Error"), NULL);
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (NULL);
	j = -1;
	while(++j < info->num_lines)
		content[j] = get_next_line(fd);
	content[j] = NULL;
	close(fd);
	return (content);
}

int main(int ac, char **av)
{
	char	**content;
	t_data	data;
	t_info	info;

	if (check_argument_error(ac, av) == -1)
		return (printf("ERROR Argument"), -1);
	content = read_map(av[1], &info);
	if (!content)
		return (printf("ERROR Argumenttt"), -1);
	init_data(&data, &info);
	extract_line(content, &data, &info);
	// int i = -1;
	// while(++i < 105)
	// 	printf("%s", content[i]);
}