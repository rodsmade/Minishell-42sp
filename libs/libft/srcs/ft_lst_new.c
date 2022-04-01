/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 10:54:46 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/01 20:24:00 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_new(void *content)
{
	t_list	*newitem;

	newitem = malloc(sizeof(t_list));
	newitem->content = content;
	newitem->next = NULL;
	return (newitem);
}
