/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:31:04 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/12/17 22:29:23 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

void	color(t_data *data, int x, int y)
{
	if (data->map[y][x] == '0')
		data->color = 0xffffff;
	else if (data->map[y][x] == '1')
		data->color = 0xff0000;
	else if (data->map[y][x] == '*')
		data->color = 0x000000;
	else if (data->map[y][x] == '2')
		data->color = 0xFFFF00;
	else if (data->map[y][x] == '3')
		data->color = 0x00FF00;
}

void	rectangle(int x, int y, t_data *data)
{
	int	i;
	int	j;

	i = x * SQ / 5;
	if (data->color == 0x000000)
		return ;
	while (i < (x + 1) * SQ / 5)
	{
		j = y * SQ / 5;
		while (j < (y + 1) * SQ / 5)
		{
			my_mlx_pixel_put(data, i, j);
			j++;
		}
		i++;
	}
}

void	draw_line(t_data *data, int x, int y, int y2)
{
	int	i;

	i = y;
	while (i < y2)
	{
		my_mlx_pixel_put(data, x, i);
		i++;
	}
}

void	ft_open_n_close(t_data *data)
{
	int	x;
	int	y;

	x = data->player_i.x / SQ;
	y = data->player_i.y / SQ;
	if (data->map[y][x + 1] == '2')
		data->map[y][x + 1] = '3';
	else if (data->map[y][x + 1] == '3')
		data->map[y][x + 1] = '2';
	if (data->map[y + 1][x] == '2')
		data->map[y + 1][x] = '3';
	else if (data->map[y + 1][x] == '3')
		data->map[y + 1][x] = '2';
	if (data->map[y - 1][x] == '2')
		data->map[y - 1][x] = '3';
	else if (data->map[y - 1][x] == '3')
		data->map[y - 1][x] = '2';
	if (data->map[y][x - 1] == '2')
		data->map[y][x - 1] = '3';
	else if (data->map[y][x - 1] == '3')
		data->map[y][x - 1] = '2';
}
