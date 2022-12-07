/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 15:29:42 by akadi             #+#    #+#             */
/*   Updated: 2022/12/07 21:06:29 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_data *cor, int i, int j)
{
	char	*dst;

	if (i > 0 && j > 0 && W > i && H > j)
	{
		dst = cor->mlx.addr + (j * cor->mlx.line_length + \
		i * (cor->mlx.bits_per_pixel / 8));
		*(unsigned int *)dst = cor->color;
	}
}

void	image(t_data *file)
{
	file->mlx.img = mlx_new_image(file->mlx.ptr, W, H);
	file->mlx.addr = mlx_get_data_addr(file->mlx.img, \
		&file->mlx.bits_per_pixel, \
			&file->mlx.line_length, &file->mlx.endian);
}

void	color(t_data *data, int x, int y)
{
	if (data->map[y][x] == '0')
		data->color = 0xffffff;
	else if (data->map[y][x] == '1')
		data->color = 0xff0000;
	else if (data->map[y][x] == '*')
		data->color = 0x000000;
}

float	max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

void	dda(t_data *data, float x, float y, float x1, float y1)
{
	float	step_x;
	float	step_y;
	float	max_v;
	int		i;

	step_x = x1 - x;
	step_y = y1 - y;
	max_v = max(fabs(step_x), fabs(step_y));
	step_x /= max_v;
	step_y /= max_v;
	i = 0;
	while (i <= max_v)
	{
		my_mlx_pixel_put(data, x, y);
		x += step_x;
		y += step_y;
		i++;
	}
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

void	draw_circle(float xc, float yc, float x, float y, t_data *data)
{
	data->color = 0x0000ff;
	my_mlx_pixel_put(data, xc + x, yc + y);
	my_mlx_pixel_put(data, xc - x, yc + y);
	my_mlx_pixel_put(data, xc + x, yc - y);
	my_mlx_pixel_put(data, xc - x, yc - y);
	my_mlx_pixel_put(data, xc + y, yc + x);
	my_mlx_pixel_put(data, xc - y, yc + x);
	my_mlx_pixel_put(data, xc + y, yc - x);
	my_mlx_pixel_put(data, xc - y, yc - x);
}

void	cercle(float xc, float yc, float r, t_data *data)
{
	float	x;
	float	y;
	float	d;

	x = 0;
	y = r;
	d = 3 - 2 * r;
	draw_circle(xc, yc, x, y, data);
	while (y >= x)
	{
		x++;
		if (d > 0)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;
		draw_circle(xc, yc, x, y, data);
	}
}

int	checkiswall(t_data *data, t_index inter, int check, int face)
{
	t_int_idx	index;

	if (face == 1)
		inter.y += check;
	else
		inter.x += check;
	if (inter.y > data->pars.num_lines * SQ)
		return (0);
	if (inter.x > data->pars.max_line * SQ)
		return (0);
	index.x = floor(inter.x / SQ);
	index.y = floor(inter.y / SQ);
	if (index.y < 0 || index.y >= data->pars.num_lines)
		return (0);
	if (index.x < 0 || index.x >= data->pars.max_line)
		return (0);
	if (data->map[index.y][index.x] == '1')
		return (0);
	return (1);
}

double	distance(double x, double y, double x1, double y1)
{
	return (sqrt(pow(x1 - x, 2) + pow(y1 - y, 2)));
}

double	horizontal_inter(t_data *data, t_index player, double angle)
{
	t_index	first;
	t_index	steps;
	int		check;

	check = 0;
	angle = fmod(angle, (2 * M_PI));
	if (angle < 0)
		angle = angle + (2 * M_PI);
	first.y = floor(player.y / SQ) * SQ;
	if ((angle > 0 && angle < M_PI))
		first.y += SQ;
	first.x = player.x + (first.y - player.y) / tan(angle);
	steps.y = SQ;
	if (!(angle > 0 && angle < M_PI))
	{
		steps.y *= -1;
		check = -1;
	}
	steps.x = steps.y / tan(angle);
	if ((angle < 0.5 * M_PI || angle > 1.5 * M_PI) && steps.x < 0)
		steps.x *= -1;
	if (!(angle < 0.5 * M_PI || angle > 1.5 * M_PI) && steps.x > 0)
		steps.x *= -1;
	while (checkiswall(data, first, check, 1))
	{
		first.x += steps.x;
		first.y += steps.y;
	}
	data->inter.ray_hor_inter_x = first.x;
	data->inter.ray_hor_inter_y = first.y;
	return (distance(player.x, player.y, first.x, first.y));
}

double	vertical_inter(t_data *data, t_index player, double angle)
{
	t_index	first;
	t_index	steps;
	int		check;

	check = 0;
	angle = fmod(angle, (2 * M_PI));
	if (angle < 0)
		angle = angle + (2 * M_PI);
	first.x = floor(player.x / SQ) * SQ;
	if ((angle < 0.5 * M_PI || angle > 1.5 * M_PI))
		first.x += SQ;
	first.y = player.y + (first.x - player.x) * tan(angle);
	steps.x = SQ;
	if (!(angle < 0.5 * M_PI || angle > 1.5 * M_PI))
	{
		steps.x *= -1;
		check = -1;
	}
	steps.y = steps.x * tan(angle);
	if (!(angle > 0 && angle < M_PI) && steps.y > 0)
		steps.y *= -1;
	if ((angle > 0 && angle < M_PI) && steps.y < 0)
		steps.y *= -1;
	while (checkiswall(data, first, check, 0))
	{
		first.x += steps.x;
		first.y += steps.y;
	}
	data->inter.ray_ver_inter_x = first.x;
	data->inter.ray_ver_inter_y = first.y;
	return (distance(player.x, player.y, first.x, first.y));
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

void	project(t_data *data, double dist, int ray_i, double angle, double hit)
{
	int		y;
	int		yy;
	int		*s;
	int		offset_x;
	int		offset_y;
	double	projection_plane;
	double	wall_height_stripe;

	dist = dist * cos((angle - data->player.angle));
	projection_plane = (W / 2) / tan(FOV / 2 * M_PI / 180);
	wall_height_stripe = SQ * projection_plane / dist;
	y = (H / 2) - (wall_height_stripe / 2);
	data->color = 0xFFFFFF;
	s = (int *)mlx_get_data_addr(data->texture.ptr, \
		&data->texture.bits_per_pixel, &data->texture.line_length, \
			&data->texture.endian);
	offset_x = (hit - (int)hit) * (data->texture.w);
	yy = y;
	while (yy < wall_height_stripe + y)
	{
		offset_y = (yy - y) * ((float)data->texture.h / wall_height_stripe);
		data->color = s[(data->texture.h * offset_y) + offset_x];
		my_mlx_pixel_put(data, ray_i, yy);
		yy++;
	}
	data->color = 0x6B6B6B;
	draw_line(data, ray_i, 0, y);
	data->color = 0xA9A9A9;
	draw_line(data, ray_i, wall_height_stripe + y, H);
}

int	draw_2d(t_data *data)
{
	int		x;
	int		y;
	t_index	player;
	double	ray_hor_inter_dis;
	double	ray_ver_inter_dis;
	double	ray_angle;
	int		i;

	x = 0;
	y = 0;
	mlx_clear_window(data->mlx.ptr, data->mlx.win);
	image(data);
	data->color = 0x0000FF;
	player.y = (data->player.y * SQ) + SQ / 2;
	player.x = (data->player.x * SQ) + SQ / 2;
	ray_angle = data->player.angle - ((FOV / 2) * (M_PI / 180));
	i = 0;
	while (i < W)
	{
		ray_hor_inter_dis = horizontal_inter(data, player, ray_angle);
		ray_ver_inter_dis = vertical_inter(data, player, ray_angle);
		data->color = 0xFFFF00;
		if (ray_hor_inter_dis < ray_ver_inter_dis)
			project(data, ray_hor_inter_dis, i, ray_angle, \
				data->inter.ray_hor_inter_x / SQ);
		else
			project(data, ray_ver_inter_dis, i, ray_angle, \
				data->inter.ray_ver_inter_y / SQ);
		ray_angle += (FOV * (M_PI / 180) / W);
		i++;
	}
	while (y < data->pars.num_lines)
	{
		x = 0;
		while (x < data->pars.max_line)
		{
			color(data, x, y);
			rectangle(x, y, data);
			x++;
		}
		y++;
	}
	data->color = 0x000000;
	dda(data, player.x / 5, player.y / 5, (player.x / 5) + \
		cos(data->player.angle) * (SQ / 5) / 2 * 2, (player.y / 5) + \
			sin(data->player.angle) * (SQ / 5) / 3 * 2);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->mlx.img, 0, 0);
	return (0);
}
