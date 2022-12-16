/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:31:04 by ahel-bah          #+#    #+#             */
/*   Updated: 2022/12/16 20:23:42 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
