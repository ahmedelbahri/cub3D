/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <akadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 20:31:41 by akadi             #+#    #+#             */
/*   Updated: 2022/10/10 12:03:53 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char*)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}


int main ()
{
	const char *n = "44,231,238,45,87";

	int i = 0, j = 0;
	int len = strlen(n);
	while (n[i])
	{
		if (n[i] != ',' && !i)
			j = i;
		if (n[i] == ',' || len - 1 == i)
		{
			if (len - 1 == i)
				i++;
			printf("%s\n", ft_parse(ft_substr(n, j, i - j));
			j = i+1;
		}
		i++;
	}
	
}