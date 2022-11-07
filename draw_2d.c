/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 15:29:42 by akadi             #+#    #+#             */
/*   Updated: 2022/11/07 20:01:20 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_data *cor, int i, int j)
{
	char	*dst;
	int		p;

	p = j * cor->line_length + i * (cor->bits_per_pixel / 8);
	if (i > 0 && j > 0 && W > i && H > j)
	{
		dst = cor->addr + (j * cor->line_length + \
		i * (cor->bits_per_pixel / 8));
		*(unsigned int *)dst = cor->color;
	}
}

void	image(t_data *file)
{
	file->img = mlx_new_image(file->mlx, W, H);
	file->addr = mlx_get_data_addr(file->img, &file->bits_per_pixel, \
			&file->line_length, &file->endian);
}

void	color(t_data *data, int x, int y)
{
	if (data->map[y][x] == '0')
		data->color = 0xffffff;
	if (data->map[y][x] == '1')
		data->color = 0xff0000;
	if (data->map[y][x] == '*')
		data->color = 0x000000;
	if (data->X_player == y && data->Y_player == x)
		data->color = 0x0000ff;
}

void	dda(t_data *data, int x0, int y0,int x1, int y1)
{
	int dx,dy, step, i;
	float Xi, Yi, x, y;

	dx = x1 - x0;
	dy = y1 - y0;
	step = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	Xi = dx/step;
	Yi = dy/step;
	x = x0;
	y = y0;
	i = -1;
	while (++i <= step)
	{
		my_mlx_pixel_put(data, x, y);
		x += Xi;
		y += Yi;
	}
}

void	rectangle(int x, int y, t_data *data)
{
	int i = x * SQ,j;
	while (i < (x + 1) * SQ)
	{
		j = y * SQ;
		while (j < (y + 1) * SQ)
		{
			my_mlx_pixel_put(data, i, j);
			j++;
		}
		i++;
	}
}

void	draw_2d(t_data *data)
{
	int x,y = 0;
	int x_of_player;
	int y_of_player;
	int point_x;
	//int point_y;
	
	image(data);
	
	while (y < data->num_lines)
	{
		x = 0;
		while (x < data->MAX_LINE)
		{
			color(data, x, y);
			rectangle(x, y, data);
			if (data->X_player == y && data->Y_player == x)
			{
				printf("hey\n");
				x_of_player = x;
				y_of_player = y;
			}
			x++;
		}
		y++;
	}
	point_x = ( x_of_player * SQ + (( ((x_of_player + 1) * SQ) - (x_of_player * SQ) )/2) );
	data->color = 0xff00ff;
	dda(data, point_x, y_of_player * (SQ) + SQ/2, point_x,(y  + 1) * SQ/2);
	data->color = 0xff00ff;
	mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
}