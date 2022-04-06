/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:07:18 by roaraujo          #+#    #+#             */
/*   Updated: 2022/04/06 20:07:37 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_3(char *str1, char *str2, char *str3)
{
	char	*new_str;
	char	*tmp;
	
	tmp = ft_strjoin(str1, str2);
	new_str = ft_strjoin(tmp, str3);
	ft_free_ptr((void *)&tmp);	
	return (new_str);
}
