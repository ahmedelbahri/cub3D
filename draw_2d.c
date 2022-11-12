/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 15:29:42 by akadi             #+#    #+#             */
/*   Updated: 2022/11/12 16:59:36 by akadi            ###   ########.fr       */
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

typedef struct s_point
{
	double x;
	double y;
	/* data */
} t_point;


void	put_line(t_data *cub, t_point player, t_point end)
{
	t_point	var;
	float	dx;
	float	dy;
	float	steps;
	int		i;

	// displacement(cub, &player.x, 'x');
	// displacement(cub, &player.y, 'y');
	// displacement(cub, &end.x, 'x');
	// displacement(cub, &end.y, 'y');
	dx = (float)(end.x - player.x);
	dy = (float)(end.y - player.y);
	steps = fmax(fabs(dy), fabs(dx));
	dx = dx / steps;
	dy = dy / steps;
	var.x = player.x;
	var.y = player.y;
	i = 1;
	while (i <= steps)
	{
		my_mlx_pixel_put(cub, round(var.x), round(var.y));
		var.x += dx;
		var.y += dy;
		i++;
	}
}

void	draw_2d(t_data *data)
{
	int x,y = 0;
	// int x_of_player;
	// int y_of_player;
	int point_x;
	int point_y;
	
	image(data);
	
	while (y < data->num_lines)
	{
		x = 0;
		while (x < data->MAX_LINE)
		{
			color(data, x, y);
			rectangle(x, y, data);
			// if (data->X_player == y && data->Y_player == x)
			// {
			// 	x_of_player = x;
			// 	y_of_player = y;
			// }
			x++;
		}
		y++;
	}
	data->color = 0x0000ff;
	printf("X_pla = %d   Y_pla %d  position_x = %f  position_y = %f   angle = %f\n",data->X_player,data->Y_player,data->pixel_x,data->pixel_y, data->angle);
	// float r = 5;
	// while (r >= 0)
	// if (data->map[(int)round(data->Y_player + data->pixel_y)][(int)round(data->X_player + data->pixel_x)] != '1')
		my_mlx_pixel_put(data, (data->X_player + data->pixel_x) * SQ + SQ / 2, (data->Y_player + data->pixel_y) * SQ + SQ / 2);
	printf("%c\n", data->map[(int)round(data->Y_player + data->pixel_y)][(int)round(data->X_player + data->pixel_x)]);
	point_x = ((data->X_player + data->pixel_x) * SQ + (( (((data->X_player + 1 + data->pixel_x)) * SQ) - ((data->X_player + data->pixel_x) * SQ) )/2));
	point_y = ((data->Y_player + data->pixel_y) * SQ + (( (((data->Y_player + 1 + data->pixel_y)) * SQ) - ((data->Y_player + data->pixel_y) * SQ) )/2));
	data->color = 0xff00ff;
	dda(data, ((data->X_player + data->pixel_x) * SQ) + SQ/2, ((data->Y_player + data->pixel_y) * SQ) + SQ/2, \
	((data->X_player+ data->pixel_x) * SQ) + SQ/2 + cos(data->angle) * 20, ((data->Y_player+ data->pixel_y) * SQ) + SQ/2 + sin(data->angle) * 20);
	//dda(data, (data->X_player * SQ) + SQ/2 + (data->pixel_x * SQ), point_y, data->Y_player * (SQ*12) + (data->pixel_x * SQ),point_y);
	//dda(data, (x_of_player) * (SQ) + (SQ * 5) , point_y, x_of_player * (SQ) + SQ/2,point_y);
	//dda(data, point_x , y_of_player * (SQ) + SQ/2, point_x,(y_of_player) * (SQ) + (SQ * 5) );
	//dda(data, point_x, y_of_player * (SQ) + SQ/2 * sin(PI/2), point_x,(y_of_player) * (SQ) + (SQ * 5) * cos(0));
	mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
}
