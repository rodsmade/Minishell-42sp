/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansor_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaraujo <roaraujo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 22:53:19 by roaraujo          #+#    #+#             */
/*   Updated: 2022/05/10 18:20:47 by roaraujo         ###   ########.fr       */
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

t_list	*expand_wildcards(t_list **token)
{
	t_list	*curr_next;
	t_list	*substitutions;
	t_list	*subst_last_element;

	curr_next = (*token)->next;
	substitutions = create_wildcard_sublist((char *)(*token)->content);
	unmask_asterisks((char *)(*token)->content);
	if (!substitutions)
		return (*token);
	unmask_asterisks_in_list(substitutions);
	subst_last_element = ft_lst_last(substitutions);
	ft_free_ptr((void *)&((*token)->content));
	(*token)->content = substitutions->content;
	if (substitutions->next)
	{
		subst_last_element->next = curr_next;
		(*token)->next = substitutions->next;
		ft_free_ptr((void *)&substitutions);
		return (subst_last_element);
	}
	else
	{
		ft_free_ptr((void *)&substitutions);
		return (*token);
	}
}

bool	has_wildcard(char *token_content)
{
	int	i;

	i = -1;
	while (token_content[++i])
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
	}
	return (false);
}
