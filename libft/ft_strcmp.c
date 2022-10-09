/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:00:17 by akadi             #+#    #+#             */
/*   Updated: 2022/10/09 15:03:51 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*st1;
	unsigned char	*st2;
	size_t			i;

	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	i = 0;
	while ((st1[i] != '\0' || st2[i] != '\0'))
	{
		if ((st1[i] < st2[i]) || (st1[i] > st2[i]))
		{
			return (st1[i] - st2[i]);
		}
		i++;
	}
	return (0);
}