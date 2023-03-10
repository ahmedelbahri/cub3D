/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akadi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:55:27 by akadi             #+#    #+#             */
/*   Updated: 2021/12/11 13:40:36 by akadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *tnew)
{
	t_list	*p;

	p = NULL;
	if (*lst == NULL)
	{
		*lst = tnew;
		return ;
	}
	p = *lst;
	while (p -> next)
		p = p -> next;
	p -> next = tnew;
}
