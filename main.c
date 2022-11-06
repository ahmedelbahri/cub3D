/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:21:56 by akadi             #+#    #+#             */
/*   Updated: 2022/11/06 17:47:32 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	quit(void)
{
	exit(0);
	return (0);
}

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

char **read_map(char *av, t_data *data)
{
	char	**content;
	int 	fd;
	int		j;
	
	j = 0;
	data->num_lines = lines_of_file(av);
	content = malloc(sizeof(char *) * data->num_lines + 1);
	if (!content)
		return (printf("Malloc Error"), NULL);
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (NULL);
	j = -1;
	while(++j < data->num_lines)
		content[j] = get_next_line(fd);
	content[j] = NULL;
	close(fd);
	return (content);
}

int main(int ac, char **av)
{
	char	**content;
	t_data	data;
	//t_data	data;

	data.mlx = mlx_init();
	if (check_argument_error(ac, av) == -1)
		return (printf("ERROR Argument"), -1);
	content = read_map(av[1], &data);
	if (!content)
		return (printf("ERROR Argumenttt"), -1);
	init_data(&data);
	extract_line(content, &data);
	data.window = mlx_new_window(data.mlx, 1300, 900, "cub3D");
	draw_2d(&data);
	mlx_hook(data.window, 2, 0L, keys, &data);
	mlx_hook(data.window, 17, 1L << 0, quit, NULL);
	mlx_loop(data.mlx);
}


	// printf("##%s##\n", data.NO);
	// printf("##%s##\n", data.SO);
	// printf("##%s##\n", data.EA);
	// printf("##%s##\n", data.WE);
	// printf("##%d##\n", data.Floor[0]);
	// printf("##%d##\n", data.Floor[1]);
	// printf("##%d##\n", data.Floor[2]);
	// printf("##%d##\n", data.sky[0]);
	// printf("##%d##\n", data.sky[1]);
	// printf("##%d##\n", data.sky[2]);
	// printf("##%c##\n", data.Direction);
	// printf("##%d##\n", data.X);
	// printf("##%d##\n", data.Y);
	// printf("##%d##\n", data.MAX_LINE);
	// printf("##%d##\n", data.num_lines);

	