/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:21:56 by akadi             #+#    #+#             */
/*   Updated: 2022/10/06 12:46:30 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void alloc_size_file(char **content)
{
	int fd;
	int j;
	content = malloc(sizeof(char *) * j);
	fd = open("map.cub", O_RDONLY, 0777);
	while(get_next_line(fd))
		j++;
	close(fd);
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	int fd;
	char **content;
	int i = -1, j = 0;

	alloc_size_file(content);
	fd = open("map.cub", O_RDONLY, 0777);
	i = -1;
	while(++i < 105)
	{
		content[i] = get_next_line(fd);
		printf("%s", content[i]);
	}
}