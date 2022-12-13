/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:48:51 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/12/12 19:20:45 by ahel-bah         ###   ########.fr       */
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

void	ft_draw_map(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
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
}

float	max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

void	dda(t_data *data, t_index *player, float x1, float y1)
{
	float	step_x;
	float	step_y;
	float	max_v;
	int		i;

	player->x /= 5;
	player->y /= 5;
	step_x = x1 - player->x;
	step_y = y1 - player->y;
	max_v = max(fabs(step_x), fabs(step_y));
	step_x /= max_v;
	step_y /= max_v;
	i = 0;
	while (i <= max_v)
	{
		my_mlx_pixel_put(data, player->x, player->y);
		player->x += step_x;
		player->y += step_y;
		i++;
	}
}
