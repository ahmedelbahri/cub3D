/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 15:29:42 by akadi             #+#    #+#             */
/*   Updated: 2022/11/21 21:13:29 by akadi            ###   ########.fr       */
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
	else if (data->map[y][x] == '1')
		data->color = 0xff0000;
	else if (data->map[y][x] == '*')
		data->color = 0x000000;
	// if (data->X_player == y && data->Y_player == x)
	// 	data->color = 0x0000ff;
}

// void	dda(t_data *data, float x0, float y0,float x1, float y1)
// {
// 	float dx,dy, step, i;
// 	float Xi, Yi, x, y;

// 	dx = x1 - x0;
// 	dy = y1 - y0;
// 	step = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
// 	Xi = dx/step;
// 	Yi = dy/step;
// 	x = x0;
// 	y = y0;
// 	i = -1;
// 	while (++i <= step)
// 	{
// 		my_mlx_pixel_put(data, x, y);
// 		x += Xi;
// 		y += Yi;
// 	}
// }
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
	int i = 0;

	step_x = x1 - x;
	step_y = y1 - y;
	max_v = max(fabs(step_x), fabs(step_y));
	step_x /= max_v;
	step_y /= max_v;
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
void	draw_circle(float Xc, float Yc, float x, float y, t_data *data)
{
	data->color = 0x0000ff;
	my_mlx_pixel_put(data,Xc+x, Yc+y);
    my_mlx_pixel_put(data,Xc-x, Yc+y);
    my_mlx_pixel_put(data,Xc+x, Yc-y);
    my_mlx_pixel_put(data,Xc-x, Yc-y);
    my_mlx_pixel_put(data,Xc+y, Yc+x);
    my_mlx_pixel_put(data,Xc-y, Yc+x);
    my_mlx_pixel_put(data,Xc+y, Yc-x);
    my_mlx_pixel_put(data,Xc-y, Yc-x);
}
void	cercle(float Xc, float Yc, float r, t_data *data)
{
	float x = 0;
	float y = r;
	float d = 3 - 2* r;
	draw_circle(Xc, Yc, x, y, data);
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
        draw_circle(Xc, Yc, x, y, data);
    }
}

int	checkIsWall(t_data *data, t_index inter, int check, int face)
{
	t_int_idx	index;

	if (face == 1)
		inter.y += check;
	else
		inter.x += check;
	if (inter.y > data->num_lines * SQ)
		return (0);
	if (inter.x > data->MAX_LINE * SQ)
		return (0);
	index.x = floor(inter.x / SQ);
	index.y = floor(inter.y / SQ);
	
	if (index.y < 0 || index.y >= data->num_lines)
		return (0);
	if (index.x < 0 || index.x >= data->MAX_LINE)
		return (0);
	if (data->map[index.y][index.x] == '1')
		return (0);
	return (1);
}

double distance(double x, double y, double x1, double y1)
{
	return (sqrt(pow(x1 - x, 2) + pow(y1 - y, 2)));
}

double	horizontal_inter(t_data *data,t_index player, double angle)
{
	t_index	first;
	t_index	steps;
	double	ray_hor_inter_dis = -1;
	int		ray_hor_wall = 0;
	int		check = 0;
	// int	ray_isdown;
	// int	ray_isleft;

	angle = fmod(angle, (2 * M_PI));
	if (angle < 0)
		angle = angle + (2 * M_PI);
	first.y = floor(player.y / SQ) * SQ;
	if ((angle > 0 && angle < M_PI)) // down
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
	while (checkIsWall(data, first, check, 1))//first.x >= 0 && first.x <= W && first.y >= 0 && first.y <= H
	{
		first.x += steps.x;
		first.y += steps.y;
	}
			data->ray_hor_inter_x = first.x;
			data->ray_hor_inter_y = first.y;
			ray_hor_wall = 1;
	if (ray_hor_wall)
		ray_hor_inter_dis = distance(player.x, player.y, first.x, first.y);
	return (ray_hor_inter_dis);
}
double	vertical_inter(t_data *data,t_index player, double angle)
{
	t_index	first;
	t_index	steps;
	
	double	ray_ver_inter_dis = -1;
	int		ray_ver_wall = 0;
	int		check = 0;
	// int	ray_isdown;
	// int	ray_isleft;

	angle = fmod(angle, (2 * M_PI));
	if (angle < 0)
		angle = angle + (2 * M_PI);
	first.x = floor(player.x / SQ) * SQ;
	if ((angle < 0.5 * M_PI || angle > 1.5 * M_PI))
		first.x += SQ;
	first.y = player.y + (first.x - player.x) * tan(angle);
	steps.x = SQ;
	if (!(angle < 0.5 * M_PI || angle > 1.5 * M_PI))//left
	{
		steps.x *= -1;
		check = -1;
	}
	steps.y = steps.x * tan(angle);
	if (!(angle > 0 && angle < M_PI) && steps.y > 0)
		steps.y *= -1;
	if ((angle > 0 && angle < M_PI) && steps.y < 0)
		steps.y *= -1;
	while (checkIsWall(data, first, check, 0))//first.x >= 0 && first.x <= W && first.y >= 0 && first.y <= H
	{
		first.x += steps.x;
		first.y += steps.y;
	}
			data->ray_ver_inter_x = first.x;
			data->ray_ver_inter_y = first.y;
			//ray_ver_inter_var = ditance;
			ray_ver_wall = 1;
	if (ray_ver_wall)
		ray_ver_inter_dis = distance(player.x, player.y, first.x, first.y);
	return (ray_ver_inter_dis);
}
/// after comparaison
// save :
// wall_inter.x = best.x;
// wall_inter.y = best.y;

void	draw_2d(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	image(data);
	
	while (y < data->num_lines)
	{
		x = 0;
		while (x < data->MAX_LINE)
		{
			color(data, x, y);
			rectangle(x, y, data);
			x++;
		}
		y++;
	}
	data->color = 0x0000ff;
	//printf("X_pla = %f Y_pla %f angle = %f\n",(data->X_player * SQ) + SQ / 2,(data->Y_player * SQ) + SQ / 2, data->angle);/////delete
	my_mlx_pixel_put(data, (data->X_player * SQ) + SQ / 2, (data->Y_player * SQ) + SQ / 2);
	
	// double px = (data->X_player * SQ) + SQ / 2;
	// double py = (data->Y_player * SQ) + SQ / 2;
	// ************************************************************************* //
	// ************************************************************************* //
	// ************************************************************************* //
	// ************************************************************************* //
	t_index	player;
	double	ray_hor_inter_dis;
	double	ray_ver_inter_dis;
	
	player.y = (data->Y_player * SQ) + SQ / 2;
	player.x = (data->X_player * SQ) + SQ / 2;
	//dda(data, player.x, player.y, player.x + cos(data->angle) * 10, player.x + sin(data->angle) * 10);
	// data->angle = fmod(data->angle, (2 * M_PI));
	// if (data->angle < 0)
	// 	data->angle = data->angle + (2 * M_PI);
	double	ray_angle = data->angle - (30 * (M_PI/180));
	// ray_angle = fmod(ray_angle, (2 * M_PI));
	// if (ray_angle < 0)
	// 	ray_angle = ray_angle + (2 * M_PI);
	data->color = 0xffff00;
	for(int i = 0; i < W ;i++)
	{
		if (ray_angle == 0)
			printf("**** %f\n", ray_angle);
		ray_hor_inter_dis = horizontal_inter(data, player, ray_angle);
		ray_ver_inter_dis = vertical_inter(data, player, ray_angle);
		if (ray_hor_inter_dis < ray_ver_inter_dis)
			dda(data, player.x, player.y, data->ray_hor_inter_x, data->ray_hor_inter_y);
		else
			dda(data, player.x, player.y, data->ray_ver_inter_x, data->ray_ver_inter_y);
		ray_angle += (60 * (M_PI/180)/W);
	}
	data->color = 0xff0000;
	dda(data, player.x, player.y, player.x + cos(data->angle) * 20, player.y + sin(data->angle) * 20);
	

	// ************************************************************************* //
	// ************************************************************************* //
	// ************************************************************************* //
	// ************************************************************************* //
	
	//dda(data, px, py, px + cos(data->angle) * SQ, py + sin(data->angle) * SQ);
	//dda(data, px, py, ax + xstep, ay - ystep);
	// printf("X--  %f    Y--  %f\n", floor((ax + xstep)/SQ), floor((ay - ystep)/SQ));
	mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
}
