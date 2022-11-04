/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:21:56 by akadi             #+#    #+#             */
/*   Updated: 2022/11/04 17:17:34 by akadi            ###   ########.fr       */
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

void	rectangle2(int x, int y, t_mlx *mlx_tool)
{
	(void)x;
	(void)y;
	int i = x * 5,j;
	while ( i < (x + 1) *5)
	{
		j = y * 5;
		while (j < (y + 1) * 5)	
		{
			if (i < (x + 1) * 5 - 1)
				mlx_pixel_put(mlx_tool->mlx, mlx_tool->window, i, j, 0xff0000);
			if (j == (y + 1) * 5 - 1)
				mlx_pixel_put(mlx_tool->mlx, mlx_tool->window, i, j, 0xffffff);
			j++;
		}
		i++;
	}
}

void	rectangle1(int x, int y, t_mlx *mlx_tool)
{
	(void)x;
	(void)y;
	int i = x * 5,j;
	while ( i < (x + 1) *5)
	{
		j = y * 5;
		while (j < (y + 1) * 5)	
		{
			if (i < (x + 1) * 5 - 1)
				mlx_pixel_put(mlx_tool->mlx, mlx_tool->window, i, j, 0xffffff);
			if (j == (y + 1) * 5 - 1)
				mlx_pixel_put(mlx_tool->mlx, mlx_tool->window, i, j, 0x000000);
			j++;
		}
		i++;
	}
}

void	rectangle(int x, int y, t_mlx *mlx_tool)
{
	(void)x;
	(void)y;
	int i = x * 5,j;
	while ( i < (x + 1) *5)
	{
		j = y * 5;
		while (j < (y +1) * 5)	
		{
			if (i < (x + 1) * 5 - 1)
				mlx_pixel_put(mlx_tool->mlx, mlx_tool->window, i, j, 0x0000ff);
			if (j == (y +1) * 5 - 1)
				mlx_pixel_put(mlx_tool->mlx, mlx_tool->window, i, j, 0x000000);
			
			j++;
		}
		i++;
	}
}

int main(int ac, char **av)
{
	int x,y = 0;
	char	**content;
	t_data	data;
	t_info	info;
	t_mlx	mlx_tool;

	mlx_tool.mlx = mlx_init();
	if (check_argument_error(ac, av) == -1)
		return (printf("ERROR Argument"), -1);
	content = read_map(av[1], &info);
	if (!content)
		return (printf("ERROR Argumenttt"), -1);
	init_data(&data, &info);
	extract_line(content, &data, &info);
	mlx_tool.window = mlx_new_window(mlx_tool.mlx, 1300, 900, "cub3D");
	while (y < info.num_lines)
	{
		x = 0;
		while (x < data.MAX_LINE)
		{
			if (data.map[y][x] == '0')
				rectangle1(x, y, &mlx_tool);
			if (data.map[y][x] == '1')
				rectangle2(x, y, &mlx_tool);
			if (x == data.Y && y == data.X)
				rectangle(x, y, &mlx_tool);
			x++;
		}
		y++;
	}
	mlx_hook(mlx_tool.window, 17, 1L << 0, quit, NULL);
	printf("##%s##\n", data.NO);
	printf("##%s##\n", data.SO);
	printf("##%s##\n", data.EA);
	printf("##%s##\n", data.WE);
	printf("##%d##\n", data.Floor[0]);
	printf("##%d##\n", data.Floor[1]);
	printf("##%d##\n", data.Floor[2]);
	printf("##%d##\n", data.sky[0]);
	printf("##%d##\n", data.sky[1]);
	printf("##%d##\n", data.sky[2]);
	printf("##%c##\n", data.Direction);
	printf("##%d##\n", data.X);
	printf("##%d##\n", data.Y);
	printf("##%d##\n", data.MAX_LINE);
	printf("##%d##\n", info.num_lines);
	mlx_loop(mlx_tool.mlx);
}