/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:48:51 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/12/16 23:24:27 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

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

void	ft_mini_map(t_data *data, t_index *player)
{
	double	y;
	double	x;
	int		i;
	int		j;

	x = 0;
	y = (player->y / SQ) - MAP_S / 2;
	data->color = 0x000000;
	j = -1;
	while (++j < MAP_S)
	{
		i = -1;
		x = (player->x / SQ) - MAP_S / 2;
		while (++i < MAP_S)
		{
			x++;
			if (x >= 0 && y >= 0
				&& x < data->pars.max_line && y < dubstrlen(data->map))
			{
				color(data, x, y);
				rectangle(i, j, data);
			}
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

void	ft_direction(t_data *data, double angle)
{
	t_index	step;
	t_index	player;
	float	max_v;
	int		i;

	player.x = ((MAP_S / 2) - 0.5) * (SQ / 5);
	player.y = ((MAP_S / 2) + 0.5) * (SQ / 5);
	step.x = (((cos(angle) * (SQ / 5)) / 2) * 5);
	step.y = (((sin(angle) * (SQ / 5)) / 2) * 5);
	max_v = max(fabs(step.x), fabs(step.y));
	step.x /= max_v;
	step.y /= max_v;
	i = 0;
	while (i <= max_v)
	{
		my_mlx_pixel_put(data, player.x, player.y);
		player.x += step.x;
		player.y += step.y;
		i++;
	}
}
