/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 15:29:42 by akadi             #+#    #+#             */
/*   Updated: 2022/12/16 17:49:40 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_wich_texture(t_data *data)
{
	if (data->proj.v_n_h && (((data->inter.angle >= (M_PI)) && \
	(data->inter.angle <= (2 * M_PI))) || (data->inter.angle <= (0))))
		data->color = data->proj.so[(data->texture.h * \
		data->proj.offset_y) + data->proj.offset_x];
	else if (data->proj.v_n_h)
		data->color = data->proj.no[(data->texture.h * \
		data->proj.offset_y) + \
		data->proj.offset_x];
	else if (data->proj.v_n_h == 0 && (data->inter.angle >= (M_PI / 2) \
		&& (data->inter.angle <= (M_PI * 1.5))))
		data->color = data->proj.ea[(data->texture.h * \
		data->proj.offset_y) + \
		data->proj.offset_x];
	else
		data->color = data->proj.we[(data->texture.h * \
		data->proj.offset_y) + \
		data->proj.offset_x];
}

void	project(t_data *data, double dist, int ray_i, float hit)
{
	dist = dist * cos((data->inter.angle - data->player.angle));
	data->proj.projection_plane = (W / 2) / tan(FOV / 2 * M_PI / 180);
	data->proj.wall_height_stripe = SQ * data->proj.projection_plane / dist;
	data->proj.y = (H / 2) - (data->proj.wall_height_stripe / 2);
	data->color = 0xFFFFFF;
	data->proj.offset_x = (hit - (int)hit) * (data->texture.w);
	data->proj.line = data->proj.y;
	while (data->proj.line < data->proj.wall_height_stripe + data->proj.y)
	{
		data->proj.offset_y = (data->proj.line - data->proj.y) * \
		((float)data->texture.h / data->proj.wall_height_stripe);
		ft_wich_texture(data);
		my_mlx_pixel_put(data, ray_i, data->proj.line);
		data->proj.line++;
	}
	data->color = data->texture.c;
	draw_line(data, ray_i, 0, data->proj.y);
	data->color = data->texture.f;
	draw_line(data, ray_i, data->proj.wall_height_stripe + data->proj.y, H);
}

void	ft_cast_rays(t_data *data, t_index player)
{
	int	i;

	i = 0;
	while (i < W)
	{
		data->inter.hor_dis = horizontal_inter(data, player, data->inter.angle);
		data->inter.ver_dis = vertical_inter(data, player, data->inter.angle);
		if (data->inter.hor_dis < data->inter.ver_dis)
		{
			data->proj.v_n_h = 1;
			project(data, data->inter.hor_dis, i, \
				data->inter.ray_hor_inter_x / SQ);
		}
		else
		{
			data->proj.v_n_h = 0;
			project(data, data->inter.ver_dis, i, \
				data->inter.ray_ver_inter_y / SQ);
		}
		data->inter.angle += (FOV * (M_PI / 180) / W);
		i++;
	}
}

int	draw_2d(t_data *data)
{
	mlx_clear_window(data->mlx.ptr, data->mlx.win);
	image(data);
	data->player_i.y = (data->player.y * SQ) + SQ / 2;
	data->player_i.x = (data->player.x * SQ) + SQ / 2;
	data->inter.angle = data->player.angle - ((FOV / 2) * (M_PI / 180));
	ft_cast_rays(data, data->player_i);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->mlx.img, 0, 0);
	return (0);
}
