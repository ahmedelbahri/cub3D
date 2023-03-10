/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 18:45:20 by akadi             #+#    #+#             */
/*   Updated: 2022/11/01 12:03:33 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*src;
	char			*p;
	unsigned int	i;

	i = 0;
	src = (char *)s;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(src))
		return (ft_strdup(""));
	if (len > ft_strlen(src))
		len = ft_strlen(src);
	p = malloc((len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = src[start];
		i++;
		start++;
	}
	p[i] = '\0';
	return (p);
}
