/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:32:01 by akadi             #+#    #+#             */
/*   Updated: 2022/11/17 17:09:28 by ahel-bah         ###   ########.fr       */
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
# define H 900
# define W 1300
# define SQ 30
# define PI 3.142857

typedef struct s_ray
{
	int		up;
	int		down;
	int		left;
	int		right;
	float	x_wall;
	float	y_wall;
	float	angle;
}		t_ray;

typedef struct s_data
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	**map;
	char	Direction;
	int		Floor[3];
	int		sky[3];
	int		MAX_LINE;
	float	X_player;
	float	Y_player;
	void	*img;
	void	*window;
	void	*mlx;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		color;
	int		num_lines;
	int		empty_lines;
	float	angle;
	int		w_pressed;
	int		a_pressed;
	int		s_pressed;
	int		d_pressed;
	int		larr_pressed;
	int		rarr_pressed;
	t_ray	rays[W];
}			t_data;

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
int		layerOneChecker(char *line);
int		layerTwoChecker(char *line);
int		layerThreeChecker(char *line, t_data *data);
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
void	draw_2d(t_data *data);
//keys
int		keys(int key, t_data *data);
void	more_keys(int key, t_data *data);
//main
int		dubstrlen(char **content);
#endif