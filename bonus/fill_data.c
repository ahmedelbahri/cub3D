/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:00:06 by akadi             #+#    #+#             */
/*   Updated: 2022/12/18 22:36:18 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	fill_map_with_z(t_data *data)
{
	int	s;
	int	k;

	k = 0;
	s = 0;
	while (data->map[k])
	{
		s = 0;
		while (data->map[k][s])
		{
			fill_direction(data, k, s);
			s++;
		}
		k++;
	}
}

void	fill_color(char line, char *sub, t_data *data, int k)
{
	if (line == 'C')
	{
		data->texture.sky[k] = ft_atoi(sub);
		free(sub);
	}
	if (line == 'F')
	{
		data->texture.floor[k] = ft_atoi(sub);
		free(sub);
	}
}

void	fill_direction(t_data *data, int k, int s)
{
	if (data->map[k][s] == ' ')
		data->map[k][s] = '*';
	else if (data->map[k][s] == 'E' || data->map[k][s] == 'S' \
	|| data->map[k][s] == 'W' || data->map[k][s] == 'N')
	{
		if (data->player.direction)
		{
			printf("Direction full\n");
			exit(1);
		}
		data->player.direction = data->map[k][s];
		data->player.x = s;
		data->player.y = k;
		data->map[k][s] = '0';
	}
	else if (data->map[k][s] != '0' && data->map[k][s] != '1' \
	&& data->map[k][s] != '*' && data->map[k][s] != '2')
	{
		printf("invalid map\n");
		exit(1);
	}
}

void	ft_read_anime(t_data *data, int fd[6], int i)
{
	fd[0] = open("./../texture/DOOR.xpm", O_RDONLY);
	fd[1] = open("./../texture/1.xpm", O_RDONLY);
	fd[2] = open("./../texture/2.xpm", O_RDONLY);
	fd[3] = open("./../texture/3.xpm", O_RDONLY);
	fd[4] = open("./../texture/4.xpm", O_RDONLY);
	fd[5] = open("./../texture/5.xpm", O_RDONLY);
	while (++i < 6)
	{
		if (fd[i] < 0)
		{
			printf("Error\n missing door texture file.");
			exit(1);
		}
	}
	data->proj.gun[0] = mlx_xpm_file_to_image(data->mlx.ptr, \
	"./../texture/1.xpm", &data->proj.gun_w, &data->proj.gun_h);
	data->proj.gun[1] = mlx_xpm_file_to_image(data->mlx.ptr, \
	"./../texture/2.xpm", &data->proj.gun_w, &data->proj.gun_h);
	data->proj.gun[2] = mlx_xpm_file_to_image(data->mlx.ptr, \
	"./../texture/3.xpm", &data->proj.gun_w, &data->proj.gun_h);
	data->proj.gun[3] = mlx_xpm_file_to_image(data->mlx.ptr, \
	"./../texture/4.xpm", &data->proj.gun_w, &data->proj.gun_h);
	data->proj.gun[4] = mlx_xpm_file_to_image(data->mlx.ptr, \
	"./../texture/5.xpm", &data->proj.gun_w, &data->proj.gun_h);
}

void	condition_texture(t_data *data, char direction, char *line)
{
	int	i;
	int	fd[6];

	i = -1;
	ft_read_anime(data, fd, i);
	while (++i < 6)
		close(fd[i]);
	data->coord.door = "./../texture/DOOR.xpm";
	if (data->coord.so == NULL && direction == 'S')
		data->coord.so = ft_strdup(line);
	else if (data->coord.no == NULL && direction == 'N')
		data->coord.no = ft_strdup(line);
	else if (data->coord.ea == NULL && direction == 'E')
		data->coord.ea = ft_strdup(line);
	else if (data->coord.we == NULL && direction == 'W')
		data->coord.we = ft_strdup(line);
	else
	{
		printf("Error\n Duplicate symbol");
		exit(1);
	}
}
