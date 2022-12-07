/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:32:01 by akadi             #+#    #+#             */
/*   Updated: 2022/12/07 21:14:40 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <mlx.h>
# include "libft/libft.h"

# define BUFFER_SIZE 1000000000
# define W 1300
# define H 1000
# define SQ 50
# define FOV 60
# define SPEED 0.05

typedef struct s_index
{
	float	x;
	float	y;
	float	var;
}			t_index;

typedef struct s_int_idx
{
	int	x;
	int	y;
}		t_int_idx;

typedef struct s_coordination
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}			t_coordination;

typedef struct s_events
{
	int		w_pressed;
	int		a_pressed;
	int		s_pressed;
	int		d_pressed;
	int		larr_pressed;
	int		rarr_pressed;
}			t_events;

typedef struct s_mlx
{
	void	*ptr;
	void	*img;
	void	*win;
	char	*addr;
	int		endian;
	int		line_length;
	int		bits_per_pixel;
}			t_mlx;

typedef struct s_player
{
	float	x;
	float	y;
	double	angle;
	char	direction;
}			t_player;

typedef struct s_texture
{
	int		h;
	int		w;
	void	*ptr;
	int		sky[3];
	int		floor[3];
	int		endian;
	int		line_length;
	int		bits_per_pixel;
}			t_texture;

typedef struct s_intersection
{
	double	ray_hor_inter_x;
	double	ray_hor_inter_y;
	double	ray_ver_inter_x;
	double	ray_ver_inter_y;
}			t_intersection;

typedef struct s_parsing
{
	int		max_line;
	int		num_lines;
	int		empty_lines;
}			t_parsing;

typedef struct s_data
{
	char			**map;
	int				color;
	t_mlx			mlx;
	t_parsing		pars;
	t_coordination	coord;
	t_intersection	inter;
	t_player		player;
	t_events		events;
	t_texture		texture;
}					t_data;

//extract_line
void	extract_line(char **content, t_data *data);
void	check_color_line(char *line, t_data *data);
void	check_each_line(char *line, char *direction, t_data *data);
void	check_line(char *line, t_data *data);
int		lines_before_map(char *content);
//fill_data
void	fill_map_with_z(t_data *data);
void	fill_color(char line, char *sub, t_data *data, int k);
void	fill_direction(t_data *data, int k, int s);
void	condition_texture(t_data *data, char direction, char *line);
//layers
int		layeronechecker(char *line);
int		layertwochecker(char *line);
int		layerthreechecker(char *line, t_data *data);
//map_handling
void	check_map_error(t_data *data);
int		check_up_down(t_data *data, int i, int j);
void	malloc_map(t_data *data, char **content, int i);
void	tallest_line(char **content, int i, t_data *data);
void	condition(char **content, int i, t_data *data);
//utils
int		is_space(char line);
int		color_is_valid(char *color);
int		num_of_comma(char *line);
//init_data
void	init_data(t_data *data);
//get_next_line
char	*get_next_line(int fd);
//draw_2d
int		register_keys(int key, t_data *data);
int		draw_2d(t_data *data);
void	image(t_data *file);
double	distance(double x, double y, double x1, double y1);
//keys
int		keys(t_data *data);
void	more_keys(t_data *data);
//main
int		dubstrlen(char **content);
#endif