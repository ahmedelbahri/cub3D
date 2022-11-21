/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:21:56 by akadi             #+#    #+#             */
/*   Updated: 2022/11/21 18:27:38 by akadi            ###   ########.fr       */
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

int	dubstrlen(char **content)
{
	int i;
	i = 0;
	while (content[i] != NULL)
		i++;
	return (i);
}

char	*ft_strjoin_read(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		return (NULL);
	p = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		p[i] = s2[j];
		i++;
		j++;
	}
	p[i] = '\0';
	return (free(s1), free(s2), p);
}

char **read_map(char *av)
{
	char	**content;
	char	*buffer;
	char	*save;
	int 	fd;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (NULL);
	save = ft_strdup("");
	buffer = get_next_line(fd);
	while (buffer)
	{
		save = ft_strjoin_read(save, buffer);
		buffer = get_next_line(fd);
	}
	content = ft_split(save, '\n');
	free(save);
	close(fd);
	return (content);
}

int	key_rel(int key, t_data *data)
{
	if (key == 13)
		data->w_pressed = 0;
	if (key == 0)
		data->a_pressed = 0;
	if (key == 1)
		data->s_pressed = 0;
	if (key == 2)
		data->d_pressed = 0;
	if (key == 124)
		data->rarr_pressed = 0;
	if (key == 123)
		data->larr_pressed = 0;
	printf("w %d s %d rarr %d larr %d\n", data->w_pressed, data->s_pressed, data->rarr_pressed, data->larr_pressed);
	return (0);
}

int main(int ac, char **av)
{
	char	**content;
	t_data	data;

	data.mlx = mlx_init();
	if (check_argument_error(ac, av) == -1)
		return (printf("ERROR Argument"), -1);
	content = read_map(av[1]);
	if (!content)
		return (printf("ERROR Argumenttt"), -1);
	data.num_lines = dubstrlen(content);
	init_data(&data);
	extract_line(content, &data);
	data.window = mlx_new_window(data.mlx, W, H, "cub3D");
	if (data.Direction == 'N')
		data.angle = M_PI/2;
	if (data.Direction == 'E')
	{
		data.angle = 0;
		data.angle = fmod(data.angle, (2 * M_PI));
		if (data.angle < 0)
			data.angle = data.angle + (2 * M_PI);
	}
	if (data.Direction == 'W')
		data.angle = M_PI;
	if (data.Direction == 'S')
		data.angle = 3 * M_PI/2;
	draw_2d(&data);
	mlx_hook(data.window, 2, (1L<<0), keys, &data);
	mlx_hook(data.window, 3, (1L<<1), key_rel, &data);
	mlx_hook(data.window, 17, 0, quit, NULL);
	mlx_loop(data.mlx);
	return (0);
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
