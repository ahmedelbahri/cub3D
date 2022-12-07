/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:21:56 by akadi             #+#    #+#             */
/*   Updated: 2022/12/07 19:06:47 by ahel-bah         ###   ########.fr       */
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
	if (!ft_strnstr(av[1], ".cub", ft_strlen(av[1])))
		return (-1);
	return (0);
}

int	dubstrlen(char **content)
{
	int	i;

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

char	**read_map(char *av)
{
	char	**content;
	char	*buffer;
	char	*save;
	int		fd;

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
		data->events.w_pressed = 0;
	else if (key == 0)
		data->events.a_pressed = 0;
	else if (key == 1)
		data->events.s_pressed = 0;
	else if (key == 2)
		data->events.d_pressed = 0;
	else if (key == 124)
		data->events.rarr_pressed = 0;
	else if (key == 123)
		data->events.larr_pressed = 0;
	else if (key == 53)
		exit(0);
	return (0);
}

int	ft_parser(int ac, char **av, t_data *data)
{
	char	**content;

	if (check_argument_error(ac, av) == -1)
		return (printf("ERROR Argument"), -1);
	content = read_map(av[1]);
	if (!content)
		return (printf("ERROR Argumenttt"), -1);
	data->pars.num_lines = dubstrlen(content);
	extract_line(content, data);
	if (data->player.direction == 'N')
		data->player.angle = M_PI / 2;
	if (data->player.direction == 'E')
	{
		data->player.angle = 0;
		data->player.angle = fmod(data->player.angle, (2 * M_PI));
		if (data->player.angle < 0)
			data->player.angle = data->player.angle + (2 * M_PI);
	}
	if (data->player.direction == 'W')
		data->player.angle = M_PI;
	if (data->player.direction == 'S')
		data->player.angle = 3 * M_PI / 2;
	return (0);
}

void	ft_mlx(t_data *data)
{
	data->mlx.win = mlx_new_window(data->mlx.ptr, W, H, "cub3D");
	draw_2d(data);
	mlx_hook(data->mlx.win, 2, 0, register_keys, data);
	mlx_hook(data->mlx.win, 3, 0, key_rel, data);
	mlx_hook(data->mlx.win, 17, 0, quit, NULL);
	mlx_loop_hook(data->mlx.ptr, keys, data);
	mlx_loop(data->mlx.ptr);
}

void	ft_texture(t_data *data)
{
	data->texture.ptr = mlx_xpm_file_to_image(data->mlx.ptr, "./0.xpm", \
		&data->texture.w, &data->texture.h);
}

int	main(int ac, char **av)
{
	t_data	data;

	init_data(&data);
	if (ft_parser(ac, av, &data))
		exit(0);
	ft_texture(&data);
	ft_mlx(&data);
	return (0);
}
