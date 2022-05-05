/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansor_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 22:53:19 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/05 15:26:16 by roaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unmask_asterisks_in_list(t_list *list)
{
	t_list	*pivot;

	pivot = list;
	while (pivot)
	{
		unmask_asterisks((char *)pivot->content);
		pivot = pivot->next;
	}
}

void	expand_wildcards(t_list **token)
{
	t_list	*curr_next;
	t_list	*substitutions;
	t_list	*subst_last_element;

	curr_next = (*token)->next;
	substitutions = create_wildcard_sublist((char *)(*token)->content);
	if (!substitutions)
	{
		unmask_asterisks((char *)(*token)->content);
		return ;
	}
	unmask_asterisks_in_list(substitutions);
	subst_last_element = ft_lst_last(substitutions);
	subst_last_element->next = curr_next;
	ft_free_ptr((void *)&((*token)->content));
	(*token)->content = substitutions->content;
	(*token)->next = substitutions->next;
	ft_free_ptr((void *)&substitutions);
	*token = subst_last_element;
	return ;
}

bool	has_wildcard(char *token_content)
{
	int	i;

	i = 0;
	while (token_content[i])
	{
		if (token_content[i] == '\'')
		{
			while (token_content[++i] && token_content[i] != '\'')
				continue ;
			if (token_content[i])
				i++;
		}
		if (token_content[i] == '\"')
		{
			while (token_content[++i] && token_content[i] != '\"')
				continue ;
			if (token_content[i])
				i++;
		}
		if (token_content[i] == '*')
			return (true);
		if (!token_content[i])
			break ;
		i++;
	}
	return (false);
}
