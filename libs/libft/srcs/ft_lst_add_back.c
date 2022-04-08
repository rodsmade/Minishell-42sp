/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_add_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 10:54:25 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/01 20:24:31 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_add_back(t_list **lst, t_list *new)
{
	t_list	*last_element;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last_element = ft_lst_last(*lst);
		last_element->next = new;
	}
}
