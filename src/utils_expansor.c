/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:08:58 by adrianofaus       #+#    #+#             */
/*   Updated: 2022/04/01 19:38:22 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_append_char(char *str, char c)
{
	char	*new_str;
	int		str_size;
	int		i;

	i = -1;
	if (str)
		str_size = ft_strlen(str);
	else
		str_size = 0;
	new_str = malloc((str_size + 2) * sizeof(char));
	while (++i < str_size)
		new_str[i] = str[i];
	new_str[str_size] = c;
	new_str[str_size + 1] = '\0';
	ft_free_ptr((void *)&str);
	return (new_str);
}

int	is_valid_key_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

void	expand_wildcards(void)
{
	return ;
}

void	remove_null_nodes_from_token_list(void)
{
	t_list	*pivot;
	t_list	*tmp;

	pivot = g_tudao.token_list;
	while (pivot)
	{
		if (pivot->content == NULL)
		{
			tmp = pivot->next;
			ft_lst_remove_node(&g_tudao.token_list, pivot);
			pivot = tmp;
		}
		else
			pivot = pivot->next;
	}
	return ;
}
