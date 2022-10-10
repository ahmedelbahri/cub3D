/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:21:56 by akadi             #+#    #+#             */
/*   Updated: 2022/10/10 13:01:47 by akadi            ###   ########.fr       */
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

char **read_map(char *av)
{
	char	**content;
	int 	fd;
	int		j;
	int		i;
	
	j = 0;
	i = 0;
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (NULL);
	while(get_next_line(fd))
		i++;
	content = malloc(sizeof(char *) * i);
	if (!content)
		return (printf("Malloc Error"), NULL);
	close(fd);
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (NULL);
	j = -1;
	while(++j < i)
		content[j] = get_next_line(fd);
	return (content);
}

int main(int ac, char **av)
{
	char	**content;
	t_data	data;

	if (check_argument_error(ac, av) == -1)
		return (printf("ERROR Argument"), -1);
	content = read_map(av[1]);
	if (!content)
		return (printf("ERROR Argumenttt"), -1);
	extract_line(content, &data);
	// int i = -1;
	// while(++i < 105)
	// 	printf("%s", content[i]);
}