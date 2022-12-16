/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:31:04 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/12/16 20:08:04 by ahel-bah         ###   ########.fr       */
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

void	draw_circle(float xc, float yc, t_index *index, t_data *data)
{
	data->color = 0x0000ff;
	my_mlx_pixel_put(data, xc + index->x, yc + index->y);
	my_mlx_pixel_put(data, xc - index->x, yc + index->y);
	my_mlx_pixel_put(data, xc + index->x, yc - index->y);
	my_mlx_pixel_put(data, xc - index->x, yc - index->y);
	my_mlx_pixel_put(data, xc + index->y, yc + index->x);
	my_mlx_pixel_put(data, xc - index->y, yc + index->x);
	my_mlx_pixel_put(data, xc + index->y, yc - index->x);
	my_mlx_pixel_put(data, xc - index->y, yc - index->x);
}

void	cercle(float xc, float yc, float r, t_data *data)
{
	t_index	index;
	float	d;

	index.x = 0;
	index.y = r;
	d = 3 - 2 * r;
	draw_circle(xc, yc, &index, data);
	while (index.y >= index.x)
	{
		index.x++;
		if (d > 0)
		{
			index.y--;
			d = d + 4 * (index.x - index.y) + 10;
		}
		else
			d = d + 4 * index.x + 6;
		draw_circle(xc, yc, &index, data);
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
