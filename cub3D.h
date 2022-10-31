/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:32:01 by akadi             #+#    #+#             */
/*   Updated: 2022/10/31 11:27:42 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"

#define BUFFER_SIZE 1000000000

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
	int		X;
	int		Y;
	
}t_data;

typedef struct s_info
{
	int	num_lines;
}t_info;

//get_next_line
char	*get_next_line(int fd);

void	init_data(t_data *data);
void	extract_line(char **content, t_data *data, t_info *info);
#endif