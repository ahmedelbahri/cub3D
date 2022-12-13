/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:21:56 by akadi             #+#    #+#             */
/*   Updated: 2022/12/13 00:53:00 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	quit(void)
{
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
	data->texture.ptr = mlx_xpm_file_to_image(data->mlx.ptr, data->coord.we,
			&data->texture.w, &data->texture.h);
	data->proj.we = (int *)mlx_get_data_addr(data->texture.ptr, \
		&data->texture.bits_per_pixel, &data->texture.line_length, \
			&data->texture.endian);
	data->texture.ptr = mlx_xpm_file_to_image(data->mlx.ptr, data->coord.ea,
			&data->texture.w, &data->texture.h);
	data->proj.ea = (int *)mlx_get_data_addr(data->texture.ptr, \
		&data->texture.bits_per_pixel, &data->texture.line_length, \
			&data->texture.endian);
	data->texture.ptr = mlx_xpm_file_to_image(data->mlx.ptr, data->coord.no,
			&data->texture.w, &data->texture.h);
	data->proj.no = (int *)mlx_get_data_addr(data->texture.ptr, \
		&data->texture.bits_per_pixel, &data->texture.line_length, \
			&data->texture.endian);
	data->texture.ptr = mlx_xpm_file_to_image(data->mlx.ptr, data->coord.so,
			&data->texture.w, &data->texture.h);
	data->proj.so = (int *)mlx_get_data_addr(data->texture.ptr, \
		&data->texture.bits_per_pixel, &data->texture.line_length, \
			&data->texture.endian);
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
